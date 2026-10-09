// Portable semantic arguments. Included in animated-script.inc after object-reference helpers.
RefCountedObj* AnimationObjectArgument::get() const {
    if(auto object=lifetime.lock()) return *object;
    return retained.get();
}
AnimationObjectArgument captureAnimationObject(RefCountedObj* object) {
    if(auto* animated=dynamic_cast<AnimatedBase*>(object)) return {animated->animationLifetime(),{}};
    if(object) object->addRef();
    return {{},std::shared_ptr<RefCountedObj>(object,[](RefCountedObj* p){if(p)p->release();})};
}
namespace {
std::vector<AnimationValueCodec>& animationValueCodecs() {
    static std::vector<AnimationValueCodec> codecs; return codecs;
}
std::string readAnimationArgumentString(IDeserializer* reader) {
    const auto length=reader->deserialize_memGetLen();
    if(length>1000000) throw std::runtime_error("Animation argument exceeds size limit");
    std::string result(length,0);
    if(reader->deserialize_mem(result.data(),length)!=length) throw std::runtime_error("Truncated animation argument");
    return result;
}
}
void registerAnimationValueCodec(AnimationValueCodec codec) {
    auto& codecs=animationValueCodecs();
    for(const auto& existing:codecs) if(existing.type==codec.type || existing.name==codec.name)
        throw std::logic_error("Duplicate animation argument codec");
    codecs.push_back(std::move(codec));
}
uint32 serializeAnimationArgument(const std::any& argument, ISerializer* serializer, bool writing) {
    uint8 kind=255; uint32 size=1;
    if(argument.type()==typeid(double)) kind=0;
    else if(argument.type()==typeid(std::string)) kind=1;
    else if(argument.type()==typeid(EasingFunc)) kind=2;
    else if(argument.type()==typeid(Point)) kind=3;
    else if(argument.type()==typeid(Offset)) kind=4;
    else if(argument.type()==typeid(Vector)) kind=5;
    else if(argument.type()==typeid(Rect)) kind=6;
    else if(argument.type()==typeid(Color)) kind=7;
    else if(argument.type()==typeid(AnimationObjectArgument)) kind=8;
    if(writing) serializer->serialize_1u(kind);
    switch(kind) {
        case 0: {
            const auto value=std::any_cast<double>(argument);
            if(!std::isfinite(value)) throw std::runtime_error("Nonfinite animation argument");
            if(writing) serializer->serialize_d(value);
            return size+serializer->sizeof_d(value);
        }
        case 1: {
            const auto& value=std::any_cast<const std::string&>(argument);
            if(value.size()>1000000) throw std::runtime_error("Animation argument exceeds size limit");
            if(writing) serializer->serialize_mem(value.data(),value.size());
            return size+serializer->sizeof_mem(value.data(),value.size());
        }
        case 2: {
            const auto id=easingFuncToId(std::any_cast<EasingFunc>(argument));
            if(id>=NUM_BUILTIN_EASINGS) throw std::runtime_error("Custom animation easing is not portable");
            if(writing) serializer->serialize_1u(id);
            return size+1;
        }
        case 3: {const auto& v=std::any_cast<const Point&>(argument);if(writing) serializer->serialize_point(v);return size+serializer->sizeof_point(v);}
        case 4: {const auto& v=std::any_cast<const Offset&>(argument);if(writing) serializer->serialize_offset(v);return size+serializer->sizeof_offset(v);}
        case 5: {const auto& v=std::any_cast<const Vector&>(argument);if(writing) serializer->serialize_vector(v);return size+serializer->sizeof_vector(v);}
        case 6: {const auto& v=std::any_cast<const Rect&>(argument);if(writing) serializer->serialize_rect(v);return size+serializer->sizeof_rect(v);}
        case 7: {const auto& v=std::any_cast<const Color&>(argument);if(writing) serializer->serialize_color(v);return size+serializer->sizeof_color(v);}
        case 8: {
            auto* object=std::any_cast<const AnimationObjectArgument&>(argument).get();
            auto* animated=dynamic_cast<AnimatedBase*>(object);
            if(writing) serializer->serialize_1u(animated?1:0);
            ++size;
            if(animated) {if(writing) writeAnimationReference(serializer,animated);return size+animationReferenceSize(serializer,animated);}
            auto* serializable=dynamic_cast<ISerializable*>(object);
            if(object && !serializable) throw std::runtime_error("Animation command references a nonserializable resource");
            if(writing) serializer->serialize_obj(serializable);
            return size+serializer->sizeof_obj(serializable);
        }
        default:
            for(const auto& codec:animationValueCodecs()) if(codec.type==std::type_index(argument.type())) {
                if(writing) serializer->serialize_mem(codec.name.data(),codec.name.size());
                return size+serializer->sizeof_mem(codec.name.data(),codec.name.size())+codec.write(argument,serializer,writing);
            }
            throw std::runtime_error("Animation command argument is not portable");
    }
}
std::any deserializeAnimationArgument(IDeserializer* reader) {
    switch(reader->deserialize_1u()) {
        case 0: {const auto value=reader->deserialize_d();if(!std::isfinite(value))throw std::runtime_error("Nonfinite animation argument");return value;}
        case 1: return readAnimationArgumentString(reader);
        case 2: {auto easing=easingIdToFunc(reader->deserialize_1u());if(!easing)throw std::runtime_error("Invalid animation argument easing");return easing;}
        case 3: return reader->deserialize_point();
        case 4: return reader->deserialize_offset();
        case 5: return reader->deserialize_vector();
        case 6: return reader->deserialize_rect();
        case 7: return reader->deserialize_color();
        case 8: {
            const auto kind=reader->deserialize_1u();
            if(kind==1) {
                auto reference=readAnimationReference(reader);
                return AnimationObjectArgument{reference.member?captureAnimationObject(reference.member).lifetime:std::weak_ptr<AnimatedBase*>(),std::move(reference.retained)};
            }
            if(kind!=0) throw std::runtime_error("Invalid animation argument object reference");
            auto* object=reader->deserialize_obj();
            return AnimationObjectArgument{{},std::shared_ptr<RefCountedObj>(object,[](RefCountedObj* p){if(p)p->release();})};
        }
        case 255: {
            const auto name=readAnimationArgumentString(reader);
            for(const auto& codec:animationValueCodecs()) if(codec.name==name) return codec.read(reader);
            throw std::runtime_error("Unknown animation argument codec");
        }
        default: throw std::runtime_error("Invalid animation argument kind");
    }
}
