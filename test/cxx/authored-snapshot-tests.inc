void compressedAuthoredAssets() {
#ifdef PDG_SPRITER_SUPPORT
    using namespace pdg;
    const auto fixture=std::filesystem::path(__FILE__).parent_path().parent_path()/"data/spriter-regression/arm.scml";
    const auto xml=SpriterSnapshotAsset::loadDocument(fixture.string());
    const std::string tiny="<spriter_data/>";
    auto read=[](Serializer& writer) {
        auto* bytes=std::malloc(writer.getDataSize());
        std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        return std::make_unique<Deserializer>(bytes,writer.getDataSize());
    };
    for(bool tags:{false,true}) {
        auto asset=SpriterSnapshotAsset::share(new SpriterSnapshotAsset());asset->path=fixture.string();
        // Change the same resource in both directions to exercise cache invalidation.
        for(const auto& document:std::vector<std::string>{xml,tiny,xml}) {
            asset->setDocument(document);
            Serializer writer;writer.setSendTags(tags);
            const auto size=asset->getSerializedSize(&writer);asset->serialize(&writer);
            expect(writer.getDataSize()==size+(tags?3:0),"compressed/raw asset size matches actual stream bytes");
            auto fields=read(writer);
            expect(fields->deserialize_1u()==3&&!fields->deserialize_bool(),"versioned complete asset record");
            std::string path;fields->deserialize_string(path);
            const auto high=fields->deserialize_4u(),low=fields->deserialize_4u();
            const auto encoding=fields->deserialize_1u();const auto length=fields->deserialize_uint();
            const auto stored=fields->deserialize_memGetLen();std::string payload(stored,'\0');
            fields->deserialize_mem(payload.data(),stored);
            expect(length==document.size(),"asset records exact original XML byte length");
            expect(encoding==(document==tiny?0:1),"XML compresses only when its payload gets smaller");
            if(encoding)expect(stored<document.size()/2,"representative SCML achieves substantial compression");
            else expect(payload==document,"small XML remains readable raw bytes");
            auto reader=read(writer);auto copy=SpriterSnapshotAsset::share(new SpriterSnapshotAsset());copy->deserialize(reader.get());
            expect(copy->getDocument()==document,"XML codec round trip is byte-exact");
            Serializer rewritten;rewritten.setSendTags(tags);copy->serialize(&rewritten);
            expect(rewritten.getDataSize()==writer.getDataSize() &&
                std::memcmp(rewritten.getDataPtr(),writer.getDataPtr(),writer.getDataSize())==0,"restored asset can reuse its encoded payload");
            auto rejects=[&](uint8 codec,uint32 expanded,const std::string& bytes,uint8 version=3,uint32 checksumDelta=0) {
                Serializer bad;bad.setSendTags(tags);bad.serialize_1u(version);bad.serialize_bool(false);
                bad.serialize_string(path);bad.serialize_4u(high);bad.serialize_4u(low^checksumDelta);
                bad.serialize_1u(codec);bad.serialize_uint(expanded);bad.serialize_mem(bytes.data(),bytes.size());bad.serialize_uint(0);
                auto input=read(bad);auto rejected=SpriterSnapshotAsset::share(new SpriterSnapshotAsset());
                bool failed=false;try{rejected->deserialize(input.get());}catch(const std::exception&){failed=true;}
                expect(failed,"malformed XML snapshot is rejected");
            };
            rejects(2,length,payload); // unknown encoding
            rejects(encoding,length,payload,1); // old asset format
            rejects(encoding,0,payload);
            rejects(encoding,64*1024*1024+1,payload);
            rejects(encoding,length,std::string());
            rejects(encoding,length,payload,3,1); // original-document fingerprint
            rejects(encoding,length+1,payload);
            rejects(encoding,length-1,payload);
            if(encoding) {
                rejects(encoding,length,payload.substr(0,payload.size()-1));
                rejects(encoding,length,payload+"trailing data");
                rejects(encoding,length,payload+payload); // concatenated streams are not one XML record
                auto corrupt=payload;corrupt.back()^=1;rejects(encoding,length,corrupt);
                rejects(encoding,8,payload); // stop expansion at the declared bound
            }
        }
        asset->setDocument(xml);
        Serializer shared;shared.setSendTags(tags);
        const auto size=shared.sizeof_obj(asset.get())+shared.sizeof_obj(asset.get());
        shared.serialize_obj(asset.get());const auto firstSize=shared.getDataSize();shared.serialize_obj(asset.get());
        expect(shared.getDataSize()==size+(tags?3:0),"shared compressed assets have exact object-stream size");
        expect(shared.getDataSize()-firstSize<16,"shared XML is encoded once per stream");
        auto reader=read(shared);auto* first=reader->deserialize_obj();auto* second=reader->deserialize_obj();
        expect(first==second,"compressed asset identity survives repeated references");first->release();second->release();

        Serializer external;external.setSendTags(tags);external.setResourceMode(serialization_ExternalReferences);
        const auto externalSize=asset->getSerializedSize(&external);asset->serialize(&external);
        expect(external.getDataSize()==externalSize+(tags?3:0),"external reference sizing remains exact");
        expect(external.getDataSize()<asset->path.size()+40,"external asset omits XML payload");
        reader=read(external);auto copy=SpriterSnapshotAsset::share(new SpriterSnapshotAsset());copy->deserialize(reader.get());
        expect(copy->getDocument()==xml,"external XML still resolves and verifies its original fingerprint");
    }
#endif
}

