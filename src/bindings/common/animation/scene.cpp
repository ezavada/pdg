#include "pdg_script_macros.h"
#include "../core/core_impl_macros.h"
%#include "pdg_project.h"
%#define PDG_COMPILING_SCRIPT_IMPL
%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"
%#include "internals.h"
%#include "pdg-lib.h"
%#include <stdexcept>
%#include <cmath>
namespace pdg {
%#ifdef PDG_USING_JAVASCRIPT_CORE
static void Scene_finalize(JSObjectRef object) {
    auto* value=static_cast<Scene*>(JSObjectGetPrivate(object)); if(!value)return;
    value->mSceneScriptObj=nullptr;value->mEventEmitterScriptObj=nullptr;
    JSObjectSetPrivate(object,nullptr);value->release();
}
%#define SCENE_SAVE(cppObj,obj) cppObj->mSceneScriptObj=obj;cppObj->mEventEmitterScriptObj=obj
%#else
%#define SCENE_SAVE(cppObj,obj) cppObj->mSceneScriptObj.Reset(isolate,obj);cppObj->mSceneScriptObj.SetWeak();cppObj->mEventEmitterScriptObj.Reset(isolate,obj);cppObj->mEventEmitterScriptObj.SetWeak()
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(Scene, SCENE_SAVE(cppObj,obj);cppObj->addRef())
EXPORT_DERIVED_CLASS_SYMBOLS("Scene", Scene, EventEmitter, Scene_finalize, , ,
    HAS_EMITTER_METHODS(Scene)
    HAS_METHOD(Scene, "_raycast", Raycast)
    HAS_METHOD(Scene, "_sweepCircle", SweepCircle)
    HAS_METHOD(Scene, "_overlapPoint", OverlapPoint)
    HAS_METHOD(Scene, "_overlapCircle", OverlapCircle)
    HAS_METHOD(Scene, "_overlapBox", OverlapBox)
    HAS_METHOD(Scene, "_overlapCapsule", OverlapCapsule)
    HAS_METHOD(Scene, "_nearestPoint", NearestPoint)
    HAS_METHOD(Scene, "addLayer", AddLayer)
    HAS_METHOD(Scene, "removeLayer", RemoveLayer)
    HAS_METHOD(Scene, "disposeLayer", DisposeLayer)
    HAS_METHOD(Scene, "createSpriteLayer", CreateSpriteLayer)
    HAS_METHOD(Scene, "getLayer", GetLayer)
    HAS_METHOD(Scene, "pause", Pause)
    HAS_METHOD(Scene, "resume", Resume)
    HAS_METHOD(Scene, "dispose", Dispose)
    HAS_METHOD(Scene, "cancelAllTimers", CancelAllTimers)
    HAS_METHOD(Scene, "isPaused", IsPaused)
    HAS_METHOD(Scene, "isDisposed", IsDisposed)
    HAS_METHOD(Scene, "getLayerCount", GetLayerCount)
    HAS_METHOD(Scene, "getTimeScale", GetTimeScale)
    HAS_METHOD(Scene, "getFixedStep", GetFixedStep)
    HAS_METHOD(Scene, "getSimulationTime", GetSimulationTime)
    HAS_METHOD(Scene, "getDroppedTime", GetDroppedTime)
    HAS_METHOD(Scene, "getInterpolationAlpha", GetInterpolationAlpha)
    HAS_METHOD(Scene, "getTick", GetTick)
    HAS_METHOD(Scene, "isInputEnabled", IsInputEnabled)
    HAS_METHOD(Scene, "isManual", IsManual)
    HAS_METHOD(Scene, "isInterpolationEnabled", IsInterpolationEnabled)
    HAS_METHOD(Scene, "setTimeScale", SetTimeScale)
    HAS_METHOD(Scene, "setFixedStep", SetFixedStep)
    HAS_METHOD(Scene, "advance", Advance)
    HAS_METHOD(Scene, "setManual", SetManual)
    HAS_METHOD(Scene, "setInputEnabled", SetInputEnabled)
    HAS_METHOD(Scene, "setInterpolation", SetInterpolation)
    HAS_METHOD(Scene, "getCamera", GetCamera)
    HAS_METHOD(Scene, "setCamera", SetCamera)
    HAS_METHOD(Scene, "startTimer", StartTimer)
    HAS_METHOD(Scene, "cancelTimer", CancelTimer)
    HAS_METHOD(Scene, "pauseTimer", PauseTimer)
    HAS_METHOD(Scene, "unpauseTimer", UnpauseTimer)
    HAS_METHOD(Scene, "delayTimer", DelayTimer)
    HAS_METHOD(Scene, "isTimerPaused", IsTimerPaused)
    HAS_METHOD(Scene, "getWhenTimerFiresNext", GetWhenTimerFiresNext)
);
END
EMITTER_BASE_CLASS_IMPL(Scene)
%#ifdef PDG_USING_JAVASCRIPT_CORE
Scene* New_Scene(SCRIPT_ARGS) { return new Scene(); }
%#else
SceneWrap::SceneWrap(SCRIPT_ARGS) : cppPtr_(New_Scene(args)) {}
SceneWrap::~SceneWrap() {if(cppPtr_){cppPtr_->mSceneScriptObj.Reset();cppPtr_->mEventEmitterScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}}
Scene* New_Scene(SCRIPT_ARGS) {if(s_Scene_InNewFromCpp) { return nullptr; }auto* isolate=args.GetIsolate();auto* cppObj=new Scene();cppObj->addRef();SCENE_SAVE(cppObj,args.This());return cppObj;}
%#endif
%#undef SCENE_SAVE
METHOD_IMPL(Scene, AddLayer)
    METHOD_SIGNATURE("Attach a detached or legacy layer to this scene.", undefined, 1, ([object SpriteLayer*] layer));
    try { REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer); self->addLayer(layer); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, RemoveLayer)
    METHOD_SIGNATURE("Detach without destroying; caller owns the surviving layer.", undefined, 1, ([object SpriteLayer*] layer));
    try { REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer); self->removeLayer(layer); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, DisposeLayer)
    METHOD_SIGNATURE("Detach and destroy an attached layer safely.", undefined, 1, ([object SpriteLayer*] layer));
    try { REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer); self->disposeLayer(layer); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, CreateSpriteLayer)
    METHOD_SIGNATURE("Create a scene-owned sprite layer; setSpritePort selects its output.", [object SpriteLayer*], 0, ());
    try { RETURN_NEW_CPP_OBJECT(self->createSpriteLayer(), SpriteLayer); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, GetLayer)
    METHOD_SIGNATURE("Borrow an attached layer by draw order.", [object SpriteLayer*], 1, ([number int] index));
    try { REQUIRE_INT32_ARG(1,index); RETURN_CPP_OBJECT(self->getLayer(index),SpriteLayer); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, Pause)
    METHOD_SIGNATURE("Freeze scene simulation and owned timers while keeping rendering.", undefined, 0, ());
    try { self->pause(); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, Resume)
    METHOD_SIGNATURE("Resume without catch-up; individually paused timers remain paused.", undefined, 0, ());
    try { self->resume(); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, Dispose)
    METHOD_SIGNATURE("Dispose attached layers and cancel timers; detached layers survive.", undefined, 0, ());
    try { self->dispose(); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, CancelAllTimers)
    METHOD_SIGNATURE("Cancel only this scene's timers.", undefined, 0, ());
    try { self->cancelAllTimers(); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, IsPaused)
    METHOD_SIGNATURE("Inspect scene state.", boolean, 0, ());
    try { RETURN_BOOL(self->isPaused()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, IsDisposed)
    METHOD_SIGNATURE("Inspect scene state.", boolean, 0, ());
    try { RETURN_BOOL(self->isDisposed()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, GetLayerCount)
    METHOD_SIGNATURE("Inspect scene state.", number int, 0, ());
    try { RETURN_INTEGER(self->getLayerCount()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, GetTimeScale)
    METHOD_SIGNATURE("Inspect scene state.", number, 0, ());
    try { RETURN_NUMBER(self->getTimeScale()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, GetFixedStep)
    METHOD_SIGNATURE("Inspect scene state.", number, 0, ());
    try { RETURN_NUMBER(self->getFixedStep()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, GetSimulationTime)
    METHOD_SIGNATURE("Inspect scene state.", number, 0, ());
    try { RETURN_NUMBER(self->getSimulationTime()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, GetDroppedTime)
    METHOD_SIGNATURE("Inspect scene state.", number, 0, ());
    try { RETURN_NUMBER(self->getDroppedTime()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, GetInterpolationAlpha)
    METHOD_SIGNATURE("Inspect scene state.", number, 0, ());
    try { RETURN_NUMBER(self->getInterpolationAlpha()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, GetTick)
    METHOD_SIGNATURE("Inspect scene state.", number, 0, ());
    try { RETURN_NUMBER(self->getTick()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, IsInputEnabled)
    METHOD_SIGNATURE("Inspect scene state.", boolean, 0, ());
    try { RETURN_BOOL(self->isInputEnabled()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, IsManual)
    METHOD_SIGNATURE("Inspect scene state.", boolean, 0, ());
    try { RETURN_BOOL(self->isManual()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, IsInterpolationEnabled)
    METHOD_SIGNATURE("Inspect scene state.", boolean, 0, ());
    try { RETURN_BOOL(self->isInterpolationEnabled()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, SetTimeScale)
    METHOD_SIGNATURE("Set timing or advance a scene manually; values must be finite and nonnegative.", undefined, 1, (number scale));
    try { REQUIRE_NUMBER_ARG(1,scale); self->setTimeScale(scale); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, SetFixedStep)
    METHOD_SIGNATURE("Set timing or advance a scene manually; values must be finite and nonnegative.", undefined, 1, (number seconds));
    try { REQUIRE_NUMBER_ARG(1,seconds); self->setFixedStep(seconds); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, Advance)
    METHOD_SIGNATURE("Set timing or advance a scene manually; values must be finite and nonnegative.", undefined, 1, (number seconds));
    try { REQUIRE_NUMBER_ARG(1,seconds); self->advance(seconds); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, SetManual)
    METHOD_SIGNATURE("Configure scene update, input or interpolation behavior.", undefined, 1, (boolean enabled));
    try { REQUIRE_BOOL_ARG(1,enabled); self->setManual(enabled); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, SetInputEnabled)
    METHOD_SIGNATURE("Configure scene update, input or interpolation behavior.", undefined, 1, (boolean enabled));
    try { REQUIRE_BOOL_ARG(1,enabled); self->setInputEnabled(enabled); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, SetInterpolation)
    METHOD_SIGNATURE("Configure scene update, input or interpolation behavior.", undefined, 1, (boolean enabled));
    try { REQUIRE_BOOL_ARG(1,enabled); self->setInterpolation(enabled); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, GetCamera)
    METHOD_SIGNATURE("Borrow the scene camera inherited by its layers.", [object Camera*], 0, ());
    try { RETURN_CPP_OBJECT(self->getCamera(),Camera); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, SetCamera)
    METHOD_SIGNATURE("Retain a camera as scene default; reject ownership by another scene.", undefined, 1, ([object Camera*] camera));
    try { REQUIRE_CPP_OBJECT_ARG(1,camera,Camera); self->setCamera(camera); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, StartTimer)
    METHOD_SIGNATURE("Create a scene-local timer in scaled logical milliseconds; scene pause and disposal apply automatically.", undefined, 3, ([number int] id, number delayMs, boolean oneShot = true));
    try { REQUIRE_INT32_ARG(1,id); REQUIRE_NUMBER_ARG(2,delayMs); OPTIONAL_BOOL_ARG(3,oneShot,true); self->startTimer(id,delayMs,oneShot); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, CancelTimer)
    METHOD_SIGNATURE("Control one scene-local timer independently of scene suspension.", undefined, 1, ([number int] id));
    try { REQUIRE_INT32_ARG(1,id); self->cancelTimer(id); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, PauseTimer)
    METHOD_SIGNATURE("Control one scene-local timer independently of scene suspension.", undefined, 1, ([number int] id));
    try { REQUIRE_INT32_ARG(1,id); self->pauseTimer(id); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, UnpauseTimer)
    METHOD_SIGNATURE("Control one scene-local timer independently of scene suspension.", undefined, 1, ([number int] id));
    try { REQUIRE_INT32_ARG(1,id); self->unpauseTimer(id); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, DelayTimer)
    METHOD_SIGNATURE("Add logical time to the remaining delay.", undefined, 2, ([number int] id, number delayMs));
    try { REQUIRE_INT32_ARG(1,id); REQUIRE_NUMBER_ARG(2,delayMs); self->delayTimer(id,delayMs); NO_RETURN; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, IsTimerPaused)
    METHOD_SIGNATURE("Inspect effective scene/timer suspension.", boolean, 1, ([number int] id));
    try { REQUIRE_INT32_ARG(1,id); RETURN_BOOL(self->isTimerPaused(id)); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, GetWhenTimerFiresNext)
    METHOD_SIGNATURE("Logical deadline in scene milliseconds, or -1 when missing/suspended.", number, 1, ([number int] id));
    try { REQUIRE_INT32_ARG(1,id); RETURN_NUMBER(self->getWhenTimerFiresNext(id)); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Scene, Raycast)
    METHOD_SIGNATURE("Query authoritative scene geometry into reusable retained results.", number uint, 3, ([object Point const&] start, [object Point const&] end, [object CollisionQueryBuffer&] results));
    try { REQUIRE_ARG_COUNT(3); REQUIRE_POINT_ARG(1,start); REQUIRE_POINT_ARG(2,end); REQUIRE_CPP_OBJECT_ARG(3,results,CollisionQueryBuffer);
        RETURN_NUMBER(self->raycast(start,end,*results));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END

METHOD_IMPL(Scene, SweepCircle)
    METHOD_SIGNATURE("Query authoritative scene geometry into reusable retained results.", number uint, 4, ([object Point const&] center, number radius, [object Vector const&] delta, [object CollisionQueryBuffer&] results));
    try { REQUIRE_ARG_COUNT(4); REQUIRE_POINT_ARG(1,center); REQUIRE_NUMBER_ARG(2,radius); REQUIRE_VECTOR_ARG(3,delta); REQUIRE_CPP_OBJECT_ARG(4,results,CollisionQueryBuffer);
        RETURN_NUMBER(self->sweepCircle(center,radius,delta,*results));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END

METHOD_IMPL(Scene, OverlapPoint)
    METHOD_SIGNATURE("Query authoritative scene geometry into reusable retained results.", number uint, 2, ([object Point const&] point, [object CollisionQueryBuffer&] results));
    try { REQUIRE_ARG_COUNT(2); REQUIRE_POINT_ARG(1,point); REQUIRE_CPP_OBJECT_ARG(2,results,CollisionQueryBuffer);
        RETURN_NUMBER(self->overlapPoint(point,*results));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END

METHOD_IMPL(Scene, OverlapCircle)
    METHOD_SIGNATURE("Query authoritative scene geometry into reusable retained results.", number uint, 3, ([object Point const&] center, number radius, [object CollisionQueryBuffer&] results));
    try { REQUIRE_ARG_COUNT(3); REQUIRE_POINT_ARG(1,center); REQUIRE_NUMBER_ARG(2,radius); REQUIRE_CPP_OBJECT_ARG(3,results,CollisionQueryBuffer);
        RETURN_NUMBER(self->overlapCircle(center,radius,*results));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END

METHOD_IMPL(Scene, OverlapBox)
    METHOD_SIGNATURE("Query authoritative scene geometry into reusable retained results.", number uint, 2, ([object RotatedRect const&] box, [object CollisionQueryBuffer&] results));
    try { REQUIRE_ARG_COUNT(2); REQUIRE_ROTATED_RECT_ARG(1,box); REQUIRE_CPP_OBJECT_ARG(2,results,CollisionQueryBuffer);
        RETURN_NUMBER(self->overlapBox(box,*results));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END

METHOD_IMPL(Scene, OverlapCapsule)
    METHOD_SIGNATURE("Query authoritative scene geometry into reusable retained results.", number uint, 4, ([object Point const&] start, [object Point const&] end, number radius, [object CollisionQueryBuffer&] results));
    try { REQUIRE_ARG_COUNT(4); REQUIRE_POINT_ARG(1,start); REQUIRE_POINT_ARG(2,end); REQUIRE_NUMBER_ARG(3,radius); REQUIRE_CPP_OBJECT_ARG(4,results,CollisionQueryBuffer);
        RETURN_NUMBER(self->overlapCapsule(start,end,radius,*results));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END

METHOD_IMPL(Scene, NearestPoint)
    METHOD_SIGNATURE("Query authoritative scene geometry into reusable retained results.", number uint, 3, ([object Point const&] point, number maxDistance, [object CollisionQueryBuffer&] results));
    try { REQUIRE_ARG_COUNT(3); REQUIRE_POINT_ARG(1,point); REQUIRE_NUMBER_ARG(2,maxDistance); REQUIRE_CPP_OBJECT_ARG(3,results,CollisionQueryBuffer);
        RETURN_NUMBER(self->queryNearestPoint(point,maxDistance,*results));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END

%#ifdef PDG_USING_JAVASCRIPT_CORE
static void CollisionQueryBuffer_finalize(JSObjectRef object) {
    auto* value=static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(object)); if(!value)return;
    value->mCollisionQueryBufferScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);value->release();
}
%#define QUERY_SAVE(cppObj,obj) cppObj->mCollisionQueryBufferScriptObj=obj
%#else
%#define QUERY_SAVE(cppObj,obj) cppObj->mCollisionQueryBufferScriptObj.Reset(isolate,obj);cppObj->mCollisionQueryBufferScriptObj.SetWeak()
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(CollisionQueryBuffer, QUERY_SAVE(cppObj,obj);cppObj->addRef())
EXPORT_FINALIZED_CLASS_SYMBOLS("CollisionQueryBuffer", CollisionQueryBuffer, CollisionQueryBuffer_finalize, , ,
    HAS_METHOD(CollisionQueryBuffer, "getCapacity", GetCapacity)
    HAS_METHOD(CollisionQueryBuffer, "getPointX", GetPointX)
    HAS_METHOD(CollisionQueryBuffer, "getPointY", GetPointY)
    HAS_METHOD(CollisionQueryBuffer, "getNormalX", GetNormalX)
    HAS_METHOD(CollisionQueryBuffer, "getNormalY", GetNormalY)
    HAS_METHOD(CollisionQueryBuffer, "getCount", GetCount)
    HAS_METHOD(CollisionQueryBuffer, "isOverflowed", IsOverflowed)
    HAS_METHOD(CollisionQueryBuffer, "clear", Clear)
    HAS_METHOD(CollisionQueryBuffer, "getCollider", GetCollider)
    HAS_METHOD(CollisionQueryBuffer, "getShapeId", GetShapeId)
    HAS_METHOD(CollisionQueryBuffer, "getPoint", GetPoint)
    HAS_METHOD(CollisionQueryBuffer, "getNormal", GetNormal)
    HAS_METHOD(CollisionQueryBuffer, "getFraction", GetFraction)
    HAS_METHOD(CollisionQueryBuffer, "getDistance", GetDistance)
    HAS_METHOD(CollisionQueryBuffer, "getInitialOverlap", GetInitialOverlap)
    HAS_METHOD(CollisionQueryBuffer, "configure", Configure)
    HAS_METHOD(CollisionQueryBuffer, "selectLayers", SelectLayers)
    HAS_METHOD(CollisionQueryBuffer, "addLayer", AddLayer)
    HAS_METHOD(CollisionQueryBuffer, "excludeCollider", ExcludeCollider)
    HAS_METHOD(CollisionQueryBuffer, "excludeBody", ExcludeBody)
    HAS_METHOD(CollisionQueryBuffer, "setPredicate", SetPredicate)
);
END
CollisionQueryBuffer* New_CollisionQueryBuffer(SCRIPT_ARGS) {
    SETUP_CONSTRUCTOR_CALL;
%#ifndef PDG_USING_JAVASCRIPT_CORE
    if(s_CollisionQueryBuffer_InNewFromCpp) { return nullptr; }auto* isolate=args.GetIsolate();
%#endif
    if(ARGC>1 || (ARGC && !VALUE_IS_NUMBER(ARGV[0]))) { SAVE_ERR("Expected optional query capacity"); return nullptr; }
    const double capacity=ARGC ? VAL2NUM(ARGV[0]) : 16;
    if(!std::isfinite(capacity)||capacity<0||capacity>1048576||std::floor(capacity)!=capacity) { SAVE_ERR("Expected integer query capacity from 0 to 1048576"); return nullptr; }
    auto* cppObj=new CollisionQueryBuffer(uint32_t(capacity));
%#ifndef PDG_USING_JAVASCRIPT_CORE
    cppObj->addRef();QUERY_SAVE(cppObj,args.This());
%#endif
    return cppObj;
}
%#ifndef PDG_USING_JAVASCRIPT_CORE
CollisionQueryBufferWrap::CollisionQueryBufferWrap(SCRIPT_ARGS):cppPtr_(New_CollisionQueryBuffer(args)) {}
CollisionQueryBufferWrap::~CollisionQueryBufferWrap(){if(cppPtr_){cppPtr_->mCollisionQueryBufferScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}}
%#endif
%#undef QUERY_SAVE
METHOD_IMPL(CollisionQueryBuffer, GetCapacity)
    METHOD_SIGNATURE("Inspect reusable query results.", [number uint], 0, ());
    try { REQUIRE_ARG_COUNT(0);  auto value=self->getCapacity(); RETURN_NUMBER(value); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetPointX)
    METHOD_SIGNATURE("Read internal result coordinate.", number, 1, ([number uint] index));
    try { REQUIRE_UINT32_ARG(1,index); RETURN_NUMBER(self->getPointX(index)); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetPointY)
    METHOD_SIGNATURE("Read internal result coordinate.", number, 1, ([number uint] index));
    try { REQUIRE_UINT32_ARG(1,index); RETURN_NUMBER(self->getPointY(index)); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetNormalX)
    METHOD_SIGNATURE("Read internal result coordinate.", number, 1, ([number uint] index));
    try { REQUIRE_UINT32_ARG(1,index); RETURN_NUMBER(self->getNormalX(index)); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetNormalY)
    METHOD_SIGNATURE("Read internal result coordinate.", number, 1, ([number uint] index));
    try { REQUIRE_UINT32_ARG(1,index); RETURN_NUMBER(self->getNormalY(index)); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetCount)
    METHOD_SIGNATURE("Inspect reusable query results.", [number uint], 0, ());
    try { REQUIRE_ARG_COUNT(0);  auto value=self->getCount(); RETURN_NUMBER(value); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, IsOverflowed)
    METHOD_SIGNATURE("Inspect reusable query results.", [boolean], 0, ());
    try { REQUIRE_ARG_COUNT(0);  auto value=self->isOverflowed(); RETURN_BOOL(value); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetShapeId)
    METHOD_SIGNATURE("Inspect reusable query results.", [number uint], 1, ([number uint] index));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,indexValue); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue) { THROW_RANGE_ERR("Expected unsigned integer hit index"); RETURN_NULL; } const auto index=uint32_t(indexValue); auto value=self->getShapeId(index); RETURN_NUMBER(value); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetPoint)
    METHOD_SIGNATURE("Inspect reusable query results.", [object Point], 1, ([number uint] index));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,indexValue); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue) { THROW_RANGE_ERR("Expected unsigned integer hit index"); RETURN_NULL; } const auto index=uint32_t(indexValue); auto value=self->getPoint(index); RETURN_POINT(value); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetNormal)
    METHOD_SIGNATURE("Inspect reusable query results.", [object Vector], 1, ([number uint] index));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,indexValue); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue) { THROW_RANGE_ERR("Expected unsigned integer hit index"); RETURN_NULL; } const auto index=uint32_t(indexValue); auto value=self->getNormal(index); RETURN_VECTOR(value); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetFraction)
    METHOD_SIGNATURE("Inspect reusable query results.", [number], 1, ([number uint] index));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,indexValue); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue) { THROW_RANGE_ERR("Expected unsigned integer hit index"); RETURN_NULL; } const auto index=uint32_t(indexValue); auto value=self->getFraction(index); RETURN_NUMBER(value); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetDistance)
    METHOD_SIGNATURE("Inspect reusable query results.", [number], 1, ([number uint] index));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,indexValue); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue) { THROW_RANGE_ERR("Expected unsigned integer hit index"); RETURN_NULL; } const auto index=uint32_t(indexValue); auto value=self->getDistance(index); RETURN_NUMBER(value); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetInitialOverlap)
    METHOD_SIGNATURE("Inspect reusable query results.", [boolean], 1, ([number uint] index));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,indexValue); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue) { THROW_RANGE_ERR("Expected unsigned integer hit index"); RETURN_NULL; } const auto index=uint32_t(indexValue); auto value=self->getInitialOverlap(index); RETURN_BOOL(value); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, GetCollider)
    METHOD_SIGNATURE("Borrow the retained collider for a hit.", [object Collider*], 1, ([number uint] index));
    try { REQUIRE_NUMBER_ARG(1,indexValue); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue) { THROW_RANGE_ERR("Expected unsigned integer hit index"); RETURN_NULL; } const auto index=uint32_t(indexValue); RETURN_CPP_OBJECT(self->getCollider(index),Collider); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(CollisionQueryBuffer, Clear)
    METHOD_SIGNATURE("Release previous hits and reset overflow.", undefined, 0, ());
    try {self->clear();NO_RETURN;} catch(const std::exception& e){THROW_ERR(e.what());}
    END
