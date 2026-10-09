// Shared native script construction and playback. Included by animated.cpp so
// every existing Animated build lane links the same implementation.
#include <map>
#include <set>
#include <limits>

namespace pdg {
namespace animation_script_detail {
struct ScriptNode {
    enum Kind { Operation, Group, Conditional, Until, Yoyo, Repeat, Gain, Rate, Flip, Invocation, Mark, Jump, Target, Stagger, Emit, Command } kind = Group;
    struct Value { unsigned field; float target; };
    std::vector<Value> values;
    std::vector<std::shared_ptr<ScriptNode>> children;
    AnimationEvaluator evaluator;
    std::map<std::string,std::vector<AnimationEventHandler>> handlers;
    std::weak_ptr<AnimatedBase*> target, troupe;
    std::string name;
    AnimationArguments arguments;
    double seconds = 0, delay = 0;
    float factor = 1;
    EasingFunc easing = linearTween;
    uint8 mode = animationMode_Assign, playback = 0, completion = 0;
    int direction = rotationDirection_AsSpecified, count = 0, dependency = -1;
    uint32 externalDependency=0, requiredClass=0;
};
using ScriptNodePtr = std::shared_ptr<ScriptNode>;
} // namespace animation_script_detail
using animation_script_detail::ScriptNode;
using animation_script_detail::ScriptNodePtr;
namespace {
struct ScriptJump { std::string name; bool restore; double remaining; ScriptExecution* scope; AnimatedBase* target; };
constexpr double scriptInfinity = std::numeric_limits<double>::infinity();

bool scriptCustomEventName(const std::string& name) {
    static const std::set<std::string> reserved={"started","finished","scriptFinished","mark","yoyo","repeat","untilFired","unsupportedOp"};
    return !name.empty() && !reserved.contains(name) && !name.starts_with("eventType_");
}


void scriptNonempty(const ScriptNodePtr& node) {
    if (!node || (node->kind == ScriptNode::Group && node->children.empty()))
        throw std::logic_error("Animation block must not be empty");
}

// Immutable publication copies symbols and evaluators, never property pointers.
ScriptNodePtr cloneScript(const ScriptNodePtr& source) {
    auto result = std::make_shared<ScriptNode>(*source);
    result->children.clear();
    for (const auto& child : source->children) result->children.push_back(cloneScript(child));
    return result;
}

bool scriptCommandNumeric(const ScriptNodePtr& node) {
    return node->name.starts_with("change") || node->name=="fadeTo" || node->name=="fadeIn" ||
        node->name=="fadeOut" || node->name=="zoomTo" || node->name=="zoom";
}
bool scriptReversible(const ScriptNodePtr& node) {
    if(node->kind==ScriptNode::Command) return scriptCommandNumeric(node);
    if (node->kind==ScriptNode::Flip || node->kind==ScriptNode::Mark || node->kind==ScriptNode::Jump || node->kind==ScriptNode::Emit) return false;
    if (node->kind == ScriptNode::Operation)
        for (const auto& value : node->values) if ((value.field >= animationChannel_MovementX && value.field <= animationChannel_StretchingHeight) || value.field==animationChannel_CameraHidden || value.field==animationChannel_CameraTransition) return false;
    if (node->kind == ScriptNode::Repeat && node->count < 0) return false;
    for (const auto& child : node->children) if (!scriptReversible(child)) return false;
    return true;
}

bool scriptNumeric(const ScriptNodePtr& node) {
    if(node->kind==ScriptNode::Command) return scriptCommandNumeric(node);
    if (node->kind==ScriptNode::Flip || node->kind==ScriptNode::Mark || node->kind==ScriptNode::Jump || node->kind==ScriptNode::Emit) return false;
    if (node->kind==ScriptNode::Operation)
        for (const auto& value : node->values) if ((value.field>=animationChannel_MovementX && value.field<=animationChannel_StretchingHeight) || value.field==animationChannel_CameraHidden || value.field==animationChannel_CameraTransition) return false;
    for (const auto& child : node->children) if (!scriptNumeric(child)) return false;
    return true;
}

std::set<unsigned> scriptChannels(const ScriptNodePtr& node, bool skipStopped = false) {
    std::set<unsigned> result;
    if (skipStopped && (node->playback&2)) return result;
    if (node->kind==ScriptNode::Operation) for (auto& value : node->values) result.insert(value.field);
    if (node->kind==ScriptNode::Flip) { result.insert(animationChannel_CenterOffsetX+node->values.at(0).field); result.insert(UINT32_MAX-node->values.at(0).field); }
    for (auto& child : node->children) { auto fields=scriptChannels(child,skipStopped); result.insert(fields.begin(),fields.end()); }
    return result;
}
void scriptValidateParallel(const ScriptNodePtr& node) {
    if (node->kind!=ScriptNode::Group) return;
    for (size_t i=0;i<node->children.size();++i) for (size_t j=0;j<i;++j) {
        bool ordered=false;
        for (int predecessor=node->children[i]->dependency;predecessor>=0;predecessor=node->children.at(predecessor)->dependency)
            if (predecessor==static_cast<int>(j)) {ordered=true;break;}
        if (ordered) continue;
        const auto a=scriptChannels(node->children[i],true),b=scriptChannels(node->children[j],true);
        for (auto field : a) {
            if (b.contains(field) || (field<=animationChannel_Height && b.contains(field+animationChannel_MovementX)) || (field>=animationChannel_MovementX && field<=animationChannel_StretchingHeight && b.contains(field-animationChannel_MovementX)))
                throw std::logic_error("Concurrent script blocks claim the same animation channel; use andThen");
        }
    }
}

double scriptEnvelope(const ScriptNode& node, double time, float begin) {
    if (node.seconds == 0 || time >= node.seconds) return node.factor;
    const double fraction=node.easing(std::max(0.0,time),0,1,node.seconds);
    if (!std::isfinite(fraction)) throw std::runtime_error("Animation envelope easing returned a nonfinite value");
    return begin+(node.factor-begin)*std::clamp(fraction,0.0,1.0);
}

// A fixed normalized grid makes the integral independent of frame partitioning.
double scriptClock(const ScriptNode& node, double time) {
    const double span = std::min(time,node.seconds);
    if (node.seconds == 0) { const double result=time*node.factor; if(!std::isfinite(result)) throw std::invalid_argument("Animation script clock overflow"); return result; }
    constexpr int subdivisions = 512;
    const double width = node.seconds/subdivisions;
    double area = 0;
    const int whole = std::min(subdivisions,static_cast<int>(span/width));
    for (int i=0;i<whole;++i) {
        const double a=i*width,b=(i+1)*width;
        area += width*(scriptEnvelope(node,a,1)+4*scriptEnvelope(node,(a+b)/2,1)+scriptEnvelope(node,b,1))/6;
    }
    const double a=whole*width,b=span;
    if (b>a) area += (b-a)*(scriptEnvelope(node,a,1)+4*scriptEnvelope(node,(a+b)/2,1)+scriptEnvelope(node,b,1))/6;
    const double result=area+std::max(0.0,time-node.seconds)*node.factor;
    if (!std::isfinite(result)) throw std::invalid_argument("Animation script clock overflow");
    return result;
}

} // anonymous namespace

namespace {
struct RegisteredAnimationOperation {
    std::string name;
    std::function<bool(AnimatedBase&,const AnimationArguments&)> apply;
    std::function<double(const AnimationArguments&)> duration;
};
std::vector<RegisteredAnimationOperation>& animationOperations() {
    static std::vector<RegisteredAnimationOperation> operations; return operations;
}
}
void registerAnimationOperation(const std::string& name,
    std::function<bool(AnimatedBase&,const AnimationArguments&)> apply,
    std::function<double(const AnimationArguments&)> duration) {
    animationOperations().push_back({name,std::move(apply),std::move(duration)});
}
bool applyAnimationOperation(AnimatedBase& target,const std::string& name,const AnimationArguments& arguments) {
    for(const auto& operation:animationOperations()) if(operation.name==name && operation.apply(target,arguments)) return true;
    return false;
}
double animationOperationDuration(const std::string& name,const AnimationArguments& arguments) {
#include "animation-operation-durations.inc"
    for(const auto& operation:animationOperations()) if(operation.name==name) {
        try { const double duration=operation.duration(arguments); if(duration!=0) return duration; }
        catch(const std::bad_any_cast&) {}
    }
    return 0;
}

struct ScriptExecution {
    ScriptNodePtr node;
    ScriptExecution* parent=nullptr;
    struct Notification {
        AnimationEventHandler handler;
        std::weak_ptr<AnimatedBase*> target;
        std::string type, scriptName, markName, operationName;
        double elapsed;
        unsigned iteration;
        bool reverse;
    };
    std::vector<Notification> notifications;
    void emit(const std::string& type, AnimatedBase& target) {
        auto* owner=this;
        std::string script;
        for(auto* cursor=this;cursor;cursor=cursor->parent) {
            owner=cursor;
            if(script.empty() && cursor->node->kind==ScriptNode::Group && cursor->node->name.starts_with("@script:") && cursor->node->name!="@script:@stagger") script=cursor->node->name.substr(8);
        }
        for(auto* cursor=this;cursor;cursor=cursor->parent) {
            if(auto found=cursor->node->handlers.find(type);found!=cursor->node->handlers.end())
                for(const auto& handler:found->second) owner->notifications.push_back({handler,target.animationLifetime(),type,script,
                    node->kind==ScriptNode::Mark || node->kind==ScriptNode::Jump?node->name:"",type=="unsupportedOp"?node->name:"",elapsed,static_cast<unsigned>(iteration),reverse});
            if(type=="started" || type=="finished") break;
        }
    }
    struct MarkState {
        std::vector<float> values;
        std::vector<AnimatedBase::Animation> animations;
        std::shared_ptr<ScriptExecution> cursor;
        struct Member { std::weak_ptr<AnimatedBase*> lifetime; std::vector<float> values; std::vector<AnimatedBase::Animation> animations; std::array<double,5> credits{}; };
        std::vector<Member> members;
        std::array<double,5> credits{};
    };
    std::map<std::string, MarkState> marks;
    std::map<AnimatedBase*, std::vector<float>> memberBaselines;
    std::vector<float> memberValues;
    std::shared_ptr<ScriptExecution*> externalLifetime;
    using Publisher=std::function<void(AnimatedBase&,const std::vector<float>&)>;
    AnimatedBase* memberTarget() const {
        const auto lifetime=node->target.lock(), owner=node->troupe.lock();
        if(!lifetime || !*lifetime || !owner || !*owner) return nullptr;
        const auto targets=(*owner)->animationTargets();
        return std::find(targets.begin(),targets.end(),*lifetime)!=targets.end()?*lifetime:nullptr;
    }
    static std::vector<const float*> fields(AnimatedBase& target) { return target.tweenFields(); }
    static uint8 trackFlags(AnimatedBase& target,const AnimatedBase::Animation& a) { return target.animationFlags(a); }
    static void readFlags(AnimatedBase& target,AnimatedBase::Animation& a,uint8 flags) { target.readAnimationFlags(a,flags,true); }
    static void attach(ScriptExecution& execution) {
        if(execution.node->kind==ScriptNode::Target && execution.active && !execution.complete) if(auto* member=execution.memberTarget()) {
            execution.externalLifetime=std::make_shared<ScriptExecution*>(&execution);
            member->mExternalScriptExecutions.push_back(execution.externalLifetime);
        }
    }
    static std::vector<float> readValues(AnimatedBase& target) {
        std::vector<float> values;
        for(auto field:target.tweenFields()) values.push_back(*field);
        values.push_back(target.mFlipX); values.push_back(target.mFlipY); return values;
    }
    ScriptExecution& root() { auto* owner=this; while(owner->parent && !(owner->node->kind==ScriptNode::Group && owner->node->name.starts_with("@script:"))) owner=owner->parent; return *owner; }
    bool findMark(const std::string& name, std::vector<unsigned>& path) const {
        if (node->kind==ScriptNode::Mark && node->name==name) return true;
        for (unsigned i=0;i<children.size();++i) {
            path.push_back(i); if(children[i]->findMark(name,path)) return true; path.pop_back();
        }
        return false;
    }
    void seekMark(const std::vector<unsigned>& path, size_t depth, const std::vector<float>& values) {
        reset(); capture(values);
        if (depth==path.size()) { complete=true; duration=0; return; }
        const unsigned selected=path[depth];
        if (node->kind==ScriptNode::Group) {
            for(unsigned i=0;i<=selected;++i) {
                starts[i]=0; finishes[i]=0;
                if(i<selected) { children[i]->complete=true; children[i]->duration=0; }
            }
            finishes[selected]=scriptInfinity;
        } else if(node->kind==ScriptNode::Conditional) branch=selected;
        children[selected]->seekMark(path,depth+1,values);
        if(node->kind==ScriptNode::Group && children[selected]->complete) finishes[selected]=0;
    }
    void jump(const std::string& name, bool restore, std::vector<float>& values, AnimatedBase& target) {
        std::vector<unsigned> path;
        if (!findMark(name,path)) throw std::invalid_argument("Unknown animation mark: "+name);
        target.mTroupeRateTime.fill(0);
        auto saved=marks;
        const auto found=saved.find(name);
        if(restore && found!=saved.end()) {
            values=found->second.values;
            target.mAnimations=found->second.animations; target.mTroupeRateTime=found->second.credits;
            for(const auto& member:found->second.members) if(auto entry=member.lifetime.lock();entry && *entry) {
                auto* receiver=*entry;
                const auto fields=receiver->tweenFields();
                for(size_t i=0;i<fields.size();++i) *const_cast<float*>(fields[i])=member.values[i];
                const bool beforeX=receiver->mFlipX,beforeY=receiver->mFlipY;
                receiver->mFlipX=member.values[fields.size()]!=0; receiver->mFlipY=member.values[fields.size()+1]!=0;
                if(beforeX!=receiver->mFlipX || beforeY!=receiver->mFlipY) receiver->flipChanged(beforeX!=receiver->mFlipX,beforeY!=receiver->mFlipY);
                receiver->mAnimations=member.animations; receiver->mTroupeRateTime=member.credits; receiver->animationValuesChanged();
            }
            const auto restored=std::make_unique<ScriptExecution>(*found->second.cursor);
            adopt(*restored);
        } else seekMark(path,0,values);
        marks=std::move(saved);
        for(auto* cursor=this;cursor;cursor=cursor->parent) {
            cursor->complete=false; cursor->finished=scriptInfinity;
            if(cursor->parent && cursor->parent->node->kind==ScriptNode::Group) {
                auto& owner=*cursor->parent;
                for(size_t i=0;i<owner.children.size();++i) if(owner.children[i].get()==cursor) owner.finishes[i]=scriptInfinity;
            }
        }
    }
    void adopt(const ScriptExecution& other) {
        auto* owner=parent;
        auto copy=std::make_unique<ScriptExecution>(other);
        node=copy->node; children=std::move(copy->children); history=std::move(copy->history);
        memberBaselines=copy->memberBaselines; memberValues=copy->memberValues;
        baseline=copy->baseline; logical=copy->logical; begin=copy->begin; end=copy->end;
        channels=copy->channels; canceled=copy->canceled; starts=copy->starts; finishes=copy->finishes;
        elapsed=copy->elapsed; duration=copy->duration; born=copy->born; finished=copy->finished;
        id=copy->id; iteration=copy->iteration; branch=copy->branch;
        active=copy->active; complete=copy->complete; paused=copy->paused; stopped=copy->stopped;
        reverse=copy->reverse; completionSent=copy->completionSent;
        lastPollTick=UINT64_MAX; lastPollElapsed=-1; parent=owner;
        for(auto& child:children) child->parent=this;
    }
    std::vector<std::unique_ptr<ScriptExecution>> children, history;
    std::vector<float> baseline, logical, begin, end;
    std::vector<unsigned> channels, canceled;
    std::vector<double> starts, finishes;
    double elapsed=0, duration=0, born=0, finished=scriptInfinity;
    uint32 id=0;
    int iteration=0, branch=-1;
    uint64 lastPollTick=UINT64_MAX;
    double lastPollElapsed=-1;
    bool active=false, complete=false, paused=false, stopped=false, reverse=false, completionSent=false;

