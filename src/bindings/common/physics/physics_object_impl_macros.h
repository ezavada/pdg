#ifndef PDG_PHYSICS_OBJECT_IMPL_MACROS_H
#define PDG_PHYSICS_OBJECT_IMPL_MACROS_H

// Shared PhysicsBody/Collider argument checks, included inside namespace pdg.
%#ifdef PDG_USING_JAVASCRIPT_CORE
static bool collisionArgumentIs(JSContextRef ctx, JSValueRef value, bool body) {
    return JSValueIsObjectOfClass(ctx, value, body ? PhysicsBody_class() : Collider_class());
}
%#define COLLISION_ARGUMENT_IS(value, body) collisionArgumentIs(ctx, value, body)
%#else
static bool collisionArgumentIs(v8::Isolate* isolate, v8::Local<v8::Value> value, bool body) {
    return (body ? PhysicsBodyWrap::GetTemplate(isolate) : ColliderWrap::GetTemplate(isolate))->HasInstance(value);
}
%#define COLLISION_ARGUMENT_IS(value, body) collisionArgumentIs(isolate, value, body)
%#endif

#endif