METHOD_IMPL(CollisionQueryBuffer, Configure)
    METHOD_SIGNATURE("Configure selection for a synchronous query.", undefined, 3, ([number uint] layers, [number uint] categories, boolean sensors));
    REQUIRE_UINT32_ARG(1,layers);REQUIRE_UINT32_ARG(2,categories);REQUIRE_BOOL_ARG(3,sensors);
    try {self->configure(layers,categories,sensors);NO_RETURN;} catch(const std::exception& e){THROW_ERR(e.what());}
    END
METHOD_IMPL(CollisionQueryBuffer, SelectLayers)
    METHOD_SIGNATURE("Select an explicit layer list initially empty.", undefined, 0, ());
    try {self->selectLayers();NO_RETURN;} catch(const std::exception& e){THROW_ERR(e.what());}
    END
METHOD_IMPL(CollisionQueryBuffer, AddLayer)
    METHOD_SIGNATURE("Configure query selection.", undefined, 1, ([object SpriteLayer*] layer));
    REQUIRE_CPP_OBJECT_ARG(1,layer,SpriteLayer);try {self->addLayer(layer);NO_RETURN;} catch(const std::exception& e){THROW_ERR(e.what());}
    END
METHOD_IMPL(CollisionQueryBuffer, ExcludeCollider)
    METHOD_SIGNATURE("Configure query selection.", undefined, 1, ([object Collider*] collider));
    REQUIRE_CPP_OBJECT_ARG(1,collider,Collider);try {self->excludeCollider(collider);NO_RETURN;} catch(const std::exception& e){THROW_ERR(e.what());}
    END
