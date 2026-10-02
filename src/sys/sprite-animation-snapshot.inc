// Imported asset and playback records precede Parts so their source frames exist
// before local transforms or bodies are restored.
class SpriteAnimationSnapshot {
#ifdef PDG_SPRITER_SUPPORT
    struct IK {
        AnimationModifierId id;
        int order;
        bool enabled;
        std::string error;
        AnimationTwoBoneIK config;
        AnimationIKResult result;
    };
    struct Artwork {
        AnimationDrawableId id;
        AnimationDrawableOptions options;
        bool enabled;
        std::string error;
        std::shared_ptr<Drawing> drawing;
    };
    struct State {
        std::shared_ptr<SpriterEngine::SpriterModel> model;
        SpriterSnapshotAsset* asset=nullptr;
        std::string entity,clip,reference;
        double seconds=0;
        float scaleX=1,scaleY=1;
        bool paused=false,finished=false,events=false,pose=false,blending=false;
        std::string blendTarget,transitionSource;
        double blendDuration=0,blendElapsed=0,blendProgress=0;
        double transitionTime=0,transitionDuration=0,transitionElapsed=0;
        bool transitioning=false,transitionCompleted=false;
        std::shared_ptr<AnimationPose> transitionSnapshot;
        int source=animationSource_Clip,debug=animationDebug_None;
        std::vector<std::string> maps;
        std::map<AnimationBoneId,AnimationTransform> overrides;
        std::vector<IK> ik;
        std::vector<Artwork> artwork;
        uint32 nextModifier=1,nextDrawable=1;
        uint64_t revision=1;
    };
    static State capture(const Sprite& s) {
        State result;
        if(!s.mEntityInstance)return result;
        auto* factory=dynamic_cast<PDGFileFactory*>(s.mSpriterModel->getFileFactory());
        if(!factory)throw std::runtime_error("Imported animation snapshots require the PDG file factory");
        result.asset=&factory->snapshotAsset();result.asset->validate();
        if(s.mAnimationPipeline) {
            for(const auto& entry:s.mAnimationPipeline->mEntries) {
                auto found=s.mAnimationIK.find(entry->id);
                if(found==s.mAnimationIK.end())throw std::runtime_error("Cannot snapshot animation modifier callbacks");
                result.ik.push_back({entry->id,entry->order,entry->enabled,entry->error,found->second->config,found->second->result});
            }
            result.nextModifier=s.mAnimationPipeline->mNextId;result.revision=s.mAnimationPipeline->mRevision;
        }
        for(const auto& entry:s.mAnimationDrawings.mEntries) {
            if(!entry->constantDrawing)throw std::runtime_error("Cannot snapshot animation drawing callbacks");
            result.artwork.push_back({entry->id,entry->options,entry->enabled,entry->error,entry->constantDrawing});
        }
        result.nextDrawable=s.mAnimationDrawings.mNextId;
        if(!s.mAttachedSprites.empty()||s.mSpriterAttachmentOwner)
            throw std::runtime_error("Use Part mounts before saving imported Sprite attachments");
        result.model=s.mSpriterModelOwner;
        if(!result.model)result.model=std::shared_ptr<SpriterEngine::SpriterModel>(s.mSpriterModel,[](SpriterEngine::SpriterModel*){});
        result.entity=s.mEntityInstance->currentEntityName();result.clip=s.mEntityInstance->currentAnimationName();
        result.seconds=s.mEntityInstance->getCurrentTime()/1000.;
        result.scaleX=s.mEntityScaleX;result.scaleY=s.mEntityScaleY;
        result.paused=s.mIsAnimationPaused;result.finished=s.mIsAnimationFinished;result.events=s.mSpriterEventsEnabled;
        result.maps=s.mAppliedCharacterMaps;result.pose=bool(s.mAnimationPoseAdapter);
        result.blending=s.mIsBlending;result.blendTarget=s.mBlendTargetName;
        result.blendDuration=s.mBlendDurationMs/1000.;result.blendElapsed=s.mBlendElapsedMs/1000.;result.blendProgress=s.mBlendProgress;
        if(result.pose) {
            for(const auto& item:s.mAnimationRigSchema->referenceRigs)
                if(item.second==s.getAnimationRig()){result.reference=item.first;break;}
            if(result.reference.empty())throw std::runtime_error("Missing imported reference clip");
            result.source=s.getAnimationSource();result.debug=s.mAnimationDebugDraw;result.overrides=s.mAnimationPoseAdapter->mOverrides;
            const auto& a=*s.mAnimationPoseAdapter;result.transitioning=a.mTransitionActive;result.transitionCompleted=a.mTransitionCompleted;
            result.transitionSource=a.mTransitionSource;result.transitionTime=a.mTransitionTime;
            result.transitionDuration=a.mTransitionDuration;result.transitionElapsed=a.mTransitionElapsed;
            if(a.mTransitionSnapshot)result.transitionSnapshot=std::make_shared<AnimationPose>(a.mTransitionSnapshot->copy());
        }
        return result;
    }
    static void configure(Sprite& s,const State& state) {
        std::unique_ptr<SpriterEngine::EntityInstance> entity;
        if(state.asset) {
            entity.reset(state.model->getNewEntityInstance(state.entity));
            if(!entity)throw std::runtime_error("Missing saved Spriter entity: "+state.entity);
            bool found=false;
            for(int i=0;i<entity->animationCount();++i){entity->setCurrentAnimation(i);if(entity->currentAnimationName()==state.clip){found=true;break;}}
            if(!found)throw std::runtime_error("Missing saved Spriter animation: "+state.clip);
            for(const auto& name:state.maps)entity->applyCharacterMap(name);
            entity->setCurrentTime(state.seconds*1000.);
            if(state.paused)entity->pausePlayback();
        }
        s.disableAnimationPose();
        delete s.mEntityInstance;s.mEntityInstance=entity.release();
        s.mSpriterModelOwner=state.model;s.mSpriterModel=state.model.get();
        s.mEntityScaleX=state.scaleX;s.mEntityScaleY=state.scaleY;
        s.mIsBlending=false;s.mBlendTargetName.clear();s.mBlendDurationMs=s.mBlendElapsedMs=0;s.mBlendProgress=0;
        s.mAppliedCharacterMaps=state.maps;s.mSpriterEventsEnabled=state.events;
        s.mIsAnimationPaused=state.paused;s.mIsAnimationFinished=state.finished;
        s.cacheSpriterAnimationNames();
        // Caching enumerates clips; restore the saved phase after enumeration.
        if(s.mEntityInstance){s.mEntityInstance->setCurrentAnimation(state.clip);s.mEntityInstance->setCurrentTime(state.seconds*1000.);if(state.paused)s.mEntityInstance->pausePlayback();}
        s.mIsBlending=state.blending;s.mBlendTargetName=state.blendTarget;
        s.mBlendDurationMs=state.blendDuration*1000.;s.mBlendElapsedMs=state.blendElapsed*1000.;s.mBlendProgress=state.blendProgress;
        if(state.blending) {
            if(!s.hasAnimation(state.blendTarget.c_str()))throw std::runtime_error("Missing saved blend target");
            s.mEntityInstance->setCurrentAnimation(state.blendTarget,s.mBlendDurationMs);
            if(state.paused)s.mEntityInstance->pausePlayback();
            s.mEntityInstance->blend(state.blendProgress,s.mEntityInstance->getTimeRatio());
        }
        if(state.pose) {
            if(!s.enableAnimationPose(state.reference.c_str()))throw std::runtime_error(s.getAnimationRigError());
            auto& adapter=*s.mAnimationPoseAdapter;
            adapter.mTransitionActive=state.transitioning;adapter.mTransitionCompleted=state.transitionCompleted;
            adapter.mTransitionSource=state.transitionSource;adapter.mTransitionTime=state.transitionTime;
            adapter.mTransitionDuration=state.transitionDuration;adapter.mTransitionElapsed=state.transitionElapsed;
            adapter.mTransitionModel=s.mSpriterModel;
            if(state.transitionSnapshot)adapter.mTransitionSnapshot=std::make_unique<AnimationPose>(state.transitionSnapshot->copy());
            if(state.transitioning&&!state.transitionSnapshot&&!s.hasAnimation(state.transitionSource.c_str()))throw std::runtime_error("Missing saved outgoing clip");
            s.setAnimationSource(state.source);
            for(const auto& item:state.overrides) {
                s.getAnimationRig()->getBone(item.first);
                s.mAnimationPoseAdapter->setBoneOverride(item.first,item.second,s.spriterRootTransform());
            }
            for(const auto& item:state.ik) {
                s.mAnimationPipeline->mNextId=item.id;
                const auto id=s.addAnimationIK(item.config,item.order);
                auto entry=s.mAnimationPipeline->find(id);entry->enabled=item.enabled;entry->error=item.error;
                s.mAnimationIK.at(id)->result=item.result;
            }
            s.mAnimationPipeline->mNextId=state.nextModifier;s.mAnimationPipeline->mRevision=state.revision;
#ifndef PDG_NO_GUI
            for(const auto& item:state.artwork) {
                s.mAnimationDrawings.mNextId=item.id;const auto id=s.addAnimationDrawable(item.options,*item.drawing);
                auto entry=s.mAnimationDrawings.find(id);entry->enabled=item.enabled;entry->error=item.error;
            }
            s.mAnimationDrawings.mNextId=state.nextDrawable;
            s.setAnimationDebugDraw(state.debug);
#else
            if(!state.artwork.empty())throw std::runtime_error("Authored Drawing snapshots require GUI support");
#endif
        }
        s.invalidateSpriterPose();s.refreshSpriterPose();
    }
    static uint32 encodePose(const AnimationPose& pose,ISerializer* writer,bool emit) {
        SnapshotWriter out(writer,emit);
        auto integer=[&](uint32 n){out.integer(n);};
        auto string=[&](const std::string& value){out.text(value);};
        auto number=[&](double value,double fallback=0){out.real(value,fallback);};
        auto transform=[&](const AnimationTransform& t){number(t.x);number(t.y);number(t.rotation);number(t.scaleX,1);number(t.scaleY,1);number(t.alpha,1);};
        auto rig=pose.getRig();integer(rig->getBoneCount());for(uint32 i=0;i<rig->getBoneCount();++i)transform(pose.getLocalTransform(i));
        integer(rig->getBindingCount());for(uint32 i=0;i<rig->getBindingCount();++i)transform(pose.getBindingLocalTransform(i));
        const auto& meta=pose.getMetadata();integer(meta.variables.size());
        for(const auto& item:meta.variables) {
            string(item.object);string(item.name);out.byte(item.value.index());
            if(auto* value=std::get_if<int>(&item.value)){out.signedInteger(*value);}
            else if(auto* value=std::get_if<double>(&item.value))number(*value);else string(std::get<std::string>(item.value));
        }
        integer(meta.tags.size());for(const auto& item:meta.tags){string(item.object);integer(item.tags.size());for(const auto& tag:item.tags)string(tag);}
        return out.size();
    }
    static std::shared_ptr<AnimationPose> readPose(IDeserializer* reader,std::shared_ptr<const AnimationRig> rig) {
        auto result=std::make_shared<AnimationPose>(rig);SnapshotReader in(reader);
        auto count=[&]{auto n=reader->deserialize_uint();if(n>1000000)throw std::runtime_error("Transition pose count too large");return n;};
        auto string=[&]{return in.text();};
        auto number=[&](double fallback=0){double n=in.real(fallback);if(!std::isfinite(n))throw std::runtime_error("Invalid transition pose value");return n;};
        auto transform=[&]{AnimationTransform t;t.x=number();t.y=number();t.rotation=number();t.scaleX=number(1);t.scaleY=number(1);t.alpha=number(1);return t;};
        if(count()!=rig->getBoneCount())throw std::runtime_error("Transition bone count mismatch");
        for(uint32 i=0;i<rig->getBoneCount();++i)result->setLocalTransform(i,transform());
        if(count()!=rig->getBindingCount())throw std::runtime_error("Transition binding count mismatch");
        for(uint32 i=0;i<rig->getBindingCount();++i)result->setBindingLocalTransform(i,transform());
        AnimationMetadata meta;
        for(auto n=count();n;--n) {
            AnimationVariable item;item.object=string();item.name=string();const auto type=reader->deserialize_1u();
            if(type==0)item.value=int(in.signedInteger());else if(type==1)item.value=number();else if(type==2)item.value=string();else throw std::runtime_error("Invalid transition variable type");
            meta.variables.push_back(std::move(item));
        }
        for(auto n=count();n;--n){AnimationTagSet item;item.object=string();for(auto tags=count();tags;--tags)item.tags.push_back(string());meta.tags.push_back(std::move(item));}
        result->setMetadata(std::move(meta));return result;
    }
    static uint32 encode(const Sprite& s,ISerializer* writer,bool emit) {
        const auto state=capture(s);SnapshotWriter out(writer,emit);uint64_t nested=0;
        if(!out.flag(state.asset!=nullptr))return out.size();
        if(emit)writer->serialize_obj(state.asset);else nested+=writer->sizeof_obj(state.asset);
        auto str=[&](const std::string& v){out.text(v);};
        auto integer=[&](uint32 v){out.integer(v);};
        auto number=[&](double v,double fallback=0){out.real(v,fallback);};
        str(state.entity);str(state.clip);number(state.seconds);
        out.floating(state.scaleX,1);out.floating(state.scaleY,1);
        out.byte((state.paused?1:0)|(state.finished?2:0)|(state.events?4:0)|(state.pose?8:0)|(state.blending?16:0));
        str(state.blendTarget);number(state.blendDuration);number(state.blendElapsed);number(state.blendProgress);
        integer(state.maps.size());for(const auto& name:state.maps)str(name);
        if(state.pose) {
            str(state.reference);out.byte(state.source);out.byte(state.debug);
            out.byte((state.transitioning?1:0)|(state.transitionCompleted?2:0)|(state.transitionSnapshot?4:0));
            str(state.transitionSource);number(state.transitionTime);number(state.transitionDuration);number(state.transitionElapsed);
            if(state.transitionSnapshot)nested+=encodePose(*state.transitionSnapshot,writer,emit);
            integer(state.overrides.size());for(const auto& item:state.overrides){integer(item.first);const auto& t=item.second;number(t.x);number(t.y);number(t.rotation);number(t.scaleX,1);number(t.scaleY,1);number(t.alpha,1);}
        }
        if(state.pose) {
            integer(state.nextModifier);integer(state.revision>>32);integer(state.revision);
            integer(state.ik.size());
            for(const auto& item:state.ik) {
                integer(item.id);out.signedInteger(item.order);out.flag(item.enabled);str(item.error);
                const auto& c=item.config;integer(c.root);integer(c.middle);integer(c.tip);
                out.byte(c.space);out.flag(c.bendDirection==1);out.byte(c.stretch);out.flag(c.matchOrientation);
                const AnimationTwoBoneIK defaults;
                for(auto member:{&AnimationTwoBoneIK::rootLength,&AnimationTwoBoneIK::middleLength,&AnimationTwoBoneIK::targetX,&AnimationTwoBoneIK::targetY,&AnimationTwoBoneIK::influence,&AnimationTwoBoneIK::targetRotation,&AnimationTwoBoneIK::rootMin,&AnimationTwoBoneIK::rootMax,&AnimationTwoBoneIK::middleMin,&AnimationTwoBoneIK::middleMax})number(c.*member,defaults.*member);
                const auto& r=item.result;number(r.reachError);
                out.byte((r.reachable?1:0)|(r.clamped?2:0)|(r.limited?4:0)|(r.stretched?8:0));
            }
            integer(state.nextDrawable);integer(state.artwork.size());
            for(const auto& item:state.artwork) {
                integer(item.id);const auto& o=item.options;integer(o.bone);
                out.byte(o.placement);out.signedInteger(o.order);out.byte(o.strokeSpace);out.flag(item.enabled);out.flag(o.bounds.uncullable);
                str(o.slot);str(item.error);for(double value:{o.bounds.left,o.bounds.top,o.bounds.right,o.bounds.bottom})number(value);
#ifndef PDG_NO_GUI
                if(emit)serializeDrawing(item.drawing.get(),writer);else nested+=drawingSerializedSize(item.drawing.get(),writer);
#endif
            }
        }
		if(uint64_t(nested)+out.size()>UINT32_MAX)throw std::overflow_error("Imported animation record is too large");
		return uint32(nested+out.size());
    }
#endif
public:
#include "sprite-rig-snapshot.inc"
    static void validate(const Sprite& sprite) {
#ifdef PDG_SPRITER_SUPPORT
        capture(sprite);
#endif
    }
    static uint32 size(const Sprite& sprite,ISerializer* writer) {
#ifdef PDG_SPRITER_SUPPORT
        return encode(sprite,writer,false);
#else
        return writer->sizeof_bool(false);
#endif
    }
    static void write(const Sprite& sprite,ISerializer* writer) {
#ifdef PDG_SPRITER_SUPPORT
        encode(sprite,writer,true);
#else
        writer->serialize_bool(false);
#endif
    }
    static void clone(const Sprite& source,Sprite& destination) {
#ifdef PDG_SPRITER_SUPPORT
        if(source.mEntityInstance)configure(destination,capture(source));
#endif
    }
    static void read(Sprite& sprite,IDeserializer* reader) {
        SnapshotReader in(reader);const bool present=in.flag();
#ifdef PDG_SPRITER_SUPPORT
        State state;
        if(present) {
            SpriterSnapshotAsset::registerType();auto* object=reader->deserialize_obj();auto* asset=dynamic_cast<SpriterSnapshotAsset*>(object);
            if(!asset){if(object)object->release();throw std::runtime_error("Missing imported animation asset");}
            const auto retained=std::shared_ptr<SpriterSnapshotAsset>(asset,[](SpriterSnapshotAsset* p){p->release();});
            state.asset=asset;state.model=asset->model();
            auto str=[&]{return in.text();};
            auto number=[&](double fallback=0){double value=in.real(fallback);if(!std::isfinite(value))throw std::runtime_error("Nonfinite imported animation value");return value;};
            state.entity=str();state.clip=str();state.seconds=number();
            state.scaleX=in.floating(1);state.scaleY=in.floating(1);
            const auto flags=reader->deserialize_1u();
            if(flags>31||state.seconds<0||!std::isfinite(state.seconds*1000.)||!std::isfinite(state.scaleX)||!std::isfinite(state.scaleY))throw std::runtime_error("Invalid imported playback state");
            state.paused=flags&1;state.finished=flags&2;state.events=flags&4;state.pose=flags&8;state.blending=flags&16;
            state.blendTarget=str();state.blendDuration=number();state.blendElapsed=number();state.blendProgress=number();
            if(state.blendDuration<0||state.blendElapsed<0||state.blendProgress<0||state.blendProgress>1||
               !std::isfinite(state.blendDuration*1000.)||!std::isfinite(state.blendElapsed*1000.))throw std::runtime_error("Invalid blend state");
            auto count=reader->deserialize_uint();if(count>1000000)throw std::runtime_error("Too many character maps");
            while(count--)state.maps.push_back(str());
            if(state.pose) {
                state.reference=str();state.source=reader->deserialize_1u();state.debug=reader->deserialize_1u();
                if(state.source>animationSource_Procedural||state.debug>animationDebug_All)throw std::runtime_error("Invalid imported pose mode");
                auto transition=reader->deserialize_1u();if(transition>7||((transition&1)&&(transition&2))||((transition&4)&&!(transition&1)))throw std::runtime_error("Invalid transition flags");
                state.transitioning=transition&1;state.transitionCompleted=transition&2;state.transitionSource=str();
                state.transitionTime=number();state.transitionDuration=number();state.transitionElapsed=number();
                if(state.transitionTime<0||state.transitionDuration<0||state.transitionElapsed<0||state.transitionElapsed>state.transitionDuration||
                   (state.transitioning&&state.transitionDuration==0))throw std::runtime_error("Invalid transition timing");
                if(transition&4) {
                    auto catalog=static_cast<PDGFileFactory*>(state.model->getFileFactory())->rigCatalog();auto found=catalog->entities.find(state.entity);
                    if(found==catalog->entities.end())throw std::runtime_error("Missing transition entity");
                    state.transitionSnapshot=readPose(reader,found->second->referenceRig(*state.model,state.reference));
                }
                count=reader->deserialize_uint();if(count>1000000)throw std::runtime_error("Too many bone overrides");
                while(count--){auto id=reader->deserialize_uint();AnimationTransform t;t.x=number();t.y=number();t.rotation=number();t.scaleX=number(1);t.scaleY=number(1);t.alpha=number(1);if(!t.isValid()||!state.overrides.emplace(id,t).second)throw std::runtime_error("Invalid bone override");}
                state.nextModifier=reader->deserialize_uint();const uint64_t high=reader->deserialize_uint(),low=reader->deserialize_uint();state.revision=(high<<32)|low;
                count=reader->deserialize_uint();if(count>1000000)throw std::runtime_error("Too many authored IK controllers");
                std::set<uint32> ids;
                auto flag=[&]{return in.flag();};
                while(count--) {
                    IK item;item.id=reader->deserialize_uint();
                    if(!item.id||(state.nextModifier&&item.id>=state.nextModifier)||!ids.insert(item.id).second)throw std::runtime_error("Invalid authored modifier ID");
                    item.order=in.signedInteger();item.enabled=flag();item.error=str();auto& c=item.config;
                    c.root=reader->deserialize_uint();c.middle=reader->deserialize_uint();c.tip=reader->deserialize_uint();
                    c.space=reader->deserialize_1u();c.bendDirection=flag()?1:-1;c.stretch=reader->deserialize_1u();c.matchOrientation=flag();
                    const AnimationTwoBoneIK defaults;
                    for(auto member:{&AnimationTwoBoneIK::rootLength,&AnimationTwoBoneIK::middleLength,&AnimationTwoBoneIK::targetX,&AnimationTwoBoneIK::targetY,&AnimationTwoBoneIK::influence,&AnimationTwoBoneIK::targetRotation,&AnimationTwoBoneIK::rootMin,&AnimationTwoBoneIK::rootMax,&AnimationTwoBoneIK::middleMin,&AnimationTwoBoneIK::middleMax})c.*member=number(defaults.*member);
                    auto& r=item.result;r.reachError=number();auto bits=reader->deserialize_1u();if(bits>15||r.reachError<0)throw std::runtime_error("Invalid authored IK result");
                    r.reachable=bits&1;r.clamped=bits&2;r.limited=bits&4;r.stretched=bits&8;state.ik.push_back(std::move(item));
                }
                state.nextDrawable=reader->deserialize_uint();count=reader->deserialize_uint();if(count>1000000)throw std::runtime_error("Too many authored drawables");ids.clear();
                while(count--) {
                    Artwork item;item.id=reader->deserialize_uint();
                    if(!item.id||(state.nextDrawable&&item.id>=state.nextDrawable)||!ids.insert(item.id).second)throw std::runtime_error("Invalid drawable ID");
                    auto& o=item.options;o.bone=reader->deserialize_uint();o.placement=reader->deserialize_1u();o.order=in.signedInteger();o.strokeSpace=reader->deserialize_1u();
                    item.enabled=flag();o.bounds.uncullable=flag();o.slot=str();item.error=str();
                    for(auto* v:{&o.bounds.left,&o.bounds.top,&o.bounds.right,&o.bounds.bottom})*v=number();
#ifndef PDG_NO_GUI
                    item.drawing=deserializeDrawing(reader);if(!item.drawing)throw std::runtime_error("Missing authored Drawing");
#else
                    throw std::runtime_error("Authored Drawing snapshots require GUI support");
#endif
                    state.artwork.push_back(std::move(item));
                }
            }
        }
        configure(sprite,state);
#else
        if(present)throw std::runtime_error("Imported animation snapshots require Spriter support");
#endif
    }
    static uint32 bindingSize(const Part& p,ISerializer* writer) {
#ifdef PDG_SPRITER_SUPPORT
        if(p.hasCurrentRig())return 1+writer->sizeof_str(bindingName(p).c_str());
#endif
        return 1;
    }
#ifdef PDG_SPRITER_SUPPORT
    static std::string bindingName(const Part& p) {
        if(p.mSocket!=animation_NoSocket)return p.mRig->getSocket(p.mSocket).name;
        if(p.mBinding!=animation_NoBinding)return p.mRig->getBinding(p.mBinding).name;
        return p.mRig->getBone(p.mBone).name;
    }
#endif
    static void writeBinding(const Part& p,ISerializer* writer) {
#ifdef PDG_SPRITER_SUPPORT
        if(p.hasCurrentRig()) {
            writer->serialize_1u(p.mSocket!=animation_NoSocket?3:p.mBinding!=animation_NoBinding?2:1);
            writer->serialize_string(bindingName(p));return;
        }
#endif
        writer->serialize_1u(0);
    }
    static void readBinding(Part& p,IDeserializer* reader) {
        const auto type=reader->deserialize_1u();if(!type)return;
#ifdef PDG_SPRITER_SUPPORT
        if(type>3||reader->deserialize_strGetLen()>1000000)throw std::runtime_error("Invalid authored Part binding");
        std::string name;reader->deserialize_string(name);auto rig=p.mSprite->getAnimationRig();
        if(!rig)throw std::runtime_error("Authored Part binding requires an enabled rig");
        if(type==1){const auto bone=rig->findBone(name);if(bone==boneId_None)throw std::runtime_error("Unknown saved bone binding: "+name);p.bindToBone(bone);}
        else if(type==2)p.bindToAnimationBinding(name);else p.bindToAnimationSocket(name);
#else
        throw std::runtime_error("Authored Part bindings require Spriter support");
#endif
    }
};