void authoredSnapshots() {
#if defined(PDG_SPRITER_SUPPORT)
    using namespace pdg;
    const auto fixture=std::filesystem::path(__FILE__).parent_path().parent_path()/"data/spriter-regression/arm.scml";
    const auto png=std::filesystem::path(__FILE__).parent_path().parent_path()/"data/earthmap2.png";
    {
        auto broken=SpriterSnapshotAsset::share(new SpriterSnapshotAsset());
        broken->path=fixture.string();broken->setDocument(SpriterSnapshotAsset::loadDocument(fixture.string()));
        broken->restored=true; // Deliberately omit the image table required by the document.
        bool rejected=false;try{broken->model();}catch(const std::exception&){rejected=true;}
        expect(rejected,"incomplete restored asset rejects without double-deleting its factories");
    }
    const auto directory=std::filesystem::temp_directory_path()/std::filesystem::path("pdg-authored-snapshot-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(directory);
    struct Cleanup {std::filesystem::path path;~Cleanup(){std::error_code error;std::filesystem::remove_all(path,error);}} cleanup{directory};
    for(int mode:{serialization_Complete,serialization_ExternalReferences})for(bool tags:{false,true}) {
        std::filesystem::copy_file(png,directory/"earthmap2.png",std::filesystem::copy_options::overwrite_existing);
        auto document=SpriterSnapshotAsset::loadDocument(fixture.string());
        auto offset=document.find("../earthmap2.png");document.replace(offset,std::strlen("../earthmap2.png"),"earthmap2.png");
        const auto path=directory/"arm.scml";
        {std::ofstream out(path);out<<document;}
#ifdef PDG_NO_GUI
        auto* layer=createSpriteLayer(),*copy=createSpriteLayer();
#else
        auto* layer=createSpriteLayer(nullptr),*copy=createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(false);copy->setUseChipmunkPhysics(false);
#endif
        auto* a=layer->createSpriteFromSpriterFile(path.c_str(),"arm");auto* b=layer->createSpriteFromSpriterEntity("arm");
        expect(a&&b,"authored snapshot fixture loads two shared instances");
        expect(a->enableAnimationPose("reference")&&b->enableAnimationPose("reference"),"enable reference rigs before saving bindings");
        a->setLocation(20,30);a->setScale(2);a->seekAnimation("reach",.25);a->pauseAnimation();a->enableSpriterEvents(true);
        auto transform=a->getAnimationBoneTransform("shoulder");transform.rotation=.2;a->setAnimationBoneTransform("shoulder",transform);
        b->seekAnimation("reach_once",.4);b->setAnimationSource(animationSource_Reference);
        auto* bone=a->createPart("bone"),*socket=a->createPart("socket"),*art=a->createPart("art");
        bone->bindToBone(a->getAnimationRig()->findBone("forearm")).setLocation(1,2);
        socket->bindToAnimationSocket("grip");art->bindToAnimationBinding("hand_art");
        bone->setupPhysicsBody().setMode(physicsBody_Kinematic);
        bone->setupCollider().setCircle(.5);a->setupAnimationCollider();
        const auto expectedBone=bone->getTransform(partSpace_World),expectedSocket=socket->getTransform(partSpace_World),expectedArt=art->getTransform(partSpace_World);
        auto* keep=copy->createSprite();Serializer writer;writer.setResourceMode(mode);writer.setSendTags(tags);
        const auto size=layer->getSerializedSize(&writer);layer->serialize(&writer);
        expect(writer.getDataSize()==size+(tags?3:0),"authored asset graph size accounts for shared document/images once");
        auto load=[&]{auto* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());Deserializer reader(bytes,writer.getDataSize());copy->deserialize(&reader);};
        if(mode==serialization_Complete) {std::filesystem::remove(path);std::filesystem::remove(directory/"earthmap2.png");}
        else {
            {std::ofstream changed(path,std::ios::app);changed<<"\n";}
            bool rejected=false;try{load();}catch(const std::exception&){rejected=true;}
            expect(rejected&&copy->getNthSprite(0)==keep,"changed external document rejects atomically");
            {std::ofstream restored(path);restored<<document;}
            std::filesystem::rename(path,directory/"hidden.scml");rejected=false;try{load();}catch(const std::exception&){rejected=true;}
            expect(rejected&&copy->getNthSprite(0)==keep,"missing external document rejects atomically");std::filesystem::rename(directory/"hidden.scml",path);
        }
        load();auto* first=copy->getNthSprite(0),*second=copy->getNthSprite(1);
        expect(first->isSpriterSprite()&&second->isSpriterSprite(),"imported instances survive scene loading");
        expect(first->getAnimationRig()==second->getAnimationRig(),"restored instances share model and cached rig identity");
        expect(first->isAnimationPaused()&&first->areSpriterEventsEnabled(),"playback pause and trigger delivery settings survive");
        near(first->getAnimationProgress(),.25,"authored fractional playback time survives");
        near(first->getAnimationBoneTransform("shoulder").rotation,.2,"authored local bone overrides survive");
        expect(second->getAnimationSource()==animationSource_Reference,"reference-pose source survives");
        auto* cb=first->findPart("bone"),*cs=first->findPart("socket"),*ca=first->findPart("art");
        expect(cb->getBoneId()==first->getAnimationRig()->findBone("forearm"),"Part bone binding restores against new rig");
        expect(cs->getAnimationSocketName()=="grip"&&ca->getAnimationBindingName()=="hand_art","socket and artwork bindings restore by name");
        for(const auto& entry:std::vector<std::pair<Part*,SpatialTransform>>{{cb,expectedBone},{cs,expectedSocket},{ca,expectedArt}}) {
            const auto frame=entry.first->getTransform(partSpace_World);near(frame.tx,entry.second.tx,"restored bound Part x");near(frame.ty,entry.second.ty,"restored bound Part y");
        }
        expect(first->collider.getGeometrySource()==colliderSource_Animation&&first->collider.getShapeCount()>0,"authored collision boxes remain a live source");
        first->resumeAnimation();copy->animateLayer(100);expect(first->getAnimationProgress()>.25,"restored authored playback advances");
        expect(cb->isBoundToBone()&&cb->physics.getMode()==physicsBody_Kinematic,"bound Part body remains attached after playback");
        cleanupLayer(layer);expect(first->hasAnimation("reach"),"restored model is independent of the original scene lifetime");
        cleanupLayer(copy);
    }
#ifndef PDG_NO_GUI
    for(int mode:{serialization_Complete,serialization_ExternalReferences})for(int transition:{0,1,2}) {
        auto* layer=createSpriteLayer(nullptr);auto* source=layer->createSpriteFromSpriterFile(fixture.c_str(),"arm");
        expect(source->enableAnimationPose("reference"),"transition snapshot reference rig");
        if(transition==0){source->startAnimation("reference");source->blendToAnimation("reach",1);step(*source,250);}
        else {source->seekAnimation("reference",0);source->resumeAnimation();source->transitionToAnimation("reach",0,1);step(*source,250);
            if(transition==2){source->transitionToAnimation("reference",.2,1);step(*source,125);}}
        AnimationTwoBoneIK config;config.root=0;config.middle=1;config.tip=2;config.rootLength=10;config.middleLength=5;
        config.targetX=10;config.targetY=10;config.influence=.3;
        auto retired=source->addAnimationIK(config);source->removeAnimationModifier(retired);
        auto id=source->addAnimationIK(config,4);
        std::unique_ptr<Drawing> drawing(Drawing::create());delete drawing->addLine(pdg::Point(0,0),pdg::Point(8,0),Attributes().lineThickness(2));
        AnimationDrawableOptions options;options.bone=2;options.bounds={0,-1,8,1,false};options.strokeSpace=animationStroke_Local;
        auto removed=source->addAnimationDrawable(options,*drawing);source->removeAnimationDrawable(removed);
        const auto artwork=source->addAnimationDrawable(options,*drawing);source->getAnimationPose();
        Serializer writer;writer.setResourceMode(mode);const auto size=source->getSerializedSize(&writer);source->serialize(&writer);
        expect(writer.getDataSize()==size+3,"transition/IK/Drawing record size");
        auto* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());Deserializer reader(bytes,writer.getDataSize());
        Sprite copy;copy.deserialize(&reader);
        expect(copy.isBlending()==source->isBlending()&&copy.isAnimationTransitioning()==source->isAnimationTransitioning(),"active blend/transition state survives");
        near(copy.getBlendProgress(),source->getBlendProgress(),"blend progress survives");
        near(copy.getAnimationTransitionProgress(),source->getAnimationTransitionProgress(),"transition progress survives");
        expect(copy.getAnimationModifierError(id).empty()&&copy.getAnimationDrawableError(artwork).empty(),"authored controller/artwork IDs preserve deleted gaps");
        expect(!copy.getAnimationDrawBounds().uncullable,"retained Drawing keeps its placement bounds");
        near(copy.getAnimationIKResult(id).reachError,source->getAnimationIKResult(id).reachError,"builtin rig IK result survives");
        for(int tick=0;tick<6;++tick) {
            step(*source,100);step(copy,100);
            near(copy.getAnimationTransitionProgress(),source->getAnimationTransitionProgress(),"restored transition clock continues in seconds");
            for(const auto& name:source->getAnimationBoneNames()) {
                const auto a=source->getAnimationBoneTransform(name.c_str()),b=copy.getAnimationBoneTransform(name.c_str());
                near(a.x,b.x,"resumed authored pose x");near(a.y,b.y,"resumed authored pose y");near(a.rotation,b.rotation,"resumed authored rotation");
            }
        }
        copy.setAnimationIKTarget(id,12,8);expect(copy.getAnimationIKResult(id).reachError>=0,"restored builtin IK remains editable");
        copy.setAnimationDrawableEnabled(artwork,false);copy.removeAnimationDrawable(artwork);
        expect(copy.addAnimationDrawable(options,*drawing)>artwork,"restored drawable ID allocator keeps its cursor");
        copy.removeAnimationModifier(id);expect(copy.addAnimationIK(config)>id,"restored modifier ID allocator keeps its cursor");
        cleanupLayer(layer);
    }
#endif
#endif
}