METHOD_IMPL(CollisionQueryBuffer, ExcludeBody)
    METHOD_SIGNATURE("Configure query selection.", undefined, 1, ([object PhysicsBody*] body));
    REQUIRE_CPP_OBJECT_ARG(1,body,PhysicsBody);try {self->excludeBody(body);NO_RETURN;} catch(const std::exception& e){THROW_ERR(e.what());}
    END
struct QueryScriptPredicate {
%#ifdef PDG_USING_JAVASCRIPT_CORE
    JSGlobalContextRef context; JSObjectRef function;
    QueryScriptPredicate(JSContextRef ctx,JSObjectRef f):context(JSGlobalContextRetain(JSContextGetGlobalContext(ctx))),function(f){JSValueProtect(context,function);}
    ~QueryScriptPredicate(){JSValueUnprotect(context,function);JSGlobalContextRelease(context);}
%#else
    v8::Isolate* isolate; v8::Global<v8::Context> context; v8::Global<v8::Function> function;
    QueryScriptPredicate(v8::Isolate* i,v8::Local<v8::Function> f):isolate(i),context(i,i->GetCurrentContext()),function(i,f){}
%#endif
    bool invoke(const Collider& collider) {
        auto* c=const_cast<Collider*>(&collider);
%#ifdef PDG_USING_JAVASCRIPT_CORE
        auto ctx=context; JSValueRef error=nullptr;
        JSValueRef argv[]={c->mColliderScriptObj?c->mColliderScriptObj:Collider_newFromCpp(ctx,c)};
        auto result=JSObjectCallAsFunction(ctx,function,nullptr,1,argv,&error);
        if(error)throw std::runtime_error("Query predicate failed");
        if(!JSValueIsBoolean(ctx,result))throw std::runtime_error("Query predicate must return a boolean");
        return JSValueToBoolean(ctx,result);
%#else
        v8::HandleScope handles(isolate);auto ctx=context.Get(isolate);v8::Context::Scope scope(ctx);v8::TryCatch catcher(isolate);
        v8::Local<v8::Value> argv[]={c->mColliderScriptObj.IsEmpty()?ColliderWrap::NewFromCpp(isolate,c):v8::Local<v8::Object>::New(isolate,c->mColliderScriptObj)},result;
        if(!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),1,argv).ToLocal(&result)) {
            v8::String::Utf8Value message(isolate,catcher.Exception());throw std::runtime_error(*message?*message:"Query predicate failed");
        }
        if(!result->IsBoolean())throw std::runtime_error("Query predicate must return a boolean");
        return result->BooleanValue(isolate);
