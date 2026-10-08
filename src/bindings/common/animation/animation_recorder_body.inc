try {
    REQUIRE_ARG_MIN_COUNT(1); REQUIRE_INT32_ARG(1, commandId);
    auto get = [&](auto value, const char* name) {
        if (!VALUE_IS_OBJECT(value)) { throw std::invalid_argument("Expected options record"); }
%#ifdef PDG_USING_JAVASCRIPT_CORE
        auto key=JSStringCreateWithUTF8CString(name); auto result=JSObjectGetProperty(ctx,JSValueToObject(ctx,value,exception),key,exception); JSStringRelease(key);
        if(exception && *exception) { throw std::invalid_argument("Unable to read animation argument"); } return result;
%#else
        v8::Local<v8::Value> result;
        if(!value.template As<v8::Object>()->Get(isolate->GetCurrentContext(),v8::String::NewFromUtf8(isolate,name).ToLocalChecked()).ToLocal(&result)) { throw std::invalid_argument("Unable to read animation argument"); } return result;
%#endif
    };
    auto number = [&](auto value) -> double {
        if (!VALUE_IS_NUMBER(value)) { throw std::invalid_argument("Expected numeric animation argument"); }
        const double n=VAL2NUM(value); if(!std::isfinite(n)) { throw std::invalid_argument("Expected finite animation argument"); } return n;
    };
    auto boolean = [&](auto value) -> bool {
        if (!VALUE_IS_BOOL(value)) { throw std::invalid_argument("Expected boolean animation argument"); } return VAL2BOOL(value);
    };
    auto easing = [&](auto value) -> EasingFunc {
        const double n=number(value); if(n<0 || n>=NUM_EASING_FUNCTIONS || std::floor(n)!=n) { throw std::invalid_argument("Invalid easing constant"); } return gEasingFunctions[int(n)];
    };
    auto read = [&](int index, const std::string& kind) -> std::any {
        auto value=ARGV[index+1];
        if(kind=="number") return number(value);
        if(kind=="boolean") return double(boolean(value));
        if(kind=="string") { if(!VALUE_IS_STRING(value)) { throw std::invalid_argument("Expected string animation argument"); } VALUE_TO_CSTRING(text,value); return std::string(text); }
        if(kind=="EasingFunc") return easing(value);
        if(kind=="Point") { Point result; auto ok=VALUE_IS_POINT(value,result); if(!ok.has_value() || !*ok) { throw std::invalid_argument("Expected Point"); } return result; }
        if(kind=="Offset") { Offset result; auto ok=VALUE_IS_OFFSET(value,result); if(!ok.has_value() || !*ok) { throw std::invalid_argument("Expected Offset"); } return result; }
        if(kind=="Rect") { Rect result; auto ok=VALUE_IS_RECT(value,result); if(!ok.has_value() || !*ok) { throw std::invalid_argument("Expected Rect"); } return result; }
        if(kind=="Color") { Color result; auto ok=VALUE_IS_COLOR(value,result); if(!ok.has_value() || !*ok) { throw std::invalid_argument("Expected Color"); } return result; }
        if(kind=="Camera") { if(VALUE_IS_NULL(value)) { return captureAnimationArgument(nullptr); } EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(value, object, Camera); if(!object) { throw std::invalid_argument("Expected Camera"); } return captureAnimationArgument(*object); }
        if(kind=="Sprite") { if(VALUE_IS_NULL(value)) { return captureAnimationArgument(nullptr); } EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(value, object, Sprite); if(!object) { throw std::invalid_argument("Expected Sprite"); } return captureAnimationArgument(object); }
        if(kind=="Part") { if(VALUE_IS_NULL(value)) { return captureAnimationArgument(nullptr); } EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(value, object, Part); if(!object) { throw std::invalid_argument("Expected Part"); } return captureAnimationArgument(object); }
        if(kind=="Particle") { if(VALUE_IS_NULL(value)) { return captureAnimationArgument(nullptr); } EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(value, object, Particle); if(!object) { throw std::invalid_argument("Expected Particle"); } return captureAnimationArgument(*object); }
        if(kind=="PhysicsConstraint") { if(VALUE_IS_NULL(value)) { return captureAnimationArgument(nullptr); } EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(value, object, PhysicsConstraint); if(!object) { throw std::invalid_argument("Expected PhysicsConstraint"); } return captureAnimationArgument(*object); }
        if(kind=="Animated") { if(VALUE_IS_NULL(value)) { return captureAnimationArgument(nullptr); } EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(value, object, AnimatedBase); if(!object) { throw std::invalid_argument("Expected Animated"); } return captureAnimationArgument(*object); }
%#ifndef PDG_NO_GUI
        if(kind=="Font") { if(VALUE_IS_NULL(value)) { return captureAnimationArgument(nullptr); } EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(value, object, Font); if(!object) { throw std::invalid_argument("Expected Font"); } return captureAnimationArgument(object); }
%#endif
%#ifndef PDG_NO_GUI
        if(kind=="Image") { if(VALUE_IS_NULL(value)) { return captureAnimationArgument(nullptr); } EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(value, object, Image); if(!object) { throw std::invalid_argument("Expected Image"); } return captureAnimationArgument(object); }
%#endif
%#ifndef PDG_NO_GUI
        if(kind=="Drawing") { if(VALUE_IS_NULL(value)) { return captureAnimationArgument(nullptr); } EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(value, object, Drawing); if(!object) { throw std::invalid_argument("Expected Drawing"); } return captureAnimationArgument(*object); }
%#endif
        if(kind=="AffineTransform") { glm::mat3 m(1.f); m[0][0]=number(get(value,"a"));m[0][1]=number(get(value,"b"));m[1][0]=number(get(value,"c"));m[1][1]=number(get(value,"d"));m[2][0]=number(get(value,"tx"));m[2][1]=number(get(value,"ty"));return m; }
        auto numericField = [&](const char* key,double fallback) { auto v=get(value,key); return VALUE_IS_UNDEFINED(v)?fallback:number(v); };
        if(kind=="ParticleTrailOptions") return readParticleTrailOptions(numericField,[&](Color fallback) {auto v=get(value,"color");if(VALUE_IS_UNDEFINED(v))return fallback;Color result;auto ok=VALUE_IS_COLOR(v,result);if(!ok.has_value() || !*ok) { throw std::invalid_argument("Expected trail Color"); }return result;});
        if(kind=="AnimationPhysicsDriveSettings") { AnimationPhysicsDriveSettings s; s.maxForce=numericField("maxForce",s.maxForce);s.maxTorque=numericField("maxTorque",s.maxTorque);s.frequency=numericField("frequency",s.frequency);s.dampingRatio=numericField("dampingRatio",s.dampingRatio);s.direction=int(numericField("direction",s.direction));return s; }
        if(kind=="CameraMatchOptions") { CameraMatchOptions s;
            auto sourceValue=get(value,"matchSource"),targetValue=get(value,"matchTarget");
            EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(sourceValue, source, Sprite); EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(targetValue, destination, Sprite);
            if(!source || !destination) { throw std::invalid_argument("Expected matchSource and matchTarget Sprites"); } s.matchSource=source;s.matchTarget=destination;
            s.mode=CameraMatchMode(int(numericField("mode",s.mode)));s.approachSeconds=numericField("approachSeconds",s.approachSeconds);s.settleSeconds=numericField("settleSeconds",s.settleSeconds);s.fadeSeconds=numericField("fadeSeconds",s.fadeSeconds);
            auto restore=get(value,"settleReturnsCamera");if(!VALUE_IS_UNDEFINED(restore))s.settleReturnsCamera=boolean(restore);
            auto a=get(value,"approachEasing"),b=get(value,"settleEasing"),c=get(value,"fadeEasing");if(!VALUE_IS_UNDEFINED(a))s.approachEasing=easing(a);if(!VALUE_IS_UNDEFINED(b))s.settleEasing=easing(b);if(!VALUE_IS_UNDEFINED(c))s.fadeEasing=easing(c);return captureRecorderMatchOptions(s);
        }
        throw std::invalid_argument("Unsupported animation argument type");
    };
    recordScriptCommand(*self, commandId, ARGC-1, read); RETURN_THIS;
} catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
