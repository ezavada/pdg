#ifndef PDG_SPRITER_POSE_H_INCLUDED
#define PDG_SPRITER_POSE_H_INCLUDED
#include "pdg/sys/animationpose.h"
#include "pdg/sys/animationcontroller.h"
#include <map>
#include <set>

namespace SpriterEngine {
class SpriterFileDocumentWrapper;
class SpriterModel;
class EntityInstance;
class UniversalObjectInterface;
}
namespace pdg {
// PDG-owned metadata gathered from the same document used by Spriter's loader.
// The first adapter deliberately requires all spatial tracks to retain their
// type, presence and parent across every mainline key and clip.
struct SpriterRigSchema {
    struct Trigger {std::string name;double seconds=0;};
    struct TriggerClip {double duration=0;bool looping=false;std::vector<Trigger> keys;};
    std::map<std::string,TriggerClip> triggers;
    struct Object { std::string name, parent, type; };
    int entityIndex = 0;
    uint64_t revision = 1;
    std::string entityName, error;
    struct Variable { std::string object, name, type; };
    std::vector<Variable> variables;
    std::vector<std::string> tagNames;
    std::map<std::string, std::set<std::string>> tagScopes;
    std::vector<Object> objects;
    std::set<std::string> boxNames; // Independent of fixed-hierarchy pose support.
    std::vector<std::string> clips;
    std::map<std::string, std::shared_ptr<const AnimationRig>> referenceRigs;
    std::map<std::string, std::pair<double, double>> imageSizes;
    std::shared_ptr<const AnimationRig> referenceRig(SpriterEngine::SpriterModel& model, const std::string& referenceClip);
};
struct SpriterRigCatalog {
    std::map<std::string, std::shared_ptr<SpriterRigSchema>> entities;
    void read(SpriterEngine::SpriterFileDocumentWrapper& document, const std::string& sourcePath = {});
};

// This adapter adds no playback clock. It reads the current evaluator's local
// sampling stage and publishes one pose back to its existing render/query objects.
class SpriterPoseAdapter {
    friend class SpriteAnimationSnapshot;
public:
    SpriterPoseAdapter(SpriterEngine::EntityInstance& entity, std::shared_ptr<SpriterRigSchema> schema,
        std::shared_ptr<const AnimationRig> rig);
    const AnimationPose& pose() const { return mFinal; }
    void evaluate(const std::string& blendTarget, double blendRatio, const AnimationTransform& root, AnimationPipeline* pipeline = nullptr, double deltaSeconds = 0);
    void setBoneOverride(AnimationBoneId id, const AnimationTransform& transform, const AnimationTransform& root);
    void clearBoneOverrides();
    void publish(AnimationPose final, const AnimationTransform& root);
    void recover(double durationSeconds);
    void beginTransition(SpriterEngine::SpriterModel& model, const std::string& sourceClip, double sourceSeconds, double durationSeconds, bool snapshotSource);
    void cancelTransition();
    void completeInstantTransition() { cancelTransition(); mTransitionCompleted=true; }
    bool isTransitioning() const { return mTransitionActive; }
    double transitionProgress() const { return mTransitionDuration > 0 ? mTransitionElapsed / mTransitionDuration : (mTransitionCompleted ? 1 : 0); }
    static double normalizedTime(SpriterEngine::EntityInstance& entity, const SpriterRigSchema& schema, const std::string& clip, double seconds);
    static AnimationPose sample(SpriterEngine::SpriterModel& model, const SpriterRigSchema& schema,
        std::shared_ptr<const AnimationRig> rig, const std::string& clip, double timeSeconds);
private:
    static AnimationPose readLocal(SpriterEngine::EntityInstance& entity, std::shared_ptr<const AnimationRig> rig);
    void validateWorld(const AnimationPose& pose, const AnimationTransform& root) const;
    SpriterEngine::EntityInstance& mEntity;
    std::shared_ptr<SpriterRigSchema> mSchema;
    AnimationPose mBase, mFinal;
    SpriterEngine::SpriterModel* mTransitionModel = nullptr;
    std::unique_ptr<AnimationPose> mTransitionSnapshot;
    std::string mTransitionSource;
    double mTransitionTime = 0, mTransitionDuration = 0, mTransitionElapsed = 0;
    bool mTransitionActive = false, mTransitionCompleted = false;
    std::map<AnimationBoneId, AnimationTransform> mOverrides;
};
}
#endif
