void partArtworkColliders() {
    using namespace pdg;
    Sprite owner;auto* part=owner.createPart("art");
    auto& empty=part->setupFrameCollider(frameCollider_Bounds);
    expect(empty.getShapeCount()==0,"contentless Part has no invented frame bounds");
    bool rejected=false;try{part->setupFrameCollider(99);}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected && &static_cast<Collider&>(part->collider)==&empty,"invalid Part source setup preserves collider identity");
#ifndef PDG_NO_GUI
    auto drawing=std::unique_ptr<Drawing>(Drawing::create());
    auto rect=std::unique_ptr<ElementRef>(drawing->addRect(pdg::Rect(-2,-3,4,5),Attributes()));
    part->setDrawing(*drawing).setLocation(10,20);
    near(empty.getBounds().left,8,"Drawing bounds use Part-local artwork");
    const auto shape=empty.getShapeId(0),extra=empty.addCircle(1,pdg::Point(50,0));
    rect->setAttributes(Attributes().translation(Offset(3,0)));
    near(empty.getBounds().left,11,"Drawing edits refresh source bounds");
    expect(empty.getShapeId(0)==shape && empty.getShapeCount()==2,"source edits preserve source and explicit shape IDs");
    rejected=false;try{part->setupFrameCollider();}catch(const std::logic_error&){rejected=true;}
    expect(rejected && empty.getShapeId(0)==shape,"unsupported Drawing alpha source rejects atomically");
    empty.removeShape(extra);
    for(bool tags:{false,true})for(int mode:{serialization_Complete,serialization_ExternalReferences}) {
        Serializer writer;writer.setSendTags(tags);writer.setResourceMode(mode);
        const auto size=owner.getSerializedSize(&writer);owner.serialize(&writer);
        expect(writer.getDataSize()==size+(tags?3:0),"Part artwork source snapshot size");
        auto reader=snapshotReader(writer);Sprite copy;copy.deserialize(reader.get());
        auto* restored=copy.findPart("art");
        expect(restored->collider.getGeometrySource()==colliderSource_Frame,"Part Drawing source survives snapshot");
        near(restored->collider.getBounds().left,11,"restored Drawing frame bounds");
        restored->clearContent();expect(restored->collider.getShapeCount()==0,"clearing restored content removes source shape");
    }
    auto* image=new ImageOpenGL();image->addRef();image->initEmpty(4,2,32);
    std::memset(image->data,0,32);
    static_cast<uint8*>(image->data)[3]=255;static_cast<uint8*>(image->data)[7]=255;
    part->setImage(*image,pdg::Rect(0,0,8,4));image->release();
    part->setupFrameCollider();const auto mask=part->collider.getShapeId(0);
    expect(part->collider.contains(pdg::Point(11,21)) && !part->collider.contains(pdg::Point(17,23)),"Part image alpha excludes transparent pixels");
    part->setFlipX(true);
    expect(part->collider.contains(pdg::Point(9,21)),"Part image alpha follows reflection");
    expect(part->collider.getShapeId(0)==mask,"reflection retains alpha source identity");
    Serializer writer;owner.serialize(&writer);auto reader=snapshotReader(writer);Sprite copy;copy.deserialize(reader.get());
    expect(copy.findPart("art")->collider.contains(pdg::Point(9,21)),"Part image alpha restores with reflected artwork");
    part->clearContent();expect(part->collider.getShapeCount()==0,"clearContent invalidates cached mask");
    auto* strip=new ImageOpenGL();strip->addRef();strip->initEmpty(4,2,32);strip->setNumFrames(2);
    std::memset(strip->data,0,32);static_cast<uint8*>(strip->data)[3]=255;
    auto stripDrawing=std::unique_ptr<Drawing>(Drawing::create());
    auto frame=std::unique_ptr<ElementRef>(stripDrawing->addImageStrip(pdg::Rect(0,0,4,4),*strip,Attributes().frame(0)));
    part->setDrawing(*stripDrawing);strip->release();part->setFlipX(false);
    expect(part->collider.contains(pdg::Point(11,21)),"Drawing strip frame zero has opaque pixel");
    frame->setAttributes(Attributes().frame(1));
    expect(!part->collider.contains(pdg::Point(11,21)),"Drawing frame changes refresh alpha pixels");
    frame->setAttributes(Attributes().frame(0));
    expect(part->collider.contains(pdg::Point(11,21)),"returning to a Drawing strip frame restores its mask");
#endif
#ifdef PDG_SPRITER_SUPPORT
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    const auto path=(std::filesystem::path(__FILE__).parent_path()/"../data/spriter-regression/arm.scml").lexically_normal().string();
    auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());
    sprite->pauseAnimation();expect(sprite->enableAnimationPose("reference"),"Part box fixture pose enables");
    auto* boneOnly=sprite->createPart("boneOnly");boneOnly->bindToBone(0);
    expect(boneOnly->setupFrameCollider().getShapeCount()==0,"bone binding alone never guesses image artwork, including in headless builds");
    auto* box=sprite->createPart("hit");box->bindToAnimationBinding("hitbox").setLocation(2,3);
    auto& collider=box->setupAnimationCollider("hitbox");const auto id=collider.getShapeId(0);
    const auto initial=collider.getBounds();const auto authored=sprite->getSpriterCollisionBox("hitbox").getQuad().getBounds();
    near(initial.left,authored.left,"named Part box initially matches authored box despite local offset");
    box->moveBy(1,0);const auto moved=collider.getBounds();
    expect(std::abs(moved.left-initial.left)>0.1,"later local edits carry the box with the Part");
    rejected=false;try{box->setupAnimationCollider("grip");}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected && collider.getShapeId(0)==id,"non-box selection leaves prior source intact");
    for(bool tags:{false,true})for(int mode:{serialization_Complete,serialization_ExternalReferences}) {
        Serializer writer;writer.setSendTags(tags);writer.setResourceMode(mode);
        const auto size=sprite->getSerializedSize(&writer);sprite->serialize(&writer);
        expect(writer.getDataSize()==size+(tags?3:0),"named Part box exact snapshot size");
        auto reader=snapshotReader(writer);Sprite copy;copy.deserialize(reader.get());
        auto* restored=copy.findPart("hit");
        near(restored->collider.getBounds().left,moved.left,"snapshot preserves box setup offset rather than recapturing it");
        expect(restored->collider.getShapeId(0)==id,"snapshot preserves authored source ID");
        copy.setFlipX(true);expect(std::isfinite(restored->collider.getBounds().left),"restored box reflects with pose");
    }
    sprite->disableAnimationPose();expect(collider.getShapeCount()==0,"invalidated pose safely retires Part box source");
    rejected=false;try{Serializer writer;sprite->serialize(&writer);}catch(const std::runtime_error&){rejected=true;}
    expect(rejected,"invalidated authored source cannot silently rebind during snapshot restoration");
    cleanupLayer(layer);
#endif
}
