#include "pdg_spriter_pose.h"
// Match sprite.h's guard for overload-hiding declarations in the unmodified
// SpriterPlusPlus headers. Restore diagnostics before compiling PDG's adapter.
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverloaded-virtual"
#endif
#include "spriterengine/override/spriterfiledocumentwrapper.h"
#include "spriterengine/override/spriterfileelementwrapper.h"
#include "spriterengine/override/spriterfileattributewrapper.h"
#include "spriterengine/model/spritermodel.h"
#include "spriterengine/entity/entityinstance.h"
#include "spriterengine/override/imagefile.h"
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#include <algorithm>
#include <atomic>
#include <cmath>
#include <set>
#include <stdexcept>

namespace pdg {
namespace {
using Element = SpriterEngine::SpriterFileElementWrapper;
std::string stringAttribute(Element* e, const char* name, const std::string& fallback = {}) {
    auto* a = e->getFirstAttribute(name);
    return a->isValid() ? a->getStringValue() : fallback;
}
int integerAttribute(Element* e, const char* name, int fallback = -1) {
    auto* a = e->getFirstAttribute(name);
    return a->isValid() ? a->getIntValue() : fallback;
}
void require(bool condition, const std::string& reason) { if (!condition) throw std::invalid_argument(reason); }
AnimationTransform readTransform(SpriterEngine::UniversalObjectInterface* object) {
    require(object != nullptr, "Missing evaluated rig object");
    const auto p = object->getPosition(), s = object->getScale();
    AnimationTransform result{p.x, p.y, object->getAngle(), s.x, s.y, object->getAlpha()};
    require(result.isValid(), "Nonfinite or invalid sampled animation transform");
    return result;
}
void writeTransform(SpriterEngine::UniversalObjectInterface* object, const AnimationTransform& value) {
    object->setPosition({value.x, value.y}); object->setAngle(value.rotation);
    object->setScale({value.scaleX, value.scaleY}); object->setAlpha(value.alpha);
}
void readVariables(Element* parent, const std::string& object, SpriterRigSchema& schema) {
    auto* definitions = parent->getFirstChildElement("var_defs");
    if (!definitions->isValid()) return;
    std::set<std::string> names;
    int id = 0;
    for (auto* definition = definitions->getFirstChildElement("i"); definition->isValid(); definition->advanceToNextSiblingElementOfSameName()) {
        const auto name = stringAttribute(definition, "name"), type = stringAttribute(definition, "type");
        require(!name.empty() && names.insert(name).second, "Variable names must be unique and nonempty");
        require(type == "int" || type == "float" || type == "string", "Unsupported variable type: " + type);
        require(integerAttribute(definition, "id") == id++, "Variable IDs must follow evaluator index order");
        require(definition->getFirstAttribute("default")->isValid(), "Variable default is required");
        schema.variables.push_back({object, name, type});
    }
}
void readTagScope(Element* parent, const std::string& object, const std::string& clip, SpriterRigSchema& schema) {
    auto* meta = parent->getFirstChildElement("meta");
    if (meta->isValid() && meta->getFirstChildElement("tagline")->isValid()) schema.tagScopes[clip].insert(object);
}
AnimationMetadata readMetadata(SpriterEngine::EntityInstance& entity, const SpriterRigSchema& schema, const std::string& clip) {
    AnimationMetadata result;
    for (const auto& definition : schema.variables) {
        auto* variable = entity.getVariable(definition.object, definition.name);
        require(variable != nullptr, "Missing evaluated animation variable");
        AnimationVariable value{definition.object, definition.name, 0};
        if (definition.type == "float") value.value = variable->getRealValue();
        else if (definition.type == "string") value.value = variable->getStringValue();
        else value.value = variable->getIntValue();
        result.variables.push_back(std::move(value));
    }
    std::vector<std::string> scopes{std::string()};
    for (const auto& object : schema.objects) scopes.push_back(object.name);
    const auto authored = schema.tagScopes.find(clip);
    for (const auto& scope : scopes) {
        AnimationTagSet group{scope, {}};
        // Spriter keeps an old tag set if a newly selected clip has no tag
        // timeline. Missing tracks have explicitly empty published tags.
        if (authored != schema.tagScopes.end() && authored->second.count(scope))
            for (const auto& tag : schema.tagNames) if (entity.tagIsActive(scope, tag)) group.tags.push_back(tag);
        result.tags.push_back(std::move(group));
    }
    return result;
}
void readTriggers(Element* entity,SpriterRigSchema& schema){
    for(auto* clip=entity->getFirstChildElement("animation");clip->isValid();clip->advanceToNextSiblingElementOfSameName()){
        SpriterRigSchema::TriggerClip track;
        auto* length=clip->getFirstAttribute("length");require(length->isValid(),"Missing trigger clip length");
        track.duration=length->getRealValue()/1000.0;
        require(std::isfinite(track.duration)&&track.duration>0,"Invalid trigger clip length");
        track.looping=stringAttribute(clip,"looping","true")!="false";
        for(auto* line=clip->getFirstChildElement("eventline");line->isValid();line->advanceToNextSiblingElementOfSameName()){
            const auto name=stringAttribute(line,"name");require(!name.empty(),"Empty trigger name");
            for(auto* key=line->getFirstChildElement("key");key->isValid();key->advanceToNextSiblingElementOfSameName()){
                auto* time=key->getFirstAttribute("time");const double seconds=time->isValid()?time->getRealValue()/1000.0:0;
                require(std::isfinite(seconds)&&seconds>=0&&seconds<=track.duration,"Invalid trigger timestamp");
                track.keys.push_back({name,seconds});
            }
        }
        std::stable_sort(track.keys.begin(),track.keys.end(),[](const auto& a,const auto& b){return a.seconds<b.seconds;});
        schema.triggers.emplace(stringAttribute(clip,"name"),std::move(track));
    }
}
void readSchema(Element* entity, SpriterRigSchema& schema) {
    readVariables(entity, "", schema);
    for (auto* object = entity->getFirstChildElement("obj_info"); object->isValid(); object->advanceToNextSiblingElementOfSameName())
        readVariables(object, stringAttribute(object, "name"), schema);
    std::map<std::string, std::pair<std::string, std::string>> hierarchy;
    bool first = true;
    std::set<std::string> clipNames;
    for (auto* clip = entity->getFirstChildElement("animation"); clip->isValid(); clip->advanceToNextSiblingElementOfSameName()) {
        const auto clipName = stringAttribute(clip, "name");
        require(!clipName.empty() && clipNames.insert(clipName).second, "Clip names must be unique and nonempty");
        schema.clips.push_back(clipName);
        readTagScope(clip, "", clipName, schema);
        auto* length = clip->getFirstAttribute("length");
        require(length->isValid() && std::isfinite(length->getRealValue()) && length->getRealValue() > 0,
            "Pose editing requires positive, finite clip lengths");
        std::vector<SpriterRigSchema::Object> timelines;
        std::vector<int> keyCounts;
        std::set<std::string> names;
        for (auto* timeline = clip->getFirstChildElement("timeline"); timeline->isValid(); timeline->advanceToNextSiblingElementOfSameName()) {
            SpriterRigSchema::Object object{stringAttribute(timeline, "name"), {}, stringAttribute(timeline, "object_type", "sprite")};
            require(!object.name.empty() && names.insert(object.name).second, "Spatial timeline names must be unique and nonempty");
            require(object.type == "bone" || object.type == "sprite" || object.type == "point" || object.type == "box",
                "Unsupported pose object type: " + object.type);
            require(integerAttribute(timeline, "id") == static_cast<int>(timelines.size()), "Timeline IDs must follow evaluator index order");
            int keys = 0;
            for (auto* key = timeline->getFirstChildElement("key"); key->isValid(); key->advanceToNextSiblingElementOfSameName()) {
                require(integerAttribute(key, "id") == keys++, "Timeline key IDs must follow evaluator index order");
                auto* spatial = key->getFirstChildElement(object.type == "bone" ? "bone" : "object");
                require(spatial->isValid(), "Missing spatial timeline key");
                for (const char* field : {"x", "y", "angle", "scale_x", "scale_y", "a"}) {
                    auto* value = spatial->getFirstAttribute(field);
                    require(!value->isValid() || std::isfinite(value->getRealValue()), "Nonfinite authored transform");
                }
            }
            require(keys > 0, "Empty spatial timeline");
            readTagScope(timeline, object.name, clipName, schema);
            timelines.push_back(object); keyCounts.push_back(keys);
        }
        auto* mainline = clip->getFirstChildElement("mainline");
        require(mainline->isValid(), "Missing mainline");
        bool haveKey = false;
        for (auto* key = mainline->getFirstChildElement("key"); key->isValid(); key->advanceToNextSiblingElementOfSameName()) {
            haveKey = true;
            std::map<std::string, std::pair<std::string, std::string>> current;
            std::vector<std::string> boneRefs;
            bool seenObject = false;
            for (auto* ref = key->getFirstChildElement(); ref->isValid(); ref->advanceToNextSiblingElement()) {
                const bool bone = ref->getName() == "bone_ref";
                require(bone || ref->getName() == "object_ref", "Unsupported mainline reference");
                const int timeline = integerAttribute(ref, "timeline"), index = integerAttribute(ref, "key");
                require(timeline >= 0 && timeline < static_cast<int>(timelines.size()), "Invalid mainline timeline");
                require(index >= 0 && index < keyCounts[timeline], "Invalid mainline key");
                auto object = timelines[timeline];
                require(bone == (object.type == "bone"), "Mainline reference type differs from its timeline");
                const int parent = integerAttribute(ref, "parent");
                require(parent == -1 || (parent >= 0 && parent < static_cast<int>(boneRefs.size())), "Parent must be an earlier bone reference");
                if (parent >= 0) object.parent = boneRefs[parent];
                if (bone) {
                    require(!seenObject && integerAttribute(ref, "id") == static_cast<int>(boneRefs.size()), "Bone references must follow evaluator parent order");
                    boneRefs.push_back(object.name);
                } else seenObject = true;
                require(current.emplace(object.name, std::make_pair(object.type, object.parent)).second, "Duplicate mainline object");
            }
            require(current.size() == timelines.size(), "Inactive spatial tracks are not supported by the fixed-hierarchy pose adapter");
            if (first) {
                hierarchy = current;
                for (auto object : timelines) { object.parent = hierarchy.at(object.name).second; schema.objects.push_back(object); }
                first = false;
            } else require(current == hierarchy, "Changing spatial hierarchy, type or track presence is not supported for pose editing");
        }
        require(haveKey, "Empty mainline");
    }
    require(!schema.clips.empty(), "Entity has no clips");
    require(std::any_of(schema.objects.begin(), schema.objects.end(), [](const auto& o) { return o.type == "bone"; }), "Entity has no skeletal bones");
}
SpriterEngine::AnimationInstance* animation(SpriterEngine::EntityInstance& entity, int entityIndex, const std::string& clip) {
    auto* data = entity.getEntity(entityIndex);
    auto* result = data ? data->getAnimation(clip) : nullptr;
    require(result != nullptr, "Animation is not available in this rig: " + clip);
    return result;
}
}

void SpriterRigCatalog::read(SpriterEngine::SpriterFileDocumentWrapper& document, const std::string& sourcePath) {
    entities.clear();
    static std::atomic<uint64_t> nextRevision{1};
    auto* data = document.getFirstChildElement("spriter_data");
    if (!data->isValid()) return;
    std::map<std::string, std::pair<double, double>> imageSizes;
    const auto slash = sourcePath.find_last_of("/\\");
    const auto directory = slash == std::string::npos ? std::string() : sourcePath.substr(0,slash+1);
    for (auto* folder = data->getFirstChildElement("folder"); folder->isValid(); folder->advanceToNextSiblingElementOfSameName())
        for (auto* file = folder->getFirstChildElement("file"); file->isValid(); file->advanceToNextSiblingElementOfSameName()) {
            auto* w = file->getFirstAttribute("width"); auto* h = file->getFirstAttribute("height");
            if (w->isValid() && h->isValid()) imageSizes[directory+stringAttribute(file, "name")] = {w->getRealValue(), h->getRealValue()};
        }
    std::vector<std::string> tagNames;
    auto* tags = data->getFirstChildElement("tag_list");
    if (tags->isValid()) for (auto* tag = tags->getFirstChildElement("i"); tag->isValid(); tag->advanceToNextSiblingElementOfSameName())
        tagNames.push_back(stringAttribute(tag, "name"));
    int index = 0;
    for (auto* entity = data->getFirstChildElement("entity"); entity->isValid(); entity->advanceToNextSiblingElementOfSameName(), ++index) {
        auto schema = std::make_shared<SpriterRigSchema>();
        schema->imageSizes = imageSizes;
        schema->entityIndex = index; schema->entityName = stringAttribute(entity, "name");
        schema->revision = nextRevision++;
        schema->tagNames = tagNames;
        for (auto* clip=entity->getFirstChildElement("animation"); clip->isValid(); clip->advanceToNextSiblingElementOfSameName())
            for (auto* timeline=clip->getFirstChildElement("timeline"); timeline->isValid(); timeline->advanceToNextSiblingElementOfSameName())
                if (stringAttribute(timeline,"object_type")=="box") {
                    const auto name=stringAttribute(timeline,"name");
                    if (!name.empty()) schema->boxNames.insert(name);
                }
        try { readTriggers(entity,*schema);readSchema(entity, *schema); }
        catch (const std::exception& error) { schema->error = error.what(); }
        if (!entities.emplace(schema->entityName, schema).second) entities.at(schema->entityName)->error = "Duplicate entity name";
    }
}

std::shared_ptr<const AnimationRig> SpriterRigSchema::referenceRig(SpriterEngine::SpriterModel& model, const std::string& referenceClip) {
    require(error.empty(), error);
    require(std::find(clips.begin(), clips.end(), referenceClip) != clips.end(), "Unknown reference clip: " + referenceClip);
    auto found = referenceRigs.find(referenceClip);
    if (found != referenceRigs.end()) return found->second;
    std::unique_ptr<SpriterEngine::EntityInstance> evaluator(model.getNewEntityInstance(entityName));
    require(evaluator != nullptr, "Cannot create reference evaluator");
    auto* clip = animation(*evaluator, entityIndex, referenceClip);
    clip->findCurrentKeys(0, false); clip->processRefKeys(0);
    std::vector<AnimationBone> bones;
    std::map<std::string, AnimationBoneId> ids;
    for (const auto& object : objects) if (object.type == "bone") {
        ids.emplace(object.name, static_cast<AnimationBoneId>(bones.size()));
        bones.push_back({object.name, animation_NoBone, readTransform(evaluator->getObjectInstance(object.name)), 0});
    }
    std::vector<AnimationBinding> bindings;
    std::vector<AnimationSocket> sockets;
    for (const auto& object : objects) {
        const auto parent = object.parent.empty() ? animation_NoBone : ids.at(object.parent);
        if (object.type == "bone") bones[ids.at(object.name)].parent = parent;
        else {
            const auto kind = object.type == "point" ? animationBinding_Point
                : object.type == "box" ? animationBinding_Box : animationBinding_Image;
            const auto local = readTransform(evaluator->getObjectInstance(object.name));
            if (kind == animationBinding_Point)
                sockets.push_back({object.name, parent, local, static_cast<AnimationBindingId>(bindings.size())});
            bindings.push_back({object.name, parent, kind, local});
            if (kind == animationBinding_Image) {
                auto* evaluated = evaluator->getObjectInstance(object.name);
                auto* image = evaluated->getImage();
                const auto found = image ? imageSizes.find(image->path()) : imageSizes.end();
                if (found != imageSizes.end()) {
                    auto& binding = bindings.back(); const auto pivot = evaluated->getPivot();
                    binding.hasImageBounds = true;
                    binding.imageWidth = found->second.first; binding.imageHeight = found->second.second;
                    binding.pivotX = pivot.x; binding.pivotY = pivot.y;
                }
            }
        }
    }
    // Bone width is display metadata, not an inferred IK length. The caller
    // explicitly chooses this clip at time zero as the reference pose.
    auto rig = AnimationRig::create(std::move(bones), std::move(sockets), revision, std::move(bindings));
    referenceRigs.emplace(referenceClip, rig);
    return rig;
}

SpriterPoseAdapter::SpriterPoseAdapter(SpriterEngine::EntityInstance& entity,
        std::shared_ptr<SpriterRigSchema> schema, std::shared_ptr<const AnimationRig> rig)
    : mEntity(entity), mSchema(std::move(schema)), mBase(rig), mFinal(rig) {}
AnimationPose SpriterPoseAdapter::readLocal(SpriterEngine::EntityInstance& entity, std::shared_ptr<const AnimationRig> rig) {
    AnimationPose pose(rig);
    std::vector<AnimationTransform> transforms;
    transforms.reserve(rig->getBoneCount());
    for (AnimationBoneId id = 0; id < rig->getBoneCount(); ++id)
        transforms.push_back(readTransform(entity.getObjectInstance(rig->getBone(id).name)));
    pose.setLocalTransforms(transforms);
    for (AnimationBindingId id = 0; id < rig->getBindingCount(); ++id)
        pose.setBindingLocalTransform(id, readTransform(entity.getObjectInstance(rig->getBinding(id).name)));
    return pose;
}
void SpriterPoseAdapter::validateWorld(const AnimationPose& pose, const AnimationTransform& root) const {
    const auto& rig = pose.getRig();
    for (AnimationBoneId id = 0; id < rig->getBoneCount(); ++id) pose.getWorldTransform(id, root);
    for (AnimationBindingId id = 0; id < rig->getBindingCount(); ++id) pose.getWorldBindingTransform(id, root);
}
void SpriterPoseAdapter::evaluate(const std::string& blendTarget, double blendRatio, const AnimationTransform& root, AnimationPipeline* pipeline, double deltaSeconds, const std::function<void(AnimationPose&,bool)>& controls, double simulationDeltaSeconds) {
    auto* source = animation(mEntity, mSchema->entityIndex, mEntity.currentAnimationName());
    source->processRefKeys(source->currentTime());
    if (!blendTarget.empty()) {
        auto* target = animation(mEntity, mSchema->entityIndex, blendTarget);
        target->blendRefKeys(target->currentTime(), blendRatio);
    }
    auto base = readLocal(mEntity, mBase.getRig());
    base.setMetadata(readMetadata(mEntity, *mSchema, !blendTarget.empty() && blendRatio >= 0.5 ? blendTarget : source->getName()));
    if (mTransitionActive) {
        mTransitionTime += deltaSeconds;
        mTransitionElapsed = std::min(mTransitionDuration, mTransitionElapsed + deltaSeconds);
        auto outgoing = mTransitionSnapshot ? mTransitionSnapshot->copy()
            : sample(*mTransitionModel,*mSchema,mBase.getRig(),mTransitionSource,mTransitionTime);
        base = AnimationPose::blend(outgoing,base,transitionProgress());
        if (mTransitionElapsed >= mTransitionDuration) { mTransitionActive=false; mTransitionCompleted=true; mTransitionSnapshot.reset(); }
    }
    auto final = base.copy();
    if (pipeline) final = pipeline->evaluate(base, root, deltaSeconds, mOverrides,controls,simulationDeltaSeconds);
    else for (const auto& override : mOverrides) final.setLocalTransform(override.first, override.second);
    mBase = std::move(base);
    publish(std::move(final),root);
}
void SpriterPoseAdapter::recover(double seconds) {
    if(seconds<=0){cancelTransition();return;}
    mTransitionSnapshot=std::make_unique<AnimationPose>(mFinal.copy());
    mTransitionDuration=seconds;mTransitionElapsed=0;mTransitionTime=0;
    mTransitionActive=true;mTransitionCompleted=false;
}
void SpriterPoseAdapter::publish(AnimationPose final,const AnimationTransform& root) {
    require(final.getRig()==mFinal.getRig(),"Published pose belongs to another rig");
    validateWorld(final, root); // No partial world-pose publication on overflow.
    const auto& rig = final.getRig();
    for (AnimationBoneId id = 0; id < rig->getBoneCount(); ++id)
        writeTransform(mEntity.getObjectInstance(rig->getBone(id).name), final.getWorldTransform(id, root));
    for (AnimationBindingId id = 0; id < rig->getBindingCount(); ++id)
        writeTransform(mEntity.getObjectInstance(rig->getBinding(id).name), final.getWorldBindingTransform(id, root));
    mFinal = std::move(final);
}
void SpriterPoseAdapter::setBoneOverride(AnimationBoneId id, const AnimationTransform& transform, const AnimationTransform& root) {
    auto candidate = mFinal.copy();
    candidate.setLocalTransform(id, transform);
    validateWorld(candidate, root);
    mOverrides[id] = transform;
}
void SpriterPoseAdapter::clearBoneOverrides() { mOverrides.clear(); }
void SpriterPoseAdapter::beginTransition(SpriterEngine::SpriterModel& model, const std::string& sourceClip,
        double sourceSeconds, double durationSeconds, bool snapshotSource) {
    require(std::isfinite(durationSeconds) && durationSeconds > 0, "Transition duration must be positive seconds");
    auto snapshot = snapshotSource || mTransitionActive ? std::make_unique<AnimationPose>(mBase.copy()) : nullptr;
    mTransitionModel=&model; mTransitionSnapshot=std::move(snapshot); mTransitionSource=sourceClip;
    mTransitionTime=sourceSeconds; mTransitionDuration=durationSeconds; mTransitionElapsed=0; mTransitionActive=true; mTransitionCompleted=false;
}
void SpriterPoseAdapter::cancelTransition() {
    mTransitionActive=false; mTransitionCompleted=false; mTransitionSnapshot.reset();mTransitionModel=nullptr;mTransitionSource.clear();
    mTransitionElapsed=mTransitionDuration=mTransitionTime=0;
}
double SpriterPoseAdapter::normalizedTime(SpriterEngine::EntityInstance& entity, const SpriterRigSchema& schema,
        const std::string& clipName,double seconds) {
    require(std::isfinite(seconds),"Animation time must be finite seconds");
    require(std::find(schema.clips.begin(),schema.clips.end(),clipName)!=schema.clips.end(),"Unknown animation clip");
    auto* clip=animation(entity,schema.entityIndex,clipName);const double duration=clip->length()/1000.0;
    require(std::isfinite(duration) && duration>0,"Animation duration must be positive");
    double value=clip->looping()?std::fmod(seconds,duration):std::clamp(seconds,0.0,duration);
    if(value<0)value+=duration;
    return value;
}

AnimationPose SpriterPoseAdapter::sample(SpriterEngine::SpriterModel& model, const SpriterRigSchema& schema,
        std::shared_ptr<const AnimationRig> rig, const std::string& clipName, double timeSeconds) {
    require(std::isfinite(timeSeconds), "Sample time must be finite seconds");
    require(std::find(schema.clips.begin(), schema.clips.end(), clipName) != schema.clips.end(), "Unknown sample clip");
    std::unique_ptr<SpriterEngine::EntityInstance> evaluator(model.getNewEntityInstance(schema.entityName));
    require(evaluator != nullptr, "Cannot create sample evaluator");
    auto* clip = animation(*evaluator, schema.entityIndex, clipName);
    const double seconds = normalizedTime(*evaluator,schema,clipName,timeSeconds);
    // The only public-time conversion; normalization avoids long evaluator wrap loops.
    const double time = seconds * 1000.0;
    clip->findCurrentKeys(time, true);
    const double easedTime = clip->processRefKeys(clip->currentTime());
    clip->processCurrentTimelineKeys(easedTime);
    auto pose = readLocal(*evaluator, std::move(rig));
    pose.setMetadata(readMetadata(*evaluator, schema, clipName));
    return pose;
}
}