    explicit ScriptExecution(ScriptNodePtr definition) : node(std::move(definition)), paused((node->playback&1)!=0), stopped((node->playback&2)!=0) {
        for (const auto& child : node->children) { children.push_back(std::make_unique<ScriptExecution>(child)); children.back()->parent=this; }
    }
    ScriptExecution(const ScriptExecution& source) : node(source.node), baseline(source.baseline), logical(source.logical),
        begin(source.begin), end(source.end), channels(source.channels), canceled(source.canceled), starts(source.starts), finishes(source.finishes),
        elapsed(source.elapsed), duration(source.duration), born(source.born), finished(source.finished), id(source.id), iteration(source.iteration), branch(source.branch), lastPollTick(source.lastPollTick), lastPollElapsed(source.lastPollElapsed), active(source.active),
        complete(source.complete), paused(source.paused), stopped(source.stopped), reverse(source.reverse), completionSent(source.completionSent) {
        for(const auto& [name,state]:source.marks) {
            auto copy=state; copy.cursor=std::make_shared<ScriptExecution>(*state.cursor); marks.emplace(name,std::move(copy));
        }
        memberBaselines=source.memberBaselines; memberValues=source.memberValues;
        for (const auto& child : source.children) { children.push_back(std::make_unique<ScriptExecution>(*child)); children.back()->parent=this; }
        for (const auto& past : source.history) history.push_back(std::make_unique<ScriptExecution>(*past));
    }
    void reset() {
        lastPollTick=UINT64_MAX; lastPollElapsed=-1; canceled.clear();
        elapsed=duration=0; finished=scriptInfinity; iteration=0; branch=-1; active=complete=paused=stopped=reverse=completionSent=false;
        externalLifetime.reset(); marks.clear(); memberBaselines.clear(); memberValues.clear(); history.clear(); baseline.clear(); logical.clear(); begin.clear(); end.clear(); channels.clear(); starts.clear(); finishes.clear();
        for (auto& child : children) child->reset();
    }
    void capture(const std::vector<float>& values) {
        baseline=values; logical=values; active=true;
        if (node->kind == ScriptNode::Operation) {
            for (const auto& value : node->values) {
                channels.push_back(value.field); begin.push_back(values.at(value.field));
                float target=value.target;
                if (value.field==animationChannel_Facing) {
                    // The same angular routing rules used by Animated's tracks.
                    const double turn=2*std::numbers::pi, pi=std::numbers::pi;
                    double delta=node->mode==animationMode_Add ? target : target-begin.back();
                    if (node->mode==animationMode_Add) {
                        if (node->direction==rotationDirection_Clockwise) delta=std::abs(delta);
                        if (node->direction==rotationDirection_CounterClockwise) delta=-std::abs(delta);
                    } else if (node->direction!=rotationDirection_AsSpecified) {
                        delta=std::fmod(delta,turn);
                        if (node->direction==rotationDirection_Clockwise && delta<0) delta+=turn;
                        if (node->direction==rotationDirection_CounterClockwise && delta>0) delta-=turn;
                        if (node->direction==rotationDirection_Shortest) {
                            if (std::abs(std::abs(delta)-pi)<=2*std::numeric_limits<float>::epsilon()*pi) delta=pi;
                            if (delta>pi) delta-=turn;
                            if (delta<=-pi) delta+=turn;
                        }
                    }
                    target=begin.back()+delta;
                } else if (node->mode==animationMode_Add) target+=begin.back();
                else if (node->mode==animationMode_Multiply) target*=begin.back();
                if (!std::isfinite(target) || !std::isfinite(target-begin.back())) throw std::invalid_argument("Resolved animation script target must be finite");
                end.push_back(target);
            }
        }
        if (node->kind==ScriptNode::Flip) {
            const auto axis=node->values.at(0).field;
            const auto field=values.size()-2+axis;
            const bool before=values.at(field)!=0;
            const bool after=node->mode==animationMode_Toggle ? !before : node->values[0].target!=0;
            channels={static_cast<unsigned>(field),animationChannel_CenterOffsetX+axis};
            begin={values[field],values[animationChannel_CenterOffsetX+axis]}; end={static_cast<float>(after),before==after?values[animationChannel_CenterOffsetX+axis]:-values[animationChannel_CenterOffsetX+axis]};
        }
        if (node->kind==ScriptNode::Group) {
            starts.assign(children.size(),scriptInfinity); finishes.assign(children.size(),scriptInfinity);
        }
    }
    std::set<unsigned> memberChannels(AnimatedBase& receiver) const {
        if(node->kind==ScriptNode::Target && memberTarget()==&receiver) return {channels.begin(),channels.end()};
        std::set<unsigned> result;
        for(const auto& child:children) {
            const auto owned=child->memberChannels(receiver); result.insert(owned.begin(),owned.end());
        }
        return result;
    }
    void collectChannels() {
        std::set<unsigned> unique(channels.begin(),channels.end());
        for (const auto& child : children) if (child->active)
            unique.insert(child->channels.begin(),child->channels.end());
        for (auto field : canceled) unique.erase(field);
        channels.assign(unique.begin(),unique.end());
    }
    // Replay resolved paths. Conditions are deliberately not reevaluated backwards.
    void sample(double time, std::vector<float>& values, const Publisher& publish, AnimatedBase& target) const {
        time=std::clamp(time,0.0,complete?duration:std::max(duration,elapsed));
        switch (node->kind) {
        case ScriptNode::Target:
            if(auto* member=memberTarget()) {
                auto current=readValues(*member); const auto before=current;
                children[0]->sample(time,current,publish,*member);
                for(auto field:canceled) current[field]=before[field];
                publish(*member,current);
            }
            break;
        case ScriptNode::Flip:
            for (size_t i=0;i<channels.size();++i) values[channels[i]]=end[i];
            break;
        case ScriptNode::Command:
            for(const auto& child:children) if(child->active) child->sample(time,values,publish,target);
            break;
        case ScriptNode::Operation:
            for (size_t i=0;i<node->values.size();++i) if (std::find(canceled.begin(),canceled.end(),node->values[i].field)==canceled.end()) values[node->values[i].field]=node->seconds==0 || time>=node->seconds ? end[i] :
                node->easing(time,begin[i],end[i]-begin[i],node->seconds);
            break;
        case ScriptNode::Group:
            for (size_t i=0;i<children.size();++i) if (children[i]->active && time>=starts[i])
                children[i]->sample(std::min(time-starts[i],children[i]->duration),values,publish,target);
            break;
        case ScriptNode::Conditional:
            if (branch>=0) children[branch]->sample(time,values,publish,target);
            break;
        case ScriptNode::Yoyo: {
            const double forward=children[0]->duration;
            children[0]->sample(time<=forward ? time : 2*forward-time,values,publish,target); break;
        }
        case ScriptNode::Repeat: {
            for (const auto& past : history) {
                if (time<=past->duration) { past->sample(time,values,publish,target); return; }
                time-=past->duration;
            }
            children[0]->sample(time,values,publish,target); break;
        }
        case ScriptNode::Gain: {
            const double gain=scriptEnvelope(*node,time,1);
            const auto scaled=[&](AnimatedBase& receiver,const std::vector<float>& current) {
                auto output=current;
                const auto found=memberBaselines.find(&receiver);
                const auto& origin=found==memberBaselines.end()?baseline:found->second;
                const auto owned=&receiver==&target?std::set<unsigned>(channels.begin(),channels.end()):memberChannels(receiver);
                for(auto field:owned) if(field<output.size()) output[field]=origin[field]+gain*(current[field]-origin[field]);
                publish(receiver,output);
            };
            auto copy=baseline; children[0]->sample(time,copy,scaled,target);
            for (auto field : channels) values[field]=baseline[field]+gain*(copy[field]-baseline[field]);
            break;
        }
        case ScriptNode::Rate: children[0]->sample(scriptClock(*node,time),values,publish,target); break;
        default: if (!children.empty()) children[0]->sample(time,values,publish,target); break;
        }
    }
    void prepareCommand(std::vector<float>& values, AnimatedBase& target);
    // Returns unused parent time when the block completes, otherwise zero.
    double advance(double seconds, std::vector<float>& values, AnimatedBase& target, unsigned& budget, const Publisher& publish, uint64 tick) {
        const bool before=complete;
        const double rest=advanceImpl(seconds,values,target,budget,publish,tick);
        if(!before && complete) {
            emit("finished",target);
            if(node->kind==ScriptNode::Group && node->name.starts_with("@script:") && node->name!="@script:@stagger") emit("scriptFinished",target);
        }
        return rest;
    }
    double advanceImpl(double seconds, std::vector<float>& values, AnimatedBase& target, unsigned& budget, const Publisher& publish, uint64 tick) {
        if (++budget>100000) throw std::runtime_error("Animation script made no bounded progress");
        if (complete) return seconds;
        if (paused || stopped) return 0;
        if(node->kind==ScriptNode::Target) {
            auto* member=memberTarget();
            if(!member) { complete=true; duration=elapsed; externalLifetime.reset(); return seconds; }
            if(member->mSchedulePaused) { if(!active) capture(values); return 0; }
            if(!externalLifetime) {
                externalLifetime=std::make_shared<ScriptExecution*>(this);
                std::erase_if(member->mExternalScriptExecutions,[](const auto& weak){return weak.expired();});
                member->mExternalScriptExecutions.push_back(externalLifetime);
            }
            if(!active) { capture(values); memberValues=readValues(*member); }
            auto current=readValues(*member);
            const double rest=children[0]->advance(seconds,current,*member,budget,publish,tick);
            memberValues=current; publish(*member,current);
            elapsed+=seconds-rest; duration=elapsed; complete=children[0]->complete; collectChannels();
            return complete?rest:0;
        }
        if (node->kind==ScriptNode::Jump) throw ScriptJump{node->name,node->mode!=0,seconds,&root(),&target};
        if (!active) {
            if (node->kind==ScriptNode::Operation) for (const auto& value : node->values) {
                if(target.prepareSampledAnimation(value.field,node->mode,values.at(value.field)))
                    values.at(value.field)=*target.tweenFields().at(value.field);
            }
            capture(values); born=target.scriptOwnerTime();
            emit("started",target);
            if(node->kind==ScriptNode::Command) { publish(target,values); prepareCommand(values,target); }
            if(target.isTroupe()) for(auto* member:target.animationTargets()) memberBaselines[member]=readValues(*member);
            const auto fields=target.tweenFields();
            auto* previousAcquirer=target.mScriptAcquiring; target.mScriptAcquiring=this;
            struct AcquisitionGuard { ScriptExecution*& slot; ScriptExecution* previous; ~AcquisitionGuard(){slot=previous;} } acquisitionGuard{target.mScriptAcquiring,previousAcquirer};
            if (node->kind==ScriptNode::Operation) for (const auto& value : node->values) {
                auto* field=const_cast<float*>(fields.at(value.field));
                target.cancelAnimation(field);
                if (auto* competing=target.competingAnimationChannel(field)) target.cancelAnimation(competing);
                // The numeric scheduler cancels constant motion when a pose channel acquires it.
                const unsigned rate=value.field==animationChannel_LocationX?animationChannel_MovementX:value.field==animationChannel_LocationY?animationChannel_MovementY:value.field==animationChannel_Facing?animationChannel_Spinning:value.field==animationChannel_Width?animationChannel_StretchingWidth:value.field==animationChannel_Height?animationChannel_StretchingHeight:UINT32_MAX;
                if (rate!=UINT32_MAX) values[rate]=0;
            }
        }
        if (node->kind==ScriptNode::Emit) {
            complete=true; duration=0; emit(node->name,target); return seconds;
        }
        if(node->kind==ScriptNode::Command) {
            double rest=seconds;
            for(auto& child:children) if(!child->complete)
                rest=std::min(rest,child->advance(seconds,values,target,budget,publish,tick));
            const double step=std::max(seconds-rest,std::min(seconds,std::max(0.0,node->seconds-elapsed)));
            elapsed+=step; duration=elapsed; collectChannels();
            complete=elapsed>=node->seconds && std::all_of(children.begin(),children.end(),[](const auto& child){return child->complete;});
            return complete?seconds-step:0;
        }

        if (node->kind==ScriptNode::Mark) {
            complete=true; duration=0;
            if(node->mode) {
                auto& owner=root();
                auto retained=std::move(owner.marks);
                auto snapshot=std::make_shared<ScriptExecution>(owner);
                owner.marks=std::move(retained);
                std::function<void(ScriptExecution&)> completedPlacements=[&](ScriptExecution& cursor) {
                    if(cursor.node->kind==ScriptNode::Group && cursor.active)
                        for(size_t i=0;i<cursor.children.size();++i) if(cursor.children[i]->complete && !std::isfinite(cursor.finishes[i])) cursor.finishes[i]=cursor.elapsed;
                    for(auto& child:cursor.children) completedPlacements(*child);
                };
                completedPlacements(*snapshot);
                MarkState saved{values,target.mAnimations,std::move(snapshot),{}}; saved.credits=target.mTroupeRateTime;
                if(target.isTroupe()) for(auto* member:target.animationTargets())
                    saved.members.push_back({member->animationLifetime(),readValues(*member),member->mAnimations,member->mTroupeRateTime});
                owner.marks[node->name]=std::move(saved);
            }
            emit("mark",target);
            return seconds;
        }
        if (node->kind==ScriptNode::Operation || node->kind==ScriptNode::Flip) {
            const double step=std::min(seconds,std::max(0.0,node->seconds-elapsed));
            const double before=elapsed;
            elapsed+=step; duration=node->seconds;
            if (node->kind==ScriptNode::Operation) for (size_t i=0;i<node->values.size();++i) {
                const auto field=node->values[i].field;
                if (field<animationChannel_MovementX || field>animationChannel_StretchingHeight || std::find(canceled.begin(),canceled.end(),field)!=canceled.end()) continue;
                const unsigned positions[]={animationChannel_LocationX,animationChannel_LocationY,animationChannel_Facing,animationChannel_Width,animationChannel_Height};
                float value=begin[i];
                AnimatedBase::Animation animation(&value,end[i],node->easing,0,node->seconds);
                const double area=AnimatedBase::integrateAnimation(animation,elapsed)-AnimatedBase::integrateAnimation(animation,before);
                bool external=false;
                for(auto* cursor=parent;cursor;cursor=cursor->parent) if(cursor->node->kind==ScriptNode::Target) { external=true; break; }
                const auto index=field-animationChannel_MovementX;
                values[positions[index]]+=static_cast<float>((area-(external?0:step*target.mScriptFrameRates[index]))*1000);
                if(external) target.mTroupeRateTime[index]+=step;
            }
            sample(elapsed,values,publish,target);
            complete=elapsed>=node->seconds;
            if (complete && node->completion && !completionSent) {
                publish(target,values); completionSent=true;
                for (size_t i=0;i<node->values.size();++i) {
                    target.enqueueScriptCompletion(node->values[i].field,values[node->values[i].field],node->easing,node->seconds,node->completion);
                }
            }
            return complete ? seconds-step : 0;
        }
        if (node->kind==ScriptNode::Conditional) {
            if (branch<0) {
                publish(target,values);
                const bool result=node->evaluator({target,0});
                branch=result ? 0 : children.size()>1 ? 1 : -2;
            }
            if (branch==-2) { complete=true; duration=0; return seconds; }
            const double rest=children[branch]->advance(seconds,values,target,budget,publish,tick);
            elapsed+=seconds-rest; complete=children[branch]->complete; duration=elapsed; collectChannels();
            return complete ? rest : 0;
        }
        if (node->kind==ScriptNode::Group) {
            double remaining=seconds;
            bool advanced=false;
            for (;;) {
                bool all=true;
                double step=remaining;
                for (size_t i=0;i<children.size();++i) {
                    const auto& definition=*children[i]->node;
                    if (!std::isfinite(starts[i])) {
                        if (definition.externalDependency) {
                            const double finish=target.scriptDependencyStart(definition.externalDependency);
                            if (std::isfinite(finish)) starts[i]=std::max(0.0,finish+definition.delay-born);
                        } else if (definition.dependency<0) starts[i]=definition.delay;
                        else if (std::isfinite(finishes.at(definition.dependency))) starts[i]=finishes[definition.dependency]+definition.delay;
                    }
                    if (children[i]->complete) continue;
                    all=false;
                    if (starts[i]>elapsed) { if (std::isfinite(starts[i])) step=std::min(step,starts[i]-elapsed); continue; }
                    if (!advanced || remaining>0 || !children[i]->active || children[i]->nextBoundary()==0)
                        children[i]->advance(0,values,target,budget,publish,tick);
                    if (children[i]->complete) finishes[i]=elapsed;
                    else step=std::min(step,children[i]->nextBoundary());
                }
                if (all || std::all_of(children.begin(),children.end(),[](const auto& c){return c->complete;})) {
                    complete=true; duration=elapsed; collectChannels(); return remaining;
                }
                // Newly completed predecessors can release successors at this same boundary.
                bool released=false;
                for (size_t i=0;i<children.size();++i) if (!std::isfinite(starts[i]) && children[i]->node->dependency>=0 &&
                    std::isfinite(finishes.at(children[i]->node->dependency))) { released=true; break; }
                if (released) continue;
                if (step==0) { collectChannels(); return 0; }
                for (size_t i=0;i<children.size();++i) if (!children[i]->complete && starts[i]<=elapsed) {
                    const double rest=children[i]->advance(step,values,target,budget,publish,tick);
                    if (children[i]->complete) finishes[i]=elapsed+step-rest;
                }
                elapsed+=step; remaining=std::max(0.0,remaining-step); advanced=true;
                if (++budget>100000) throw std::runtime_error("Animation script made no bounded progress");
            }
        }
        auto& child=*children.at(0);
        if (node->kind==ScriptNode::Until) {
            if (child.stopped) return 0;
            double remaining=seconds;
            for (;;) {
                if (lastPollTick!=tick || lastPollElapsed!=elapsed) {
                    publish(target,values); lastPollTick=tick; lastPollElapsed=elapsed;
                    if (node->evaluator({target,elapsed})) {
                        if (child.node->kind==ScriptNode::Operation && child.node->completion && !child.completionSent) {
                            child.completionSent=true;
                            for (const auto& value : child.node->values) target.enqueueScriptCompletion(value.field,values[value.field],child.node->easing,elapsed,child.node->completion);
                        }
                        complete=true; duration=elapsed; collectChannels(); emit("untilFired",target); return remaining;
                    }
                }
                child.advance(0,values,target,budget,publish,tick);
                if (child.complete) { complete=true; duration=elapsed; collectChannels(); return remaining; }
                const double step=std::min(remaining,child.nextBoundary());
                if (step==0) { collectChannels(); return 0; }
                const double rest=child.advance(step,values,target,budget,publish,tick);
                elapsed+=step-rest; remaining=std::max(0.0,remaining-step+rest); collectChannels();
                if (child.complete) { complete=true; duration=elapsed; return remaining; }
                if (remaining==0) return 0;
            }
        }
        if (node->kind==ScriptNode::Yoyo && reverse) {
            const double step=std::min(seconds,std::max(0.0,2*child.duration-elapsed));
            elapsed+=step; duration=2*child.duration;
            auto copy=baseline; child.sample(duration-elapsed,copy,publish,target);
            for (auto field : channels) values[field]=copy[field];
            complete=elapsed>=duration;
            if (complete && duration==0) for (auto field : channels) values[field]=baseline[field];
            return complete ? seconds-step : 0;
        }
        if (node->kind==ScriptNode::Gain || node->kind==ScriptNode::Rate) {
            const double local=node->kind==ScriptNode::Rate ? scriptClock(*node,elapsed+seconds)-scriptClock(*node,elapsed) : seconds;
            const double childBefore=child.elapsed;
            for (size_t i=0;i<logical.size();++i) if (std::find(channels.begin(),channels.end(),i)==channels.end()) {
                logical[i]=values[i]; baseline[i]=values[i];
            }
            const auto display=[&](AnimatedBase& receiver,const std::vector<float>& current) {
                auto output=current; collectChannels();
                double parentTime=elapsed+child.elapsed-childBefore;
                if (node->kind==ScriptNode::Rate) {
                    double low=0,high=seconds;
                    for (int i=0;i<48;++i) {
                        const double middle=(low+high)/2;
                        if (scriptClock(*node,elapsed+middle)-scriptClock(*node,elapsed)<child.elapsed-childBefore) low=middle; else high=middle;
                    }
                    parentTime=elapsed+high;
                }
                const double gain=node->kind==ScriptNode::Gain ? scriptEnvelope(*node,parentTime,1) : 1;
                const auto& origin=&receiver==&target?baseline:memberBaselines.at(&receiver);
                const auto owned=&receiver==&target?std::set<unsigned>(channels.begin(),channels.end()):memberChannels(receiver);
                for(auto field:owned) if(field<output.size()) output[field]=origin[field]+gain*(current[field]-origin[field]);
                publish(receiver,output);
            };
            const double rest=child.advance(local,logical,target,budget,display,tick);
            if(target.isTroupe()) { auto copy=logical; child.sample(child.elapsed,copy,display,target); }
            double consumed=seconds;
            if (child.complete) {
                if (node->kind==ScriptNode::Rate) {
                    double low=0,high=seconds;
                    for (int i=0;i<48;++i) { const double mid=(low+high)/2;
                        if (scriptClock(*node,elapsed+mid)-scriptClock(*node,elapsed)<local-rest) low=mid; else high=mid; }
                    consumed=high;
                } else consumed=seconds-rest;
            }
            elapsed+=consumed; collectChannels();
            const double gain=node->kind==ScriptNode::Gain ? scriptEnvelope(*node,elapsed,1) : 1;
            for (auto field : channels) values[field]=baseline[field]+gain*(logical[field]-baseline[field]);
            complete=child.complete; duration=elapsed;
            return complete ? seconds-consumed : 0;
        }
        double remaining=seconds;
        for (;;) {
            const double rest=child.advance(remaining,values,target,budget,publish,tick);
            elapsed+=remaining-rest; collectChannels();
            if (!child.complete) return 0;
            if (node->kind==ScriptNode::Yoyo) {
                reverse=true;
                emit("yoyo",target);
                return advance(rest,values,target,budget,publish,tick);
            }
            if (node->kind!=ScriptNode::Repeat || (node->count>=0 && iteration>=node->count)) {
                complete=true; duration=elapsed; return rest;
            }
            if (child.duration==0 && node->count<0) throw std::runtime_error("Infinite repetition requires positive elapsed time");
            ++iteration;
            emit("repeat",target);
            if (node->count>=0) history.push_back(std::make_unique<ScriptExecution>(child));
            for (auto field : channels) values[field]=baseline[field];
            child.reset(); remaining=rest;
        }
    }
    void cancelChannel(unsigned field, ScriptExecution* acquiring) {
        if(this==acquiring || !active) return;
        if(node->kind==ScriptNode::Target && complete) {
            if(std::find(channels.begin(),channels.end(),field)!=channels.end()) { canceled.push_back(field); std::erase(channels,field); }
            return;
        }
        if(complete) return;
        bool ancestor=false;
        for (auto* owner=acquiring; owner; owner=owner->parent) if (owner==this) {ancestor=true;break;}
        if (!ancestor && (node->kind==ScriptNode::Yoyo || node->kind==ScriptNode::Gain || node->kind==ScriptNode::Rate) &&
            std::find(channels.begin(),channels.end(),field)!=channels.end()) canceled.push_back(field);
        if (node->kind==ScriptNode::Operation && std::find(channels.begin(),channels.end(),field)!=channels.end()) {
            canceled.push_back(field); std::erase(channels,field);
            if (channels.empty()) { stopped=true; duration=elapsed; }
        }
        for (auto& child : children) child->cancelChannel(field,acquiring);
        if (node->kind!=ScriptNode::Operation) { channels.clear(); collectChannels(); }
    }
    bool pending() const {
        if(complete || stopped) return false;
        if(node->kind==ScriptNode::Operation || node->kind==ScriptNode::Flip || node->kind==ScriptNode::Mark || node->kind==ScriptNode::Jump || node->kind==ScriptNode::Emit || reverse) return true;
        if(node->kind==ScriptNode::Conditional && branch>=0) return children[branch]->pending();
        for(size_t i=0;i<children.size();++i) {
            const int dependency=children[i]->node->dependency;
            if(dependency>=0 && !children[dependency]->complete && !children[dependency]->pending()) continue;
            if(children[i]->pending()) return true;
        }
        return false;
    }
    double nextBoundary() const {
        if (complete || paused || stopped) return scriptInfinity;
        if(node->kind==ScriptNode::Target) { auto* member=memberTarget(); if(member && member->mSchedulePaused) return scriptInfinity; }
        if (!active) return 0;
        if (node->kind==ScriptNode::Mark || node->kind==ScriptNode::Jump || node->kind==ScriptNode::Emit) return 0;
        if (node->kind==ScriptNode::Operation || node->kind==ScriptNode::Flip || node->kind==ScriptNode::Command) return std::max(0.0,node->seconds-elapsed);
        if (node->kind==ScriptNode::Yoyo && reverse) return std::max(0.0,2*children[0]->duration-elapsed);
        if (node->kind==ScriptNode::Conditional) return branch>=0 ? children[branch]->nextBoundary() : 0;
        if (node->kind==ScriptNode::Group) {
            double result=scriptInfinity;
            for (size_t i=0;i<children.size();++i) if (!children[i]->complete) {
                if (starts[i]>elapsed) result=std::min(result,starts[i]-elapsed);
                else result=std::min(result,children[i]->nextBoundary());
            }
            return result;
        }
        if (node->kind==ScriptNode::Rate) {
            const double local=children[0]->nextBoundary();
            if (!std::isfinite(local) || local==0) return local;
            const double start=scriptClock(*node,elapsed);
            double low=0,high=local/std::min(1.f,node->factor)+std::max(0.0,node->seconds-elapsed);
            for (int i=0;i<48;++i) {
                const double middle=(low+high)/2;
                if (scriptClock(*node,elapsed+middle)-start<local) low=middle; else high=middle;
            }
            return node->seconds>elapsed ? std::min(high,node->seconds-elapsed) : high;
        }
        return children.empty() ? scriptInfinity : children[0]->nextBoundary();
    }
};

class AnimationScriptState {
public:
    static ScriptNodePtr resolve(const ScriptNodePtr& source, size_t fieldCount, uint32 targetClass=0);
    struct Context {
        ScriptNodePtr block;
        ScriptNodePtr conditional{};
        double delay=0;
        int dependency=-1;
        bool pending=false, alternative=false, sequential=false, parallelNext=false;
        uint32 externalDependency=0;
    };
    bool recording=false, sealed=false, evaluating=false, deleted=false;
    uint64 tick=0;
    double clock=0;
    uint32 nextId=1;
    struct Completion { unsigned field; float value; EasingFunc easing; double seconds; uint8 kind; };
    std::vector<Completion> completions;
    std::vector<Context> contexts;
    std::vector<std::unique_ptr<ScriptExecution>> executions;
    ScriptExecution* selectedExecution=nullptr;
    ScriptExecution* selectedRoot=nullptr;
    std::vector<unsigned> selectionPath;
    explicit AnimationScriptState(bool recorder=false) : recording(recorder) {
        contexts.push_back({std::make_shared<ScriptNode>()});
    }
    void placeSelectedPlayback() {
        if (!selectedExecution || !contexts[0].block->children.empty()) return;
        if (selectedExecution->active) return;
        auto node=cloneScript(selectedExecution->node);
        std::erase_if(executions,[&](const auto& instance){return instance.get()==selectedRoot;});
        selectedExecution=selectedRoot=nullptr; selectionPath.clear(); append(std::move(node));
    }
    void editable() const {
        if (deleted) throw std::logic_error("Animation script was deleted from the library");
        if (sealed) throw std::logic_error("Animation script is sealed");
        if (evaluating) throw std::logic_error("Animation evaluators cannot mutate the executing script graph");
    }
    void closed() const {
        if (contexts.size()!=1) throw std::logic_error("Animation script has an unclosed block");
        if (contexts.back().pending || contexts.back().parallelNext) throw std::logic_error("Animation placement requires a successor");
        scriptNonempty(contexts[0].block);
    }
    void append(ScriptNodePtr node) {
        editable(); auto& context=contexts.back();
        node->delay=context.delay; node->dependency=context.dependency; node->externalDependency=context.externalDependency;
        if (context.parallelNext) {
            auto operand=context.block->children.back();
            ScriptNodePtr parallel;
            if (operand->kind==ScriptNode::Group && operand->name=="@and") parallel=cloneScript(operand);
            else {
                parallel=std::make_shared<ScriptNode>(); parallel->name="@and";
                parallel->delay=operand->delay; parallel->dependency=operand->dependency; parallel->externalDependency=operand->externalDependency;
                auto inner=cloneScript(operand); inner->delay=0; inner->dependency=-1; inner->externalDependency=0;
                parallel->children.push_back(inner);
            }
            node->dependency=-1; node->externalDependency=0;
            parallel->children.push_back(std::move(node)); scriptValidateParallel(parallel);
            context.block->children.back()=std::move(parallel); context.parallelNext=false;
        } else {
            if (context.sequential && node->dependency<0 && !node->externalDependency && !context.block->children.empty()) node->dependency=static_cast<int>(context.block->children.size())-1;
            context.block->children.push_back(std::move(node));
        }
        context.delay=0; context.dependency=-1; context.externalDependency=0; context.pending=false;
    }
    ScriptNodePtr selected() const {
        if (!recording && contexts.size()==1 && contexts[0].block->children.empty() && selectedExecution)
            return selectedExecution->node;
        if (contexts.back().block->children.empty()) throw std::logic_error("Animation modifier requires a preceding local operand");
        return contexts.back().block->children.back();
    }
    void wrap(ScriptNodePtr wrapper) {
        editable();
        if(contexts.back().parallelNext) throw std::logic_error("andAlso requires a successor before a modifier");
        if (!recording && contexts.size()==1 && contexts[0].block->children.empty() && selectedExecution) {
            if (selectedExecution->active) throw std::logic_error("Playback modifiers must be applied before execution begins");
            const auto operand=selectedExecution->node;
            wrapper->children.push_back(cloneScript(operand));
            selectedExecution->node=std::move(wrapper);
            selectedExecution->children.clear();
            for (const auto& child : selectedExecution->node->children) {
                selectedExecution->children.push_back(std::make_unique<ScriptExecution>(child));
                selectedExecution->children.back()->parent=selectedExecution;
            }
            return;
        }
        const auto operand=selected();
        wrapper->delay=operand->delay; wrapper->dependency=operand->dependency;
        auto inner=cloneScript(operand); inner->delay=0; inner->dependency=-1;
        wrapper->children.push_back(std::move(inner));
        contexts.back().block->children.back()=std::move(wrapper);
    }
};

void ScriptExecution::prepareCommand(std::vector<float>& values, AnimatedBase& target) {
        // Run the ordinary method once to obtain its discrete effects and numeric tracks.
        // Its tracks are then driven by this execution, sharing its clock and cancellation.
        const auto beforeValues=values;
        auto savedScripts=std::move(target.mScripts);
        auto savedTracks=std::move(target.mAnimations);
        const double savedDelay=target.mDelaySeconds;
        const bool savedAppend=target.mAppendAnimation;
        auto* savedAcquirer=target.mScriptAcquiring;
        target.mScriptAcquiring=this; target.mDelaySeconds=0; target.mAppendAnimation=false;
        struct Restore {
            AnimatedBase& target; std::shared_ptr<AnimationScriptState>& scripts;
            std::vector<AnimatedBase::Animation>& tracks; double delay; bool append; ScriptExecution* acquirer;
            ~Restore() { target.mScripts=std::move(scripts); target.mAnimations=std::move(tracks); target.mDelaySeconds=delay; target.mAppendAnimation=append; target.mScriptAcquiring=acquirer; }
        } restore{target,savedScripts,savedTracks,savedDelay,savedAppend,savedAcquirer};
        const bool supported=applyAnimationOperation(target,node->name,node->arguments);
        auto definition=cloneScript(node); definition->children.clear(); node=definition;
        children.clear();
        if(!supported) { emit("unsupportedOp",target); return; }
        const auto fields=target.tweenFields();
        for(auto& track:target.mAnimations) {
            target.animationStarting(track);
            const auto found=std::find(fields.begin(),fields.end(),track.value);
            if(found==fields.end()) throw std::logic_error("Recorded operation has an unregistered animation channel");
            const auto field=static_cast<unsigned>(found-fields.begin());
            std::erase_if(savedTracks,[&](const auto& old){return old.value==track.value;});
            auto leaf=std::make_shared<ScriptNode>(); leaf->kind=ScriptNode::Operation;
            leaf->seconds=track.durationSeconds; leaf->delay=track.delaySeconds; leaf->easing=track.easing;
            leaf->mode=track.targetMode; leaf->direction=track.rotationDirection; leaf->completion=track.completion;
            leaf->values.push_back({field,track.targetVal}); definition->children.push_back(leaf);
        }
        if(target.mScripts) {
            auto graph=AnimationScriptState::resolve(target.mScripts->contexts[0].block,fields.size(),target.scriptClassTag());
            if(!graph->children.empty()) definition->children.push_back(graph);
            for(const auto& execution:target.mScripts->executions) definition->children.push_back(cloneScript(execution->node));
        }
        values=readValues(target); baseline=beforeValues; logical=values;
        for(size_t field=0;field<fields.size();++field) if(beforeValues[field]!=values[field]) {
            auto setter=std::make_shared<ScriptNode>(); setter->kind=ScriptNode::Operation;
            setter->values.push_back({static_cast<unsigned>(field),values[field]});
            definition->children.insert(definition->children.begin(),setter);
            std::erase_if(savedTracks,[&](const auto& old){return old.value==fields[field];});
        }
        if(!definition->children.empty()) {
            auto group=std::make_shared<ScriptNode>(); group->children=std::move(definition->children);
            definition->children.push_back(group);
            children.push_back(std::make_unique<ScriptExecution>(group)); children.back()->parent=this;
        }
    }

bool AnimatedBase::isRecordingOperation() const {
    return isTroupe() || (mScripts && (mScripts->recording || mScripts->contexts.size()>1 ||
        !mScripts->contexts[0].block->children.empty() || mScripts->contexts[0].pending || mScripts->contexts[0].parallelNext));
}
bool AnimatedBase::recordOperation(const std::string& name, AnimationArguments arguments) {
    if(!isRecordingOperation()) return false;
    if(!mScripts) mScripts=std::make_shared<AnimationScriptState>();
    mScripts->editable();
    const double seconds=animationOperationDuration(name,arguments); validateDuration(seconds);
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Command;
    node->name=name; node->seconds=seconds; node->arguments=std::move(arguments);
    mScripts->append(node); return true;
}

namespace {
struct ScriptBuilderRelease { void operator()(AnimationScript* script) const { script->release(); } };
using OwnedScriptBuilder = std::unique_ptr<AnimationScript,ScriptBuilderRelease>;
std::map<std::string,OwnedScriptBuilder>& scriptLibrary() {
    static std::map<std::string,OwnedScriptBuilder> library;
    return library;
}

}

AnimationScript::AnimationScript(std::string name) : mName(std::move(name)) {
    mScripts=std::make_shared<AnimationScriptState>(true);
}
AnimationScript& AnimatedBase::defineScript(const std::string& name) {
    if (name.empty()) throw std::invalid_argument("Animation script name must not be empty");
    auto& library=scriptLibrary();
    if (library.contains(name)) throw std::invalid_argument("Animation script name already exists: "+name);
    auto builder=OwnedScriptBuilder(new AnimationScript(name));
    builder->addRef();
    auto& result=*builder; library.emplace(name,std::move(builder)); return result;
}
bool AnimatedBase::hasScriptDefinition(const std::string& name) { return scriptLibrary().contains(name); }
bool AnimatedBase::deleteScript(const std::string& name) {
    if(name.empty()) throw std::invalid_argument("Script name must not be empty");
    auto& library=scriptLibrary(); const auto found=library.find(name);
    if(found==library.end()) return false;
    // Wrappers may still own the recorder shell. Release the definition graph now
    // and invalidate that shell without affecting independently published copies.
    auto invalid=std::make_shared<AnimationScriptState>(true); invalid->deleted=true;
    found->second->mScripts=std::move(invalid);
    library.erase(found); return true;
}
void AnimatedBase::clearScriptLibrary() {
    auto& library=scriptLibrary();
    while(!library.empty()) deleteScript(library.begin()->first);
}
AnimationScript& AnimationScript::endScript() {
    mScripts->editable(); mScripts->closed(); mScripts->sealed=true; return *this;
}

bool AnimatedBase::recordScriptAnimation(std::initializer_list<ScriptValue> values, double seconds, EasingFunc easing, uint8 mode, int direction, uint8 completion, uint32 requiredClass) {
    if(!mSampledPreparationDepth)validateSampledRequest(values,seconds,easing,mode);
    if (!mSampledPreparationDepth && !isRecordingOperation() && (!mScripts || (!mScripts->recording && mScripts->contexts.size()==1 && mScripts->contexts[0].block->children.empty()))) {
        for (const auto& value : values) if (mode!=animationMode_Add || value.target!=0)
            prepareSampledAnimation(value.field,mode,*tweenFields().at(value.field));
    }
    if (!mScripts && isTroupe()) mScripts=std::make_shared<AnimationScriptState>();
    if (!mScripts) return false;
    if (!isTroupe() && !mScripts->recording && mScripts->contexts.size()==1 &&
        (mScripts->contexts[0].block->children.empty() && !mScripts->contexts[0].pending && !mScripts->contexts[0].parallelNext)) return false;
    mScripts->editable(); validateDuration(seconds);
    if (!easing || mode>animationMode_Multiply || direction<rotationDirection_AsSpecified || direction>rotationDirection_CounterClockwise)
        throw std::invalid_argument("Invalid script animation easing or route");
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Operation;
    node->seconds=seconds; node->easing=easing; node->mode=mode; node->direction=direction; node->completion=completion; node->requiredClass=requiredClass;
    for (const auto& value : values) {
        if (!std::isfinite(value.target)) throw std::invalid_argument("Script animation values must be finite");
        // A zero relative displacement does not acquire or hold that axis.
        if (mode==animationMode_Add && value.target==0 &&
            (value.field==animationChannel_LocationX || value.field==animationChannel_LocationY)) continue;
        node->values.push_back({value.field,value.target});
    }
    mScripts->append(std::move(node)); return true;
}
bool AnimatedBase::recordScriptFlip(unsigned axis, bool value, bool toggle) {
    if (!mScripts && isTroupe()) mScripts=std::make_shared<AnimationScriptState>();
    if (!mScripts || (!isTroupe() && !mScripts->recording && mScripts->contexts.size()==1)) return false;
    mScripts->editable();
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Flip;
    node->values.push_back({axis,static_cast<float>(value)}); node->mode=toggle?animationMode_Toggle:animationMode_Assign;
    mScripts->append(node); return true;
}
bool AnimatedBase::scriptWait(double seconds) {
    if (!mScripts || (!mScripts->recording && mScripts->contexts.size()==1 &&
        mScripts->contexts[0].block->children.empty() && !mScripts->selectedExecution)) return false;
    mScripts->editable(); validateDuration(seconds);
    if (!mScripts->recording && mScripts->contexts.size()==1) mScripts->placeSelectedPlayback();
    auto& context=mScripts->contexts.back();
    if (!std::isfinite(context.delay+seconds)) throw std::invalid_argument("Animation delay overflow");
    context.delay+=seconds; context.pending=true; return true;
}
bool AnimatedBase::scriptAndThen() {
    if (!mScripts || (!mScripts->recording && mScripts->contexts.size()==1 &&
        mScripts->contexts[0].block->children.empty() && !mScripts->selectedExecution)) return false;
    mScripts->editable();
    if (!mScripts->recording && mScripts->contexts.size()==1) mScripts->placeSelectedPlayback();
    mScripts->selected(); auto& context=mScripts->contexts.back();
    if (context.block->children.empty()) context.externalDependency=mScripts->selectedExecution->id;
    else context.dependency=static_cast<int>(context.block->children.size())-1;
    context.pending=true; return true;
}
AnimatedBase& AnimatedBase::batch() {
    if (mAppendAnimation) { selectScriptOperand(); scriptAndThen(); }
    if (!mScripts) mScripts=std::make_shared<AnimationScriptState>();
    mScripts->editable();
    if (mWaitPending) {
        mScripts->contexts.back().delay+=mDelaySeconds;
        mScripts->contexts.back().pending=true;
    }
    finishAnimationRequest();
    mScripts->contexts.push_back({std::make_shared<ScriptNode>()}); return *this;
}
AnimatedBase& AnimatedBase::endBatch() {
    if (!mScripts || mScripts->contexts.size()<2 || mScripts->contexts.back().conditional || mScripts->contexts.back().sequential)
        throw std::logic_error("endBatch requires the innermost open group");
    mScripts->editable(); const auto context=mScripts->contexts.back();
    scriptNonempty(context.block);
    if (context.pending || context.parallelNext) throw std::logic_error("Batch placement requires a successor");
    mScripts->contexts.pop_back(); mScripts->append(context.block); return *this;
}
AnimatedBase& AnimatedBase::series() {
    batch(); mScripts->contexts.back().sequential=true; return *this;
}
AnimatedBase& AnimatedBase::endSeries() {
    if (!mScripts || mScripts->contexts.size()<2 || !mScripts->contexts.back().sequential || mScripts->contexts.back().conditional)
        throw std::logic_error("endSeries requires the innermost open series");
    mScripts->editable(); const auto context=mScripts->contexts.back();
    scriptNonempty(context.block);
    if (context.pending || context.parallelNext) throw std::logic_error("Series placement requires a successor");
    mScripts->contexts.pop_back(); mScripts->append(context.block); return *this;
}
AnimatedBase& AnimatedBase::andAlso() {
    selectScriptOperand(); mScripts->editable();
    if (!mScripts->recording && mScripts->contexts.size()==1) mScripts->placeSelectedPlayback();
    auto& context=mScripts->contexts.back();
    if (context.pending || context.parallelNext) throw std::logic_error("and requires an operand and no pending placement");
    if (context.block->children.empty()) throw std::logic_error("and must precede activation of its operand");
    context.parallelNext=true; return *this;
}
AnimatedBase& AnimatedBase::when(AnimationEvaluator evaluator) {
    if (!evaluator) throw std::invalid_argument("when requires an evaluator");
    if (!mScripts) mScripts=std::make_shared<AnimationScriptState>();
    mScripts->editable(); auto conditional=std::make_shared<ScriptNode>(); conditional->kind=ScriptNode::Conditional;
    conditional->evaluator=std::move(evaluator); auto branch=std::make_shared<ScriptNode>();
    conditional->children.push_back(branch); mScripts->contexts.push_back({branch,conditional}); return *this;
}
AnimatedBase& AnimatedBase::otherwise() {
    if (!mScripts || !mScripts->contexts.back().conditional || mScripts->contexts.back().alternative)
        throw std::logic_error("otherwise requires the innermost when branch");
    mScripts->editable(); auto& context=mScripts->contexts.back(); scriptNonempty(context.block);
    if (context.pending || context.parallelNext) throw std::logic_error("Branch placement requires a successor");
    auto branch=std::make_shared<ScriptNode>(); context.conditional->children.push_back(branch);
    context.block=std::move(branch); context.alternative=true; context.delay=0; context.dependency=-1; return *this;
}
AnimatedBase& AnimatedBase::endWhen() {
    if (!mScripts || !mScripts->contexts.back().conditional || mScripts->contexts.back().alternative)
        throw std::logic_error("endWhen requires the innermost when without otherwise");
    mScripts->editable(); const auto context=mScripts->contexts.back(); scriptNonempty(context.block);
    if (context.pending || context.parallelNext) throw std::logic_error("Branch placement requires a successor");
    mScripts->contexts.pop_back(); mScripts->append(context.conditional); return *this;
}
AnimatedBase& AnimatedBase::endOtherwise() {
    if (!mScripts || !mScripts->contexts.back().conditional || !mScripts->contexts.back().alternative)
        throw std::logic_error("endOtherwise requires the innermost otherwise branch");
    mScripts->editable(); const auto context=mScripts->contexts.back(); scriptNonempty(context.block);
    if (context.pending || context.parallelNext) throw std::logic_error("Branch placement requires a successor");
    mScripts->contexts.pop_back(); mScripts->append(context.conditional); return *this;
}
AnimatedBase& AnimatedBase::until(AnimationEvaluator evaluator) {
    if (!evaluator) throw std::invalid_argument("until requires an evaluator");
    selectScriptOperand();
    if (scriptChannels(mScripts->selected()).contains(animationChannel_CameraTransition)) throw std::logic_error("Camera transitions require a finite timed handoff");
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Until; node->evaluator=std::move(evaluator);
    mScripts->wrap(node); return *this;
}
AnimatedBase& AnimatedBase::yoyo() {
    for (const auto& track : mAnimations) if (track.operation==mAnimationOperation &&
        (track.value==&mDeltaXPerMs || track.value==&mDeltaYPerMs || track.value==&mDeltaFacingPerMs ||
         track.value==&mDeltaWidthPerMs || track.value==&mDeltaHeightPerMs))
        throw std::logic_error("Programmed rate animations cannot be reversed");
    selectScriptOperand();
    if (!scriptReversible(mScripts->selected())) throw std::logic_error("This animation block cannot be reversed");
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Yoyo; mScripts->wrap(node); return *this;
}
AnimatedBase& AnimatedBase::repeat(int count) {
    if (count < -1) throw std::invalid_argument("repeat requires a nonnegative count or omitted infinite count");
    selectScriptOperand();
    if (scriptChannels(mScripts->selected()).contains(animationChannel_CameraTransition)) throw std::logic_error("Start each Camera transition with transitionTo");
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Repeat; node->count=count;
    mScripts->wrap(node); return *this;
}
AnimatedBase& AnimatedBase::diminish(float factor, double seconds, EasingFunc easing) {
    if(diminishSampled(factor,seconds,easing))return *this;
    validateDuration(seconds);
    if (!std::isfinite(factor) || factor<0 || factor>1 || !easing) throw std::invalid_argument("diminish requires a factor from zero to one and easing");
    selectScriptOperand();
    if (!scriptNumeric(mScripts->selected())) throw std::logic_error("Diminution requires a reversible numeric trajectory");
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Gain; node->factor=factor; node->seconds=seconds; node->easing=easing;
    mScripts->wrap(node); return *this;
}
AnimatedBase& AnimatedBase::increase(float factor, double seconds, EasingFunc easing) {
    validateDuration(seconds);
    if (!std::isfinite(factor) || factor<1 || !easing) throw std::invalid_argument("increase requires a finite factor of at least one and easing");
    selectScriptOperand();
    if (!scriptNumeric(mScripts->selected())) throw std::logic_error("Amplification requires a reversible numeric trajectory");
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Gain; node->factor=factor; node->seconds=seconds; node->easing=easing;
    mScripts->wrap(node); return *this;
}
AnimatedBase& AnimatedBase::speedUp(float factor, double seconds, EasingFunc easing) {
    validateDuration(seconds);
    if (!std::isfinite(factor) || factor<=0 || !easing) throw std::invalid_argument("Playback rate must be finite and positive");
    selectScriptOperand();
    if (!scriptNumeric(mScripts->selected())) throw std::logic_error("Script clock modifiers do not support programmed rates or discrete actions");
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Rate; node->factor=factor; node->seconds=seconds; node->easing=easing;
    mScripts->wrap(node); return *this;
}
AnimatedBase& AnimatedBase::slowDown(float factor, double seconds, EasingFunc easing) {
    if (!std::isfinite(factor) || factor<=0) throw std::invalid_argument("Playback rate divisor must be finite and positive");
    return speedUp(1/factor,seconds,easing);
}
ScriptNodePtr AnimationScriptState::resolve(const ScriptNodePtr& source, size_t fieldCount, uint32 targetClass) {
    auto& library=scriptLibrary();
    std::set<std::string> stack;
    std::function<ScriptNodePtr(const std::string&)> resolveName;
    std::function<ScriptNodePtr(const ScriptNodePtr&)> resolve;
    resolve=[&](const ScriptNodePtr& source) {
        if (source->kind==ScriptNode::Invocation) {
            auto result=resolveName(source->name); result->name="@script:"+source->name; result->delay=source->delay; result->dependency=source->dependency; result->externalDependency=source->externalDependency; result->playback=source->playback;
            for(const auto& [type,handlers]:source->handlers) result->handlers[type].insert(result->handlers[type].end(),handlers.begin(),handlers.end());
            return result;
        }
        if (targetClass && source->requiredClass && source->requiredClass!=targetClass) throw std::logic_error("Animation target does not support this script capability");
        if(source->kind==ScriptNode::Stagger && targetClass) {
            auto result=resolve(source->children.at(0));
            for(const auto& [type,handlers]:source->handlers) result->handlers[type].insert(result->handlers[type].end(),handlers.begin(),handlers.end());
            result->delay=source->delay; result->dependency=source->dependency; result->externalDependency=source->externalDependency; return result;
        }
        auto result=std::make_shared<ScriptNode>(*source); result->children.clear();
        for (const auto& child : source->children) result->children.push_back(resolve(child));
        if ((result->kind==ScriptNode::Gain || result->kind==ScriptNode::Rate) && !scriptNumeric(result)) throw std::logic_error("Script modifier requires numeric pose channels");
        std::function<bool(const ScriptNodePtr&)> zero=[&](const ScriptNodePtr& node) {
            if (node->delay>0 || ((node->kind==ScriptNode::Operation || node->kind==ScriptNode::Command) && node->seconds>0) || node->kind==ScriptNode::Conditional || node->kind==ScriptNode::Until) return false;
            return std::all_of(node->children.begin(),node->children.end(),zero);
        };
        if (result->kind==ScriptNode::Repeat && result->count<0 && zero(result->children.at(0))) throw std::logic_error("Infinite repetition requires positive elapsed time");
        scriptValidateParallel(result);
        if (result->kind==ScriptNode::Yoyo && !scriptReversible(result)) throw std::logic_error("Script invocation cannot be reversed");
        for (const auto& value : result->values) if (value.field>=fieldCount) throw std::logic_error("Target does not support script animation channel");
        return result;
    };
    resolveName=[&](const std::string& scriptName) {
        if (!stack.insert(scriptName).second) throw std::logic_error("Recursive animation script: "+scriptName);
        const auto definition=library.find(scriptName);
        if (definition==library.end()) throw std::invalid_argument("Unknown animation script: "+scriptName);
        definition->second->mScripts->closed();
        auto result=resolve(definition->second->mScripts->contexts[0].block); stack.erase(scriptName); return result;
    };
    auto result=resolve(source);
    std::function<void(const ScriptNodePtr&)> validateLabels=[&](const ScriptNodePtr& scope) {
        std::set<std::string> names; std::vector<std::string> jumps;
        std::function<void(const ScriptNodePtr&)> labels=[&](const ScriptNodePtr& node) {
            if(node!=scope && node->kind==ScriptNode::Group && node->name.starts_with("@script:")) { validateLabels(node); return; }
            if(node->kind==ScriptNode::Mark && !names.insert(node->name).second) throw std::logic_error("Duplicate animation mark: "+node->name);
            if(node->kind==ScriptNode::Jump) jumps.push_back(node->name);
            for(const auto& child:node->children) labels(child);
        };
        labels(scope);
        for(const auto& name:jumps) {
            std::function<bool(const ScriptNodePtr&)> exists=[&](const ScriptNodePtr& node) {
                if(node->kind==ScriptNode::Mark && node->name==name) return true;
                return std::any_of(node->children.begin(),node->children.end(),exists);
            };
            if(!names.contains(name) && !exists(scope)) throw std::invalid_argument("Unknown animation mark: "+name);
        }
    };
    validateLabels(result);
    return result;
}
namespace {
ScriptNodePtr bindTroupe(const ScriptNodePtr& source, AnimatedBase& troupe) {
    auto result=cloneScript(source);
    if(source->kind==ScriptNode::Stagger) {
        result=std::make_shared<ScriptNode>();
        result->delay=source->delay; result->dependency=source->dependency; result->externalDependency=source->externalDependency; result->playback=source->playback;
        result->handlers=source->handlers;
        unsigned index=0;
        for(auto* member:troupe.animationTargets()) {
            member->validateTransformEdit(); member->validateProgrammedTransform();
            auto child=std::make_shared<ScriptNode>(); child->kind=ScriptNode::Target;
            child->delay=index++*source->seconds;
            if(!std::isfinite(child->delay)) throw std::invalid_argument("Stagger delay overflow");
            child->target=member->animationLifetime(); child->troupe=troupe.animationLifetime();
            auto block=AnimationScriptState::resolve(source->children.at(0),member->tweenFields().size(),member->scriptClassTag());
            if(block->kind!=ScriptNode::Group) { auto scope=std::make_shared<ScriptNode>(); scope->children.push_back(block); block=scope; }
            block->name="@script:@stagger"; child->children.push_back(block);
            result->children.push_back(child);
        }
    } else if(source->kind==ScriptNode::Operation || source->kind==ScriptNode::Flip || source->kind==ScriptNode::Command) {
        result=std::make_shared<ScriptNode>();
        result->delay=source->delay; result->dependency=source->dependency; result->externalDependency=source->externalDependency;
        result->playback=source->playback;
        result->handlers=source->handlers;
        for(auto* member:troupe.animationTargets()) {
            member->validateTransformEdit(); member->validateProgrammedTransform();
            auto leaf=cloneScript(source); leaf->delay=0; leaf->dependency=-1; leaf->externalDependency=0; leaf->playback=0;
            leaf->handlers.clear();
            leaf=AnimationScriptState::resolve(leaf,member->tweenFields().size(),member->scriptClassTag());
            auto child=std::make_shared<ScriptNode>(); child->kind=ScriptNode::Target;
            child->target=member->animationLifetime(); child->troupe=troupe.animationLifetime(); child->children.push_back(leaf);
            result->children.push_back(child);
        }
    } else {
        result->children.clear();
        for(const auto& child:source->children) result->children.push_back(bindTroupe(child,troupe));
    }
    return result;
}
}
AnimatedBase& AnimatedBase::playScript(const std::string& name) {
    auto& library=scriptLibrary();
    const auto found=library.find(name);
    if (found==library.end()) throw std::invalid_argument("Unknown animation script: "+name);
    if(!mScripts && isTroupe()) mScripts=std::make_shared<AnimationScriptState>();
    if (mScripts && (isTroupe() || mScripts->recording || mScripts->contexts.size()>1 || !mScripts->contexts[0].block->children.empty() || mScripts->contexts[0].pending)) {
        mScripts->editable(); auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Invocation; node->name=name;
        mScripts->append(node); return *this;
    }
    found->second->mScripts->closed();
    auto definition=AnimationScriptState::resolve(found->second->mScripts->contexts[0].block,tweenFields().size(),isTroupe()?0:scriptClassTag());
    definition->name="@script:"+name;
    if(isTroupe()) definition=bindTroupe(definition,*this);
    auto execution=std::make_unique<ScriptExecution>(definition);
    validateTransformEdit(); validateProgrammedTransform();
    if (!mScripts) mScripts=std::make_shared<AnimationScriptState>();
    mScripts->editable(); execution->id=mScripts->nextId++; mScripts->selectedRoot=mScripts->selectedExecution=execution.get(); mScripts->selectionPath.clear(); mScripts->executions.push_back(std::move(execution)); return *this;
}
AnimatedBase& AnimatedBase::stagger(double intervalSeconds) {
    validateDuration(intervalSeconds); selectScriptOperand();
    if(!isTroupe() && !mScripts->recording) return *this;
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Stagger; node->seconds=intervalSeconds;
    mScripts->wrap(node); return *this;
}
AnimatedBase& AnimatedBase::mark(const std::string& name, bool saveState) {
    if(name.empty()) throw std::invalid_argument("Mark name must not be empty");
    if(!mScripts) mScripts=std::make_shared<AnimationScriptState>();
    mScripts->editable();
    auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Mark; node->name=name; node->mode=saveState;
    mScripts->append(node); return *this;
}
AnimatedBase& AnimatedBase::on(const std::string& event, AnimationEventHandler handler) {
    if(event.empty()) throw std::invalid_argument("Animation event name must not be empty");
    if(!handler) throw std::invalid_argument("Animation event handler must be callable");
    if(mScripts && (mScripts->recording || mScripts->contexts.size()>1) && mScripts->contexts.back().block->children.empty()) {
        mScripts->editable(); mScripts->contexts.back().block->handlers[event].push_back(std::move(handler));
    } else {
        selectScriptOperand(); mScripts->editable();
        if(mScripts->contexts.back().parallelNext) throw std::logic_error("Complete andAlso before registering a handler");
        auto node=cloneScript(mScripts->selected());
        node->handlers[event].push_back(std::move(handler));
        if(!mScripts->recording && mScripts->contexts.size()==1 && mScripts->contexts[0].block->children.empty()) mScripts->selectedExecution->node=node;
        else mScripts->contexts.back().block->children.back()=node;
    }
    return *this;
}
AnimatedBase& AnimatedBase::triggerEvent(const std::string& name) {
    if(!scriptCustomEventName(name)) throw std::invalid_argument("triggerEvent requires a nonempty custom event name; PDG events are reserved");
    validateScriptEdit();
    if(mScripts && (mScripts->recording || mScripts->contexts.size()>1 || mScripts->contexts[0].pending)) {
        auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Emit; node->name=name;
        mScripts->append(node); return *this;
    }
    if(!mScripts) return *this;
    if(!mScripts->contexts[0].block->children.empty()) {
        // Snapshot registrations before dispatch so handlers may edit the graph.
        std::vector<AnimationEventHandler> handlers;
        for(const auto& node:{mScripts->selected(),mScripts->contexts[0].block})
            if(auto found=node->handlers.find(name);found!=node->handlers.end()) handlers.insert(handlers.end(),found->second.begin(),found->second.end());
        for(const auto& handler:handlers) handler({*this,name,"","",0,0,false,""});
    } else if(mScripts->selectedExecution) {
        auto* selected=mScripts->selectedExecution; auto* owner=selected;
        while(owner->parent) owner=owner->parent;
        selected->emit(name,*this);
        auto notifications=std::move(owner->notifications); owner->notifications.clear();
        for(const auto& event:notifications) if(auto target=event.target.lock();target && *target)
            event.handler({**target,event.type,event.scriptName,event.markName,event.elapsed,event.iteration,event.reverse,event.operationName});
    }
    return *this;
}
AnimatedBase& AnimatedBase::jumpToMark(const std::string& name, bool restoreState) {
    if(name.empty()) throw std::invalid_argument("Mark name must not be empty");
    if(!mScripts) throw std::logic_error("jumpToMark requires a script");
    mScripts->editable();
    if(mScripts->recording || mScripts->contexts.size()>1 || !mScripts->contexts[0].block->children.empty()) {
        auto node=std::make_shared<ScriptNode>(); node->kind=ScriptNode::Jump; node->name=name; node->mode=restoreState;
        mScripts->append(node); return *this;
    }
    if(!mScripts->selectedRoot) throw std::logic_error("jumpToMark requires a selected script");
    const auto fields=tweenFields(); std::vector<float> values;
    for(auto field:fields) values.push_back(*field);
    values.push_back(mFlipX); values.push_back(mFlipY);
    auto& selected=mScripts->selectedExecution->root();
    bool perMember=false;
    if(isTroupe()) {
        std::function<void(ScriptExecution&)> jumpMembers=[&](ScriptExecution& execution) {
            if(execution.node->kind==ScriptNode::Target) {
                std::vector<unsigned> path;
                if(execution.children[0]->findMark(name,path)) if(auto* member=execution.memberTarget()) {
                    auto current=ScriptExecution::readValues(*member);
                    execution.children[0]->jump(name,restoreState,current,*member);
                    const auto fields=member->tweenFields();
                    for(size_t i=0;i<fields.size();++i) *const_cast<float*>(fields[i])=current[i];
                    const bool beforeX=member->mFlipX,beforeY=member->mFlipY;
                    member->mFlipX=current[fields.size()]!=0; member->mFlipY=current[fields.size()+1]!=0;
                    if(beforeX!=member->mFlipX || beforeY!=member->mFlipY) member->flipChanged(beforeX!=member->mFlipX,beforeY!=member->mFlipY);
                    member->animationValuesChanged(); perMember=true;
                }
                return;
            }
            for(auto& child:execution.children) jumpMembers(*child);
        };
        jumpMembers(selected);
    }
    if(!perMember) selected.jump(name,restoreState,values,*this);
    mScripts->selectedExecution=mScripts->selectedRoot; mScripts->selectionPath.clear();
    for(size_t i=0;i<fields.size();++i) *const_cast<float*>(fields[i])=values[i];
    const bool previousX=mFlipX,previousY=mFlipY;
    mFlipX=values[fields.size()]!=0; mFlipY=values[fields.size()+1]!=0;
    if(previousX!=mFlipX || previousY!=mFlipY) flipChanged(previousX!=mFlipX,previousY!=mFlipY);
    animationValuesChanged(); return *this;
}
AnimatedBase& AnimatedBase::stopIt() {
    selectScriptOperand(); mScripts->editable();
    if (mScripts->recording) throw std::logic_error("Playback controls cannot be recorded without an execution handle");
    if (!mScripts->contexts[0].block->children.empty()) mScripts->selected()->playback|=2;
    else mScripts->selectedExecution->stopped=true;
    return *this;
}
AnimatedBase& AnimatedBase::pauseIt() {
    selectScriptOperand(); mScripts->editable();
    if (mScripts->recording) throw std::logic_error("Playback controls cannot be recorded without an execution handle");
    if (!mScripts->contexts[0].block->children.empty()) mScripts->selected()->playback|=1;
    else mScripts->selectedExecution->paused=true;
    return *this;
}
AnimatedBase& AnimatedBase::resumeIt() {
    selectScriptOperand(); mScripts->editable();
    if (mScripts->recording) throw std::logic_error("Playback controls cannot be recorded without an execution handle");
    if (!mScripts->contexts[0].block->children.empty()) mScripts->selected()->playback&=~1;
    else mScripts->selectedExecution->paused=false;
    return *this;
}
AnimatedBase& AnimatedBase::restartIt() {
    selectScriptOperand(); mScripts->editable();
    if (mScripts->recording) throw std::logic_error("Playback controls cannot be recorded without an execution handle");
    if (!mScripts->contexts[0].block->children.empty()) { mScripts->selected()->playback=0; return *this; }
    auto& execution=*mScripts->selectedExecution;
    auto definition=cloneScript(execution.node); definition->playback=0;
    const auto fields=tweenFields();
    for (auto channel : execution.channels) {
        if (channel<fields.size()) *const_cast<float*>(fields[channel])=execution.baseline.at(channel);
        else if (channel==fields.size()) mFlipX=execution.baseline.at(channel)!=0;
        else if (channel==fields.size()+1) mFlipY=execution.baseline.at(channel)!=0;
    }
    if(isTroupe()) for(auto* member:animationTargets()) {
        const auto found=execution.memberBaselines.find(member);
        if(found==execution.memberBaselines.end()) continue;
        const auto fields=member->tweenFields();
        for(auto channel:execution.channels) if(channel<fields.size()) *const_cast<float*>(fields[channel])=found->second.at(channel);
        member->animationValuesChanged();
    }
    execution.node=definition; execution.reset(); execution.children.clear();
    for (const auto& child : definition->children) {execution.children.push_back(std::make_unique<ScriptExecution>(child));execution.children.back()->parent=&execution;}
    if (execution.parent && execution.parent->node->kind==ScriptNode::Group) {
        auto& parent=*execution.parent; parent.complete=false; parent.finished=scriptInfinity;
        for (size_t i=0;i<parent.children.size();++i) if (parent.children[i].get()==&execution) {
            parent.starts.at(i)=parent.elapsed; parent.finishes.at(i)=scriptInfinity;
        }
    }
    animationValuesChanged(); return *this;
}
bool AnimatedBase::advanceScripts(double seconds, bool beginUpdate) {
    if (!mScripts || mScripts->recording) return false;
    auto ownedState=mScripts; auto& state=*ownedState;
    if (!std::isfinite(state.clock+seconds)) throw std::invalid_argument("Animation owner clock overflow");
    if (beginUpdate) ++state.tick;
    if (state.contexts.size()==1 && !state.contexts[0].block->children.empty() && !state.contexts[0].parallelNext) {
        auto definition=AnimationScriptState::resolve(state.contexts[0].block,tweenFields().size(),isTroupe()?0:scriptClassTag());
        if(isTroupe()) definition=bindTroupe(definition,*this);
        auto execution=std::make_unique<ScriptExecution>(definition);
        state.selectedRoot=execution.get(); state.selectionPath={static_cast<unsigned>(execution->children.size()-1)};
        execution->id=state.nextId++;
        for (auto& child : execution->children) child->id=state.nextId++;
        state.selectedExecution=execution->children.back().get(); state.executions.push_back(std::move(execution));
        if (state.contexts[0].pending && state.contexts[0].dependency>=0) {
            state.contexts[0].externalDependency=state.selectedExecution->id; state.contexts[0].dependency=-1;
        }
        state.contexts[0].block=std::make_shared<ScriptNode>();
    }
    if (state.evaluating) throw std::logic_error("Animation script playback cannot be reentered");
    state.evaluating=true;
    struct Guard { bool& flag; ~Guard(){flag=false;} } guard{state.evaluating};
    const auto fields=tweenFields(); std::vector<float> values;
    for (auto field : fields) values.push_back(*field);
    values.push_back(mFlipX); values.push_back(mFlipY);
    bool changed=false;
    const auto publish=[&](AnimatedBase& receiver,const std::vector<float>& current) {
        const auto fields=receiver.tweenFields();
        for (auto value : current) if (!std::isfinite(value)) throw std::runtime_error("Animation script produced a nonfinite value");
        for (size_t i=0;i<fields.size();++i) if (*fields[i]!=current[i]) {
            *const_cast<float*>(fields[i])=current[i]; changed=true;
        }
        const bool flipX=receiver.mFlipX,flipY=receiver.mFlipY;
        receiver.mFlipX=current[fields.size()]!=0; receiver.mFlipY=current[fields.size()+1]!=0;
        if (flipX!=receiver.mFlipX || flipY!=receiver.mFlipY) { receiver.flipChanged(flipX!=receiver.mFlipX,flipY!=receiver.mFlipY); changed=true; }
        receiver.animationValuesChanged();
    };
    std::vector<ScriptExecution::Notification> notifications;
    for (auto& execution : state.executions) {
        unsigned budget=0;
        try {
            double remaining=seconds;
            for(;;) {
                try { execution->advance(remaining,values,*this,budget,publish,state.tick); break; }
                catch(const ScriptJump& jump) {
                    if(jump.target==this) jump.scope->jump(jump.name,jump.restore,values,*this);
                    else {
                        auto current=ScriptExecution::readValues(*jump.target);
                        jump.scope->jump(jump.name,jump.restore,current,*jump.target);
                        publish(*jump.target,current);
                    }
                    if(state.selectedRoot==execution.get()) { state.selectedExecution=execution.get(); state.selectionPath.clear(); }
                    publish(*this,values); remaining=jump.remaining;
                    if(++budget>100000) throw std::runtime_error("Animation jumps made no bounded progress");
                }
            }
            if (execution->complete && !std::isfinite(execution->finished)) execution->finished=state.clock+seconds;
            for (auto& child : execution->children) if (child->complete && !std::isfinite(child->finished)) child->finished=state.clock+seconds;
            for(auto& event:execution->notifications) notifications.push_back(std::move(event));
            execution->notifications.clear();
        }
        catch (...) { execution->notifications.clear(); execution->stopped=true; throw; }
    }
    publish(*this,values);
    if (changed) animationValuesChanged();
    state.clock+=seconds;
    std::set<uint32> dependencies;
    std::function<void(const ScriptNodePtr&)> collect=[&](const ScriptNodePtr& node) {
        if (node->externalDependency) dependencies.insert(node->externalDependency);
        for (auto& child : node->children) collect(child);
    };
    collect(state.contexts[0].block);
    if (state.contexts[0].externalDependency) dependencies.insert(state.contexts[0].externalDependency);
    for (auto& execution : state.executions) if (!execution->complete) collect(execution->node);
    std::erase_if(state.executions,[&](const auto& execution){
        if (!execution->complete || execution.get()==state.selectedRoot || dependencies.contains(execution->id)) return false;
        for (auto& child : execution->children) if (dependencies.contains(child->id)) return false;
        return true;
    });
    auto completions=std::move(state.completions); state.completions.clear();
    state.evaluating=false;
    for (const auto& completion : completions) {
        Animation animation(const_cast<float*>(fields.at(completion.field)),completion.value,completion.easing,0,completion.seconds);
        animation.completion=completion.kind; easingCompleted(animation);
    }
    for(const auto& event:notifications) if(auto target=event.target.lock();target && *target)
        event.handler({**target,event.type,event.scriptName,event.markName,event.elapsed,event.iteration,event.reverse,event.operationName});
    return changed;
}

namespace {
uint32 animationReferenceSize(ISerializer* serializer,AnimatedBase* member) {
    auto* owner=member?member->snapshotAnimationOwner():nullptr;
    return 1+serializer->sizeof_obj(owner?owner:member)+(owner?serializer->sizeof_uint(member->snapshotAnimationId()):0);
}
void writeAnimationReference(ISerializer* serializer,AnimatedBase* member) {
    auto* owner=member?member->snapshotAnimationOwner():nullptr;
    serializer->serialize_1u(owner?1:0); serializer->serialize_obj(owner?owner:member);
    if(owner) serializer->serialize_uint(member->snapshotAnimationId());
}
struct AnimationReference { AnimatedBase* member; std::shared_ptr<AnimatedBase> retained; };
AnimationReference readAnimationReference(IDeserializer* reader) {
    const auto kind=reader->deserialize_1u();
    if(kind>1) throw std::runtime_error("Invalid animation member reference");
    auto* object=reader->deserialize_obj(); auto* owner=dynamic_cast<AnimatedBase*>(object);
    if(object && !owner) { object->release(); throw std::runtime_error("Invalid animation member owner"); }
    std::shared_ptr<AnimatedBase> retained(owner,[](AnimatedBase* value){if(value) value->release();});
    auto* member=kind && owner?owner->snapshotAnimationMember(reader->deserialize_uint()):owner;
    if(kind && !member) throw std::runtime_error("Missing animation member in snapshot owner");
    return {member,std::move(retained)};
}
}
#include "animation-argument-codec.inc"

uint32 Troupe::getSerializedSize(ISerializer* serializer) const {
    uint32 size=5+serializer->sizeof_uint(getMemberCount());
    for(const auto& weak:mMembers) if(auto entry=weak.lock();entry && *entry) size+=animationReferenceSize(serializer,*entry);
    return size+AnimatedBase::getSerializedSize(serializer);
}
void Troupe::serialize(ISerializer* serializer) const {
    serializer->serialize_4u(0x54525045); serializer->serialize_1u(1);
    serializer->serialize_uint(getMemberCount());
    for(const auto& weak:mMembers) if(auto entry=weak.lock();entry && *entry) writeAnimationReference(serializer,*entry);
    AnimatedBase::serialize(serializer);
}
void Troupe::deserialize(IDeserializer* deserializer) {
    if(deserializer->deserialize_4u()!=0x54525045 || deserializer->deserialize_1u()!=1) throw std::runtime_error("Unsupported Troupe snapshot");
    const auto count=deserializer->deserialize_uint();
    if(count>100000) throw std::runtime_error("Troupe snapshot exceeds member limit");
    clear();
    for(uint32 i=0;i<count;++i) {
        auto reference=readAnimationReference(deserializer);
        if(!reference.member) throw std::runtime_error("Invalid Troupe snapshot member");
        add(*reference.member); mRestoredMembers.push_back(std::move(reference.retained));
    }
    AnimatedBase::deserialize(deserializer);
}
Troupe& Troupe::add(AnimatedBase& member) {
    validateScriptEdit();
    if(member.mScripts && member.mScripts->recording) throw std::invalid_argument("Animation recorders cannot be Troupe members");
    if(&member==this) throw std::invalid_argument("A Troupe cannot contain itself");
    if(auto* nested=dynamic_cast<Troupe*>(&member)) {
        if(nested->contains(*this)) throw std::invalid_argument("Troupe membership cannot form a cycle");
    }
    for(const auto& weak:mMembers) if(auto entry=weak.lock();entry && *entry==&member) return *this;
    mMembers.push_back(member.animationLifetime()); return *this;
}
Troupe& Troupe::remove(AnimatedBase& member) {
    validateScriptEdit();
    std::erase_if(mMembers,[&](const auto& weak){const auto entry=weak.lock();return !entry || *entry==&member;});
    std::erase_if(mRestoredMembers,[&](const auto& value){return value.get()==&member;}); return *this;
}
Troupe& Troupe::clear() { validateScriptEdit(); mMembers.clear(); mRestoredMembers.clear(); return *this; }
bool Troupe::contains(const AnimatedBase& member) const {
    for(const auto& weak:mMembers) if(auto entry=weak.lock();entry && *entry) {
        if(*entry==&member) return true;
        if(auto* nested=dynamic_cast<Troupe*>(*entry);nested && nested->contains(member)) return true;
    }
    return false;
}
unsigned Troupe::getMemberCount() const {
    unsigned count=0; for(const auto& weak:mMembers) if(auto entry=weak.lock();entry && *entry) ++count; return count;
}
std::vector<AnimatedBase*> Troupe::animationTargets() const {
    std::vector<AnimatedBase*> result;
    for(const auto& weak:mMembers) if(auto entry=weak.lock();entry && *entry) {
        std::vector<AnimatedBase*> targets;
        if(auto* nested=dynamic_cast<Troupe*>(*entry)) targets=nested->animationTargets();
        else targets.push_back(*entry);
        for(auto* target:targets) if(std::find(result.begin(),result.end(),target)==result.end()) result.push_back(target);
    }
    return result;
}

namespace {
struct ScriptWriter {
    ISerializer* serializer;
    bool writing;
    AnimatedBase& receiver;
    uint32 size=0;
    void object(AnimatedBase* target) { size+=animationReferenceSize(serializer,target); if(writing) writeAnimationReference(serializer,target); }
    void string(const std::string& value) {
        if(value.size()>1000000) throw std::runtime_error("Animation snapshot name exceeds limit");
        size+=serializer->sizeof_mem(value.data(),value.size());
        if(writing) serializer->serialize_mem(value.data(),value.size());
    }
    void tracks(const std::vector<AnimatedBase::Animation>& values,AnimatedBase& target) {
        const auto fields=ScriptExecution::fields(target); integer(values.size());
        for(const auto& a:values) {
            auto field=std::find(fields.begin(),fields.end(),a.value);
            if(field==fields.end() || easingFuncToId(a.easing)>=NUM_BUILTIN_EASINGS) throw std::runtime_error("Unsupported saved mark animation");
            byte(field-fields.begin()); byte(easingFuncToId(a.easing)); byte(a.rotationDirection); byte(ScriptExecution::trackFlags(target,a));
            real(a.delaySeconds); real(a.durationSeconds); real(a.elapsedSeconds); floating(a.beginVal); floating(a.deltaVal); floating(a.targetVal);
        }
    }
    void byte(uint8 value) { ++size; if (writing) serializer->serialize_1u(value); }
    void integer(uint32 value) { size+=serializer->sizeof_uint(value); if (writing) serializer->serialize_uint(value); }
    void real(double value) { size+=serializer->sizeof_d(value); if (writing) serializer->serialize_d(value); }
    void floating(float value) { size+=serializer->sizeof_f(value); if (writing) serializer->serialize_f(value); }
    template<class T> void numbers(const std::vector<T>& values) {
        integer(values.size());
        for (auto value : values) {
            if constexpr (std::is_same_v<T,float>) floating(value);
            else if constexpr (std::is_same_v<T,double>) real(value);
            else integer(value);
        }
    }
    void definition(const ScriptNodePtr& node) {
        if (!node->handlers.empty() || node->evaluator || easingFuncToId(node->easing)>=NUM_BUILTIN_EASINGS) throw std::runtime_error("Animation snapshots cannot store runtime callback resources");
        if (node->kind==ScriptNode::Invocation) throw std::runtime_error("Publish script invocations before saving an animation snapshot");
        if(node->kind==ScriptNode::Stagger) {
            auto child=cloneScript(node->children.at(0)); child->delay=node->delay; child->dependency=node->dependency; child->externalDependency=node->externalDependency;
            definition(child); return;
        }
        if (node->kind==ScriptNode::Emit && (!scriptCustomEventName(node->name) || node->name.size()>1000000))
            throw std::runtime_error("Invalid custom animation event in snapshot");
        byte(node->kind); byte(easingFuncToId(node->easing)); byte(node->mode); byte(node->direction); byte(node->playback); byte(node->completion);
        real(node->seconds); real(node->delay); floating(node->factor);
        integer(static_cast<uint32>(node->count)); integer(static_cast<uint32>(node->dependency)); integer(node->externalDependency); integer(node->requiredClass);
        integer(node->values.size()); for (const auto& value : node->values) { integer(value.field); floating(value.target); }
        if(node->kind==ScriptNode::Target) {
            auto member=node->target.lock(), owner=node->troupe.lock(); object(member?*member:nullptr); object(owner?*owner:nullptr);
        }
        integer(node->children.size()); for (const auto& child : node->children) definition(child);
        if(node->kind!=ScriptNode::Emit) string(node->name);
        if (node->kind==ScriptNode::Emit) {
            size+=serializer->sizeof_mem(node->name.data(),static_cast<uint32>(node->name.size()));
            if (writing) serializer->serialize_mem(node->name.data(),static_cast<uint32>(node->name.size()));
        }

        if(node->kind==ScriptNode::Command) {
            integer(node->arguments.size());
            for(const auto& argument:node->arguments) size+=serializeAnimationArgument(argument,serializer,writing);
        }
    }
    void execution(const ScriptExecution& instance) {
        definition(instance.node);
        byte((instance.active?1:0)|(instance.complete?2:0)|(instance.paused?4:0)|(instance.stopped?8:0)|(instance.reverse?16:0)|(instance.completionSent?32:0));
        real(instance.elapsed); real(instance.duration); real(instance.born); real(instance.finished); integer(instance.id); integer(instance.iteration); integer(static_cast<uint32>(instance.branch));
        numbers(instance.baseline); numbers(instance.logical); numbers(instance.begin); numbers(instance.end);
        numbers(instance.channels); numbers(instance.canceled); numbers(instance.starts); numbers(instance.finishes);
        integer(instance.children.size()); for (const auto& child : instance.children) execution(*child);
        integer(instance.history.size()); for (const auto& past : instance.history) execution(*past);
        numbers(instance.memberValues);
        const auto liveMembers=receiver.animationTargets();
        const auto liveBaseline=[&](const auto& item) { return std::find(liveMembers.begin(),liveMembers.end(),item.first)!=liveMembers.end(); };
        integer(std::count_if(instance.memberBaselines.begin(),instance.memberBaselines.end(),liveBaseline));
        for(const auto& item:instance.memberBaselines) if(liveBaseline(item)) { object(item.first); numbers(item.second); }
        integer(instance.marks.size());
        for(const auto& [name,mark]:instance.marks) {
            string(name); numbers(mark.values); tracks(mark.animations,receiver); numbers(std::vector<double>(mark.credits.begin(),mark.credits.end())); execution(*mark.cursor);
            integer(mark.members.size());
            for(const auto& saved:mark.members) {
                auto member=saved.lifetime.lock(); auto* target=member?*member:nullptr;
                if(!target) throw std::runtime_error("Expired saved mark member");
                object(target); numbers(saved.values); tracks(saved.animations,*target); numbers(std::vector<double>(saved.credits.begin(),saved.credits.end()));
            }
        }

    }
    void state(const std::shared_ptr<AnimationScriptState>& state) {
        if (!state) { byte(0); return; }
        if(state->contexts[0].parallelNext) throw std::runtime_error("Complete andAlso construction before saving a snapshot");
        if (state->recording || state->contexts.size()!=1)
            throw std::runtime_error("Complete animation construction before saving a snapshot");
        byte(3); real(state->clock); integer(state->nextId);
        real(state->contexts[0].delay); integer(state->contexts[0].externalDependency); integer(static_cast<uint32>(state->contexts[0].dependency)); byte(state->contexts[0].pending);
        definition(AnimationScriptState::resolve(state->contexts[0].block,UINT32_MAX));
        integer(state->executions.size());
        int selected=-1;
        for (size_t i=0;i<state->executions.size();++i) {
            if (state->executions[i].get()==state->selectedRoot) selected=i;
            execution(*state->executions[i]);
        }
        integer(static_cast<uint32>(selected)); numbers(state->selectionPath);
    }
};
struct ScriptReader {
    IDeserializer* reader;
    size_t fieldCount;
    AnimatedBase& receiver;
    bool extended=false, commands=false;
    std::vector<std::shared_ptr<AnimatedBase>> objects;
    unsigned depth=0, total=0;
    AnimatedBase* object() {
        auto reference=readAnimationReference(reader);
        auto* target=reference.member;
        if(reference.retained.get()!=&receiver) objects.push_back(std::move(reference.retained));
        return target;
    }
    std::string string() {
        const auto length=reader->deserialize_memGetLen();
        if(length>1000000) throw std::runtime_error("Animation snapshot name exceeds limit");
        std::string value(length,0);
        if(reader->deserialize_mem(value.data(),length)!=length) throw std::runtime_error("Truncated animation name");
        return value;
    }
    std::vector<AnimatedBase::Animation> tracks(AnimatedBase& target) {
        std::vector<AnimatedBase::Animation> result; const auto fields=ScriptExecution::fields(target);
        const auto length=count();
        for(uint32 i=0;i<length;++i) {
            AnimatedBase::Animation a; const auto field=reader->deserialize_1u(); a.easing=easingIdToFunc(reader->deserialize_1u());
            a.rotationDirection=reader->deserialize_1u(); ScriptExecution::readFlags(target,a,reader->deserialize_1u());
            a.delaySeconds=real(); a.durationSeconds=real(); a.elapsedSeconds=real(); a.beginVal=floating(); a.deltaVal=floating(); a.targetVal=floating();
            if(field>=fields.size() || !a.easing || a.rotationDirection>rotationDirection_CounterClockwise || a.elapsedSeconds>a.durationSeconds) throw std::runtime_error("Invalid saved mark animation");
            a.value=const_cast<float*>(fields[field]); result.push_back(a);
        }
        return result;
    }
    std::array<double,5> credits() {
        const auto values=numbers<double>(); std::array<double,5> result{};
        if(values.size()!=5 || std::any_of(values.begin(),values.end(),[](double value){return !std::isfinite(value);})) throw std::runtime_error("Invalid saved integration credits");
        std::copy(values.begin(),values.end(),result.begin()); return result;
    }
    uint32 integer() { return reader->deserialize_uint(); }
    uint32 count() {
        const auto value=integer();
        if (value>100000 || (total+=value)>1000000) throw std::runtime_error("Animation script snapshot exceeds size limits");
        return value;
    }
    double real() {
        const auto value=reader->deserialize_d();
        if (!std::isfinite(value) || value<0) throw std::runtime_error("Invalid animation script clock");
        return value;
    }
    float floating() {
        const auto value=reader->deserialize_f();
        if (!std::isfinite(value)) throw std::runtime_error("Invalid animation script value");
        return value;
    }
    template<class T> std::vector<T> numbers() {
        std::vector<T> result;
        const auto size=count(); result.reserve(size);
        for (uint32 i=0;i<size;++i) {
            if constexpr(std::is_same_v<T,float>) result.push_back(floating());
            else if constexpr(std::is_same_v<T,double>) {
                const auto value=reader->deserialize_d();
                if (std::isnan(value) || value<0) throw std::runtime_error("Invalid animation script placement");
                result.push_back(value);
            } else result.push_back(integer());
        }
        return result;
    }
    ScriptNodePtr definition() {
        if (++depth>256) throw std::runtime_error("Animation script snapshot nesting exceeds limits");
        auto node=std::make_shared<ScriptNode>();
        const auto kind=reader->deserialize_1u();
        if ((kind>ScriptNode::Flip && kind!=ScriptNode::Emit && !(commands && kind==ScriptNode::Command) && !(extended && (kind==ScriptNode::Mark || kind==ScriptNode::Jump || kind==ScriptNode::Target))) || kind==ScriptNode::Conditional || kind==ScriptNode::Until)
            throw std::runtime_error("Unsupported animation script snapshot block");
        node->kind=static_cast<ScriptNode::Kind>(kind);
        node->easing=easingIdToFunc(reader->deserialize_1u());
        node->mode=reader->deserialize_1u(); node->direction=reader->deserialize_1u(); node->playback=reader->deserialize_1u(); node->completion=reader->deserialize_1u();
        node->seconds=real(); node->delay=real(); node->factor=floating();
        node->count=static_cast<int32>(integer()); node->dependency=static_cast<int32>(integer()); node->externalDependency=integer(); node->requiredClass=integer();
        if (node->completion>3 || node->playback>3 || !node->easing || node->mode>(node->kind==ScriptNode::Flip?animationMode_Toggle:animationMode_Multiply) || node->direction>rotationDirection_CounterClockwise || node->count<-1 || node->dependency<-1 ||
            (node->kind==ScriptNode::Gain && node->factor<0) || (node->kind==ScriptNode::Rate && node->factor<=0))
            throw std::runtime_error("Invalid animation script snapshot parameters");
        const auto values=count();
        for (uint32 i=0;i<values;++i) {
            const auto field=integer(); const auto target=floating();
            if (field>=fieldCount-2) throw std::runtime_error("Unsupported animation script snapshot channel");
            node->values.push_back({field,target});
        }
        const auto previousFieldCount=fieldCount;
        if(node->kind==ScriptNode::Target) {
            auto* target=object(); auto* owner=object();
            if(target) node->target=target->animationLifetime();
            if(owner && !owner->isTroupe()) throw std::runtime_error("Invalid animation Troupe reference");
            if(owner) node->troupe=owner->animationLifetime();
            if(target) fieldCount=ScriptExecution::fields(*target).size()+2;
        }
        const auto children=count();
        for (uint32 i=0;i<children;++i) {
            auto child=definition();
            if (child->dependency>=static_cast<int>(i)) throw std::runtime_error("Invalid animation script dependency");
            node->children.push_back(std::move(child));
        }
        fieldCount=previousFieldCount;
        if(extended && node->kind!=ScriptNode::Emit) node->name=string();
        if ((node->kind==ScriptNode::Operation || node->kind==ScriptNode::Flip) && (node->values.empty() || !node->children.empty()))
            throw std::runtime_error("Invalid animation script operation");
        if (node->kind!=ScriptNode::Operation && node->kind!=ScriptNode::Flip && node->kind!=ScriptNode::Group && node->kind!=ScriptNode::Emit && node->kind!=ScriptNode::Mark && node->kind!=ScriptNode::Jump && node->kind!=ScriptNode::Command && node->children.size()!=1)
            throw std::runtime_error("Invalid animation script modifier");
        if (node->kind==ScriptNode::Flip && (node->values.size()!=1 || node->values[0].field>animationFlipAxis_Y || node->seconds!=0 ||
            (node->values[0].target!=0 && node->values[0].target!=1))) throw std::runtime_error("Invalid animation script flip");
        if (node->kind==ScriptNode::Emit) {
            const auto length=reader->deserialize_memGetLen();
            if (!length || length>1000000 || !node->children.empty() || !node->values.empty() || node->seconds!=0)
                throw std::runtime_error("Invalid custom animation event in snapshot");
            node->name.resize(length);
            if (reader->deserialize_mem(node->name.data(),length)!=length || !scriptCustomEventName(node->name))
                throw std::runtime_error("Invalid custom animation event name in snapshot");
        }
        if((node->kind==ScriptNode::Mark || node->kind==ScriptNode::Jump) && (node->name.empty() || node->mode>1 || !node->children.empty() || !node->values.empty() || node->seconds!=0)) throw std::runtime_error("Invalid animation mark");
        if(node->kind==ScriptNode::Command) {
            if(node->name.empty() || !node->values.empty()) throw std::runtime_error("Invalid semantic animation command");
            const auto arguments=count();
            for(uint32 i=0;i<arguments;++i) node->arguments.push_back(deserializeAnimationArgument(reader));
        }
        --depth; return node;
    }
    std::unique_ptr<ScriptExecution> execution(bool attach=true) {
        if (++depth>256) throw std::runtime_error("Animation execution snapshot nesting exceeds limits");
        auto instance=std::make_unique<ScriptExecution>(definition());
        const auto flags=reader->deserialize_1u(); if (flags>63) throw std::runtime_error("Invalid animation script flags");
        instance->active=flags&1; instance->complete=flags&2; instance->paused=flags&4; instance->stopped=flags&8; instance->reverse=flags&16; instance->completionSent=flags&32;
        instance->elapsed=real(); instance->duration=real(); instance->born=real();
        instance->finished=reader->deserialize_d();
        if (std::isnan(instance->finished) || instance->finished<0) throw std::runtime_error("Invalid completion clock");
        instance->id=integer(); instance->iteration=static_cast<int32>(integer()); instance->branch=static_cast<int32>(integer());
        instance->baseline=numbers<float>(); instance->logical=numbers<float>(); instance->begin=numbers<float>(); instance->end=numbers<float>();
        instance->channels=numbers<unsigned>(); instance->canceled=numbers<unsigned>(); instance->starts=numbers<double>(); instance->finishes=numbers<double>();
        if (instance->active && (instance->baseline.size()!=fieldCount || instance->logical.size()!=fieldCount))
            throw std::runtime_error("Invalid animation script baseline");
        if (instance->iteration<0 || instance->branch!=-1 || (instance->complete && instance->elapsed>instance->duration))
            throw std::runtime_error("Invalid animation script cursor");
        for (auto field : instance->canceled) if (field>=fieldCount) throw std::runtime_error("Invalid canceled animation channel");
        for (auto field : instance->channels) if (field>=fieldCount) throw std::runtime_error("Invalid animation script owned channel");
        if (instance->active && instance->node->kind==ScriptNode::Operation &&
            (instance->begin.size()!=instance->node->values.size() || instance->end.size()!=instance->begin.size()))
            throw std::runtime_error("Invalid animation script resolved trajectory");
        const auto children=count();
        if (children!=instance->children.size()) throw std::runtime_error("Invalid animation script execution children");
        const auto previousFieldCount=fieldCount;
        if(instance->node->kind==ScriptNode::Target) if(auto* member=instance->memberTarget()) fieldCount=ScriptExecution::fields(*member).size()+2;
        instance->children.clear();
        for (uint32 i=0;i<children;++i) { instance->children.push_back(execution(attach)); instance->children.back()->parent=instance.get(); }
        if (instance->active && instance->node->kind==ScriptNode::Group &&
            (instance->starts.size()!=children || instance->finishes.size()!=children)) throw std::runtime_error("Invalid animation group placement");
        const auto history=count(); for (uint32 i=0;i<history;++i) instance->history.push_back(execution(false));
        fieldCount=previousFieldCount;
        if(extended) {
            instance->memberValues=numbers<float>();
            const auto members=count();
            for(uint32 i=0;i<members;++i) { auto* member=object(); auto values=numbers<float>(); if(!member || values.size()!=ScriptExecution::fields(*member).size()+2) throw std::runtime_error("Invalid Troupe baseline"); instance->memberBaselines.emplace(member,std::move(values)); }
            const auto marks=count();
            for(uint32 i=0;i<marks;++i) {
                auto name=string(); ScriptExecution::MarkState saved;
                saved.values=numbers<float>(); saved.animations=tracks(receiver); saved.credits=credits(); saved.cursor=execution(false);
                if(name.empty() || saved.values.size()!=ScriptExecution::fields(receiver).size()+2 || instance->marks.contains(name)) throw std::runtime_error("Invalid saved mark state");
                const auto members=count();
                for(uint32 j=0;j<members;++j) { auto* member=object(); auto values=numbers<float>(); if(!member || values.size()!=ScriptExecution::fields(*member).size()+2) throw std::runtime_error("Invalid saved mark member"); auto animations=tracks(*member); auto credit=credits(); saved.members.push_back({member->animationLifetime(),std::move(values),std::move(animations),credit}); }
                instance->marks.emplace(std::move(name),std::move(saved));
            }
            if(attach) ScriptExecution::attach(*instance);
        }
        --depth; return instance;
    }
    std::shared_ptr<AnimationScriptState> state() {
        const auto flag=reader->deserialize_1u(); if (flag==0) return {};
        if (flag!=1 && flag!=2 && flag!=3) throw std::runtime_error("Invalid animation script state flag");
        extended=flag>=2; commands=flag>=3;
        auto state=std::make_shared<AnimationScriptState>();
        state->clock=real(); state->nextId=integer();
        state->contexts[0].delay=real(); state->contexts[0].externalDependency=integer(); state->contexts[0].dependency=static_cast<int32>(integer());
        state->contexts[0].pending=reader->deserialize_1u()!=0;
        state->contexts[0].block=definition();
        if (state->contexts[0].block->kind!=ScriptNode::Group) throw std::runtime_error("Invalid animation script root");
        if (state->contexts[0].dependency<-1 || state->contexts[0].dependency>=static_cast<int>(state->contexts[0].block->children.size())) throw std::runtime_error("Invalid pending script dependency");
        const auto size=count(); for (uint32 i=0;i<size;++i) state->executions.push_back(execution());
        const auto selected=static_cast<int32>(integer());
        if (selected<-1 || selected>=static_cast<int>(size)) throw std::runtime_error("Invalid selected animation execution");
        state->selectionPath=numbers<unsigned>();
        if (selected>=0) {
            state->selectedRoot=state->selectedExecution=state->executions[selected].get();
            for (auto index : state->selectionPath) {
                if (index>=state->selectedExecution->children.size()) throw std::runtime_error("Invalid animation selection path");
                state->selectedExecution=state->selectedExecution->children[index].get();
            }
        } else if (!state->selectionPath.empty()) throw std::runtime_error("Invalid detached animation selection");
        return state;
    }
};
} // namespace
uint32 AnimatedBase::scriptSerializedSize(ISerializer* serializer) const {
    ScriptWriter writer{serializer,false,*const_cast<AnimatedBase*>(this)}; writer.state(mScripts); return writer.size;
}
void AnimatedBase::serializeScripts(ISerializer* serializer) const {
    ScriptWriter validation{serializer,false,*const_cast<AnimatedBase*>(this)}; validation.state(mScripts);
    ScriptWriter writer{serializer,true,*const_cast<AnimatedBase*>(this)}; writer.state(mScripts);
}
void AnimatedBase::deserializeScripts(IDeserializer* deserializer) {
    ScriptReader reader{deserializer,tweenFields().size()+2,*this,false,false,{}};
    auto state=reader.state(); mScripts=std::move(state); mSnapshotScriptObjects=std::move(reader.objects);
}
void AnimatedBase::copyScriptStateFrom(const AnimatedBase& source) {
    mSnapshotScriptObjects=source.mSnapshotScriptObjects;
    if (!source.mScripts) { mScripts.reset(); return; }
    if (source.mScripts->recording || source.mScripts->contexts.size()!=1) throw std::logic_error("Cannot copy an animation recorder");
    auto state=std::make_shared<AnimationScriptState>();
    state->clock=source.mScripts->clock; state->nextId=source.mScripts->nextId;
    state->contexts[0]=source.mScripts->contexts[0]; state->contexts[0].block=cloneScript(state->contexts[0].block);
    for (const auto& instance : source.mScripts->executions) {
        auto copy=std::make_unique<ScriptExecution>(*instance);
        if (instance.get()==source.mScripts->selectedRoot) {
            state->selectedRoot=state->selectedExecution=copy.get(); state->selectionPath=source.mScripts->selectionPath;
            for (auto index : state->selectionPath) state->selectedExecution=state->selectedExecution->children.at(index).get();
        }
        state->executions.push_back(std::move(copy));
    }
    const auto before=source.tweenFields(),after=tweenFields();
    std::function<void(ScriptExecution&)> rebindMarks=[&](ScriptExecution& execution) {
        for(auto& [name,mark]:execution.marks) {
            for(auto& animation:mark.animations) {
                const auto field=std::find(before.begin(),before.end(),animation.value);
                if(field==before.end()) throw std::logic_error("Cannot copy this mark animation channel");
                animation.value=const_cast<float*>(after.at(field-before.begin()));
            }
            rebindMarks(*mark.cursor);
        }
        for(auto& child:execution.children) rebindMarks(*child);
    };
    for(auto& execution:state->executions) rebindMarks(*execution);
    mScripts=std::move(state);
}
void AnimatedBase::rebaseScriptState(const Offset& translation, float rotation) {
    if (!mScripts || mScripts->recording) return;
    const float offsets[]={translation.x,translation.y,rotation};
    std::function<bool(const ScriptNodePtr&,unsigned)> relativeOnly=[&](const ScriptNodePtr& node,unsigned field) {
        for (auto& value : node->values) if (node->kind==ScriptNode::Operation && value.field==field && node->mode!=animationMode_Add) return false;
        return std::all_of(node->children.begin(),node->children.end(),[&](const auto& child){return relativeOnly(child,field);});
    };
    std::function<void(ScriptExecution&)> rebase=[&](ScriptExecution& execution) {
        if (execution.active) {
            for (unsigned field=animationChannel_LocationX;field<=animationChannel_Facing;++field) if (relativeOnly(execution.node,field)) {
                execution.baseline.at(field)+=offsets[field]; execution.logical.at(field)+=offsets[field];
            }
            if (execution.node->kind==ScriptNode::Operation && execution.node->mode==animationMode_Add)
                for (size_t i=0;i<execution.node->values.size();++i) {
                    const auto field=execution.node->values[i].field;
                    if (field<animationChannel_Width) {execution.begin[i]+=offsets[field];execution.end[i]+=offsets[field];}
                }
        }
        for (auto& child : execution.children) rebase(*child);
        for (auto& past : execution.history) rebase(*past);
    };
    for (auto& execution : mScripts->executions) rebase(*execution);
}
bool AnimatedBase::hasScriptAnimations() const {
    for(const auto& weak:mExternalScriptExecutions) if(auto entry=weak.lock();entry && *entry && (*entry)->pending()) return true;
    if (!mScripts || mScripts->recording) return false;
    if (!mScripts->contexts[0].block->children.empty()) return true;
    std::function<bool(const ScriptExecution&)> pending=[&](const ScriptExecution& instance) {
        if (instance.complete || instance.stopped) return false;
        if (instance.node->kind==ScriptNode::Operation || instance.node->kind==ScriptNode::Flip || instance.node->kind==ScriptNode::Emit || instance.node->kind==ScriptNode::Mark || instance.node->kind==ScriptNode::Jump || instance.node->kind==ScriptNode::Command || instance.reverse) return true;
        if (instance.node->kind==ScriptNode::Conditional && instance.branch>=0) return pending(*instance.children[instance.branch]);
        for (size_t i=0;i<instance.children.size();++i) {
            const auto& child=*instance.children[i];
            const int dependency=child.node->dependency;
            if (dependency>=0 && !instance.children[dependency]->complete && !pending(*instance.children[dependency])) continue;
            if (pending(child)) return true;
        }
        return false;
    };
    return std::any_of(mScripts->executions.begin(),mScripts->executions.end(),[&](const auto& instance){return pending(*instance);});
}
void AnimatedBase::enqueueScriptCompletion(unsigned field, float value, EasingFunc easing, double seconds, uint8 completion) {
    if(!mScripts) mScripts=std::make_shared<AnimationScriptState>();
    mScripts->completions.push_back({field,value,easing,seconds,completion});
}
double AnimatedBase::scriptOwnerTime() const { return mScripts?mScripts->clock:0; }
double AnimatedBase::scriptDependencyStart(uint32 id) const {
    if (mScripts) for (auto& root : mScripts->executions) {
        if (root->id==id) return root->finished;
        for (auto& child : root->children) if (child->id==id) return child->finished;
    }
    return scriptInfinity;
}
void AnimatedBase::selectNativeAnimation() {
    if (mScripts && !mScripts->recording && mScripts->contexts.size()==1 && mScripts->contexts[0].block->children.empty()) {
        mScripts->selectedRoot=mScripts->selectedExecution=nullptr; mScripts->selectionPath.clear();
    }
}
void AnimatedBase::validateUnrecordedOperation(const char* name) const {
    // Non-chainable methods operate immediately on live receivers, even while
    // building a script. A standalone recorder has no live receiver to mutate.
    if (mScripts && mScripts->recording)
        throw std::logic_error(std::string(name)+" requires a live animation target");
}
void AnimatedBase::validateScriptRead() const {
    if (mScripts && mScripts->recording) throw std::logic_error("Animation definitions have no live target state");
}
void AnimatedBase::validateScriptControl() const {
    validateScriptEdit();
    if (mScripts && mScripts->recording) throw std::logic_error("Schedule controls cannot be recorded in animation definitions");
}
void AnimatedBase::validateScriptEdit() const {
    if (mScripts) mScripts->editable();
}
void AnimatedBase::cancelScripts() {
    validateScriptEdit();
    if (mScripts && mScripts->recording) throw std::logic_error("cancelSchedule cannot be recorded in an animation definition");
    for(const auto& weak:mExternalScriptExecutions) if(auto entry=weak.lock();entry && *entry) (*entry)->stopped=true;
    mExternalScriptExecutions.clear(); mScripts.reset();
}
bool AnimatedBase::animationChannelScheduled(const float* field) const {
    if (std::any_of(mAnimations.begin(),mAnimations.end(),[&](const Animation& a){return a.value==field;})) return true;
    if (!mScripts) return false;
    const auto fields=tweenFields();
    const auto found=std::find(fields.begin(),fields.end(),field);
    if (found==fields.end()) return false;
    const unsigned index=static_cast<unsigned>(found-fields.begin());
    std::function<bool(const ScriptExecution&)> scheduled=[&](const ScriptExecution& execution) {
        if (execution.complete || execution.stopped || std::find(execution.canceled.begin(),execution.canceled.end(),index)!=execution.canceled.end()) return false;
        if (execution.node->kind==ScriptNode::Operation)
            return std::any_of(execution.node->values.begin(),execution.node->values.end(),[&](const auto& value){return value.field==index;});
        return std::any_of(execution.children.begin(),execution.children.end(),[&](const auto& child){return scheduled(*child);});
    };
    for (const auto& execution:mScripts->executions) if (scheduled(*execution)) return true;
    for (const auto& context:mScripts->contexts) if (scriptChannels(context.block,true).contains(index)) return true;
    return false;
}
bool AnimatedBase::animationChannelSelected(const float* field) const {
    if (!mScripts) return false;
    const auto fields=tweenFields();const auto found=std::find(fields.begin(),fields.end(),field);
    if (found==fields.end()) return false;
    try {return scriptChannels(mScripts->selected()).contains(static_cast<unsigned>(found-fields.begin()));}
    catch (const std::logic_error&) {return false;}
}
void AnimatedBase::stopAnimationChannel(const float* field) {
    if (!mScripts) return;
    const auto fields=tweenFields();const auto found=std::find(fields.begin(),fields.end(),field);
    if (found==fields.end()) return;
    const unsigned index=static_cast<unsigned>(found-fields.begin());
    // Resource cancellation must also stop operations that have not started;
    // ordinary channel acquisition only replaces currently active operations.
    std::function<void(ScriptExecution&)> stop=[&](ScriptExecution& execution) {
        if (scriptChannels(execution.node)==std::set<unsigned>{index}) execution.stopped=true;
        else for(auto& child:execution.children) stop(*child);
    };
    for(auto& execution:mScripts->executions) stop(*execution);
    std::function<void(const ScriptNodePtr&)> stopDraft=[&](const ScriptNodePtr& node) {
        if (scriptChannels(node)==std::set<unsigned>{index}) node->playback|=2;
        else for(const auto& child:node->children) stopDraft(child);
    };
    for(auto& context:mScripts->contexts)
        for(const auto& child:context.block->children) stopDraft(child);
}
void AnimatedBase::selectScriptOperand() {
    if (mScripts && (mScripts->recording || mScripts->contexts.size()>1 ||
        !mScripts->contexts[0].block->children.empty() || mScripts->selectedExecution)) {
        mScripts->editable(); mScripts->selected(); return;
    }
    const auto fields=tweenFields();
    auto block=std::make_shared<ScriptNode>();
    for (const auto& track : mAnimations) if (track.operation==mAnimationOperation) {
        if (track.elapsedSeconds!=0) throw std::logic_error("Playback modifiers must be applied before execution begins");
        const auto found=std::find(fields.begin(),fields.end(),track.value);
        if (found==fields.end()) throw std::logic_error("Cannot retain this animation channel");
        auto operation=std::make_shared<ScriptNode>(); operation->kind=ScriptNode::Operation;
        operation->delay=track.delaySeconds; operation->seconds=track.durationSeconds; operation->easing=track.easing;
        operation->direction=track.rotationDirection; operation->mode=track.targetMode; operation->completion=track.completion;
        float target=track.targetVal;
        if (track.spawnRelative && !track.chained) { target-=track.beginVal; operation->mode=animationMode_Add; }
        if (track.relativeRotation) operation->mode=animationMode_Add;
        operation->values.push_back({static_cast<unsigned>(found-fields.begin()),target}); block->children.push_back(operation);
    }
    scriptNonempty(block);
    if (!mScripts) mScripts=std::make_shared<AnimationScriptState>();
    ScriptNodePtr operand=block;
    if (block->children.size()==1) {
        operand=block->children.front(); mScripts->contexts.back().delay+=operand->delay;
    }
    mScripts->append(operand);
    std::erase_if(mAnimations,[&](const Animation& track){return track.operation==mAnimationOperation;});
}
void AnimatedBase::cancelScriptChannel(float* value) {
    const auto externalFields=tweenFields(); const auto externalField=std::find(externalFields.begin(),externalFields.end(),value);
    if(externalField!=externalFields.end()) for(const auto& weak:mExternalScriptExecutions) if(auto entry=weak.lock();entry && *entry)
        (*entry)->cancelChannel(static_cast<unsigned>(externalField-externalFields.begin()),mScriptAcquiring);
    if (!mScripts || mScripts->recording) return;
    const auto fields=tweenFields(); const auto field=std::find(fields.begin(),fields.end(),value);
    if (field==fields.end()) return;
    for (auto& instance : mScripts->executions) instance->cancelChannel(static_cast<unsigned>(field-fields.begin()),mScriptAcquiring);
}
double AnimatedBase::scriptNextBoundary() const {
    if (!mScripts || mScripts->recording) return scriptInfinity;
    double boundary=scriptInfinity;
    if (mScripts->contexts.size()==1 && !mScripts->contexts[0].block->children.empty() && !mScripts->contexts[0].parallelNext) boundary=0;
    for (const auto& execution : mScripts->executions) boundary=std::min(boundary,execution->nextBoundary());
    return boundary;
}
} // namespace pdg