%#endif
    }
};
METHOD_IMPL(CollisionQueryBuffer, SetPredicate)
    METHOD_SIGNATURE("Set a synchronous collider predicate; null clears it.", undefined, 1, (function callback));
    try { REQUIRE_ARG_COUNT(1);if(VALUE_IS_NULL(ARGV[0])){self->setPredicate({});NO_RETURN;}
        REQUIRE_FUNCTION_ARG(1,func);
%#ifdef PDG_USING_JAVASCRIPT_CORE
        auto predicate=std::make_shared<QueryScriptPredicate>(ctx,func);
%#else
        auto predicate=std::make_shared<QueryScriptPredicate>(isolate,func);
%#endif
        self->setPredicate([predicate](const Collider& c){return predicate->invoke(c);});NO_RETURN;
    } catch(const std::exception& e){THROW_ERR(e.what());}
    END

}
// @pdg-member {"name":"Scene.Scene","type":"constructor","native":true,"brief":"Create an independently advancing scene with its own camera and physics world.","returns":"object Scene","params":[]}
// @pdg-class {"name":"Scene","native_binding":{"ownership":"retained","browser":{"generate":true,"constructors":[{"types":[],"public":true}],"defaults":{"exceptions":"javascript","arguments":"idl"}}}}

// @pdg-member {"name":"CollisionQueryBuffer.CollisionQueryBuffer","type":"constructor","native":true,"brief":"Reserve retained collision query result slots.","returns":"object CollisionQueryBuffer","params":[{"name":"capacity","type":"number uint","optional":true,"default_value":"16"}]}
// @pdg-class {"name":"CollisionQueryBuffer","native_binding":{"ownership":"retained","browser":{"generate":true,"constructors":[{"types":["uint32_t"],"public":true}],"defaults":{"exceptions":"javascript","arguments":"idl"}}},"internal":true}
// @pdg-member {"name":"CollisionQueryBuffer.setPredicate","native_binding":{"adapter":"CollisionQueryBuffer.setPredicate","browser":{"generate":true}}}
// @pdg-member {"name":"CollisionQueryBuffer.getCollider","native_binding":{"adapter":"CollisionQueryBuffer.getCollider","browser":{"generate":true}}}

