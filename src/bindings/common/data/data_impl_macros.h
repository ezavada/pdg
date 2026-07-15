#define HAS_SERIALIZABLE_METHODS(klass) \
    HAS_GETTER(klass, MyClassTag)             \
    HAS_GETTER(klass, SerializedSize)         \
    HAS_METHOD(klass, "serialize", Serialize)      \
    HAS_METHOD(klass, "deserialize", Deserialize)  \


#define SERIALIZABLE_BASE_CLASS_IMPL(klass) CR \
  GETTER_IMPL(klass, MyClassTag, UINT32) CR \
  METHOD_IMPL(klass, GetSerializedSize) CR \
	METHOD_SIGNATURE("get size of this object's data for the given stream", CR \
		[number uint], 1, ([object Serializer] serializer)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, serializer, Serializer); CR \
    uint32 dataSize = self->getSerializedSize(serializer); CR \
	RETURN_UINT32(dataSize); CR \
	END CR \
  METHOD_IMPL(klass, Serialize) CR \
	METHOD_SIGNATURE("write this object's data into the given stream", CR \
		undefined, 1, ([object Serializer] serializer)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, serializer, Serializer); CR \
    self->serialize(serializer); CR \
	NO_RETURN; CR \
	END CR \
  METHOD_IMPL(klass, Deserialize) CR \
	METHOD_SIGNATURE("read this object's data from the given stream", CR \
		undefined, 1, ([object Deserializer] deserializer)); CR \
    REQUIRE_ARG_MIN_COUNT(1); CR \
    REQUIRE_CPP_OBJECT_ARG(1, deserializer, Deserializer); CR \
    try { CR \
    	self->deserialize(deserializer); CR \
		NO_RETURN; CR \
    } catch(out_of_data& e) { CR \
    	THROW_ERR(e.what()); CR \
	} catch(bad_tag& e) { CR \
    	THROW_ERR(e.what()); CR \
	} catch(sync_error& e) { CR \
    	THROW_ERR(e.what()); CR \
	} catch(unknown_object& e) { CR \
    	THROW_ERR(e.what()); CR \
	} CR \
	END CR \