// @pdg-member {"name":"Scene._raycast","native_binding":{"symbol":"pdg::Scene::raycast","signature":"uint32_t(const pdg::Point&, const pdg::Point&, pdg::CollisionQueryBuffer&)"},"type":"function","native":true,"brief":"Native query entry point used by the options wrapper.","returns":"number uint","params":[{"name":"arg0","type":"object Point"},{"name":"arg1","type":"object Point"},{"name":"arg2","type":"object CollisionQueryBuffer"}],"internal":true}

// @pdg-member {"name":"Scene._sweepCircle","native_binding":{"symbol":"pdg::Scene::sweepCircle","signature":"uint32_t(const pdg::Point&, double, const pdg::Vector&, pdg::CollisionQueryBuffer&)"},"type":"function","native":true,"brief":"Native query entry point used by the options wrapper.","returns":"number uint","params":[{"name":"arg0","type":"object Point"},{"name":"arg1","type":"number"},{"name":"arg2","type":"object Vector"},{"name":"arg3","type":"object CollisionQueryBuffer"}],"internal":true}

// @pdg-member {"name":"Scene._overlapPoint","native_binding":{"symbol":"pdg::Scene::overlapPoint","signature":"uint32_t(const pdg::Point&, pdg::CollisionQueryBuffer&)"},"type":"function","native":true,"brief":"Native query entry point used by the options wrapper.","returns":"number uint","params":[{"name":"arg0","type":"object Point"},{"name":"arg1","type":"object CollisionQueryBuffer"}],"internal":true}

// @pdg-member {"name":"Scene._overlapCircle","native_binding":{"symbol":"pdg::Scene::overlapCircle","signature":"uint32_t(const pdg::Point&, double, pdg::CollisionQueryBuffer&)"},"type":"function","native":true,"brief":"Native query entry point used by the options wrapper.","returns":"number uint","params":[{"name":"arg0","type":"object Point"},{"name":"arg1","type":"number"},{"name":"arg2","type":"object CollisionQueryBuffer"}],"internal":true}

// @pdg-member {"name":"Scene._overlapBox","native_binding":{"symbol":"pdg::Scene::overlapBox","signature":"uint32_t(const pdg::RotatedRect&, pdg::CollisionQueryBuffer&)"},"type":"function","native":true,"brief":"Native query entry point used by the options wrapper.","returns":"number uint","params":[{"name":"arg0","type":"object RotatedRect"},{"name":"arg1","type":"object CollisionQueryBuffer"}],"internal":true}

// @pdg-member {"name":"Scene._overlapCapsule","native_binding":{"symbol":"pdg::Scene::overlapCapsule","signature":"uint32_t(const pdg::Point&, const pdg::Point&, double, pdg::CollisionQueryBuffer&)"},"type":"function","native":true,"brief":"Native query entry point used by the options wrapper.","returns":"number uint","params":[{"name":"arg0","type":"object Point"},{"name":"arg1","type":"object Point"},{"name":"arg2","type":"number"},{"name":"arg3","type":"object CollisionQueryBuffer"}],"internal":true}

// @pdg-member {"name":"Scene._nearestPoint","native_binding":{"symbol":"pdg::Scene::queryNearestPoint","signature":"uint32_t(const pdg::Point&, double, pdg::CollisionQueryBuffer&)"},"type":"function","native":true,"brief":"Native query entry point used by the options wrapper.","returns":"number uint","params":[{"name":"arg0","type":"object Point"},{"name":"arg1","type":"number"},{"name":"arg2","type":"object CollisionQueryBuffer"}],"internal":true}
