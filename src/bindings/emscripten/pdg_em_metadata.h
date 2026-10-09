// Browser ABI mappings consumed by the source-owned IDL generator.

// @pdg-class {"name":"ISerializable","native_binding":{"browser":{"generate":true,"base":null}}}

// @pdg-class {"name":"IEventHandler","native_binding":{"browser":{"base":null,"generate":true,"constructors":[{"types":[]}]}}}

// @pdg-class {"name":"IAnimationHelper","native_binding":{"browser":{"generate":true,"base":null}}}

// @pdg-class {"name":"ISpriteDrawHelper","native_binding":{"browser":{"generate":true,"guard":"!PDG_NO_GUI","base":null}}}

// @pdg-class {"name":"Image","native_binding":{"browser":{"generate":true,"base":null,"constructors":[{"factory":"pdg::emscriptenCreateImage","allow_raw_pointers":true}],"support_bindings":[{"name":"_getImageBoundsAt","symbol":"pdg::emscriptenImageGetBoundsAt"}],"pointer_policy":"borrowed"}}}

// @pdg-member {"name":"pdg.rotationDirection_AsSpecified","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.rotationDirection_Shortest","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.rotationDirection_Clockwise","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.rotationDirection_CounterClockwise","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.lineStyle_Auto","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.lineStyle_None","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.lineStyle_Solid","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.lineStyle_Dashed","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.lineStyle_Dotted","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.lineStyle_DashDot","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.lineStyle_DashDotDot","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.blendMode_Normal","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.blendMode_Additive","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.blendMode_Multiply","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.blendMode_Screen","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.blendMode_Darken","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.blendMode_Lighten","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.gradientType_None","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.gradientType_Linear","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.gradientType_Radial","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.fit_None","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.fit_Fill","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.fit_FillKeepProportions","native_binding":{"cast":"int","browser":{"generate":true},"symbol":"pdg::fit_Overflow"}}

// @pdg-member {"name":"pdg.fit_Height","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.fit_Width","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.fit_Inside","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.fit_Overflow","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.fit_Clipped","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.fit_TileX","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.fit_TileY","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.fit_Tile","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.type_Line","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.type_Spline","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.type_Arc","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.type_Rect","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.type_Quad","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.type_Polygon","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.type_Ellipse","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.type_Image","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.type_ImageStrip","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.type_Drawing","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_Positions","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_ZOrder","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_Sizes","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_Animations","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_Motion","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_Forces","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_Physics","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_ImageRefs","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_SCMLRefs","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_HelperRefs","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_InitialData","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_Micro","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_Update","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.ser_Full","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.serialization_Complete","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.serialization_ExternalReferences","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.rand","native_binding":{"symbol":"pdg::rand","allow_raw_pointers":true,"browser":{"generate":true}}}

// @pdg-member {"name":"pdg.srand","native_binding":{"symbol":"pdg::srand","allow_raw_pointers":true,"browser":{"generate":true}}}

// @pdg-member {"name":"pdg.setSerializationDebugMode","native_binding":{"symbol":"pdg::setSerializationDebugMode","allow_raw_pointers":true,"browser":{"generate":true}}}

// @pdg-member {"name":"pdg.getFileManager","native_binding":{"symbol":"pdg::getFileManager","allow_raw_pointers":true,"browser":{"generate":true}}}

// @pdg-member {"name":"pdg.getLogManager","native_binding":{"symbol":"pdg::getLogManager","allow_raw_pointers":true,"browser":{"generate":true}}}

// @pdg-member {"name":"pdg.getConfigManager","native_binding":{"symbol":"pdg::getConfigManager","allow_raw_pointers":true,"browser":{"generate":true}}}

// @pdg-member {"name":"pdg.getResourceManager","native_binding":{"symbol":"pdg::getResourceManager","allow_raw_pointers":true,"browser":{"generate":true}}}

// @pdg-member {"name":"pdg.getEventManager","native_binding":{"symbol":"pdg::getEventManager","allow_raw_pointers":true,"browser":{"generate":true}}}

// @pdg-member {"name":"pdg.getTimerManager","native_binding":{"symbol":"pdg::getTimerManager","allow_raw_pointers":true,"browser":{"generate":true}}}

// @pdg-member {"name":"pdg.getGraphicsManager","native_binding":{"symbol":"pdg::getGraphicsManager","allow_raw_pointers":true,"browser":{"generate":true,"guard":"!PDG_NO_GUI"}}}

// @pdg-member {"name":"pdg.getSoundManager","native_binding":{"symbol":"pdg::getSoundManager","allow_raw_pointers":true,"browser":{"generate":true,"guard":"!PDG_NO_SOUND"}}}

// @pdg-member {"name":"pdg.createSpriteLayerFromSpriterFile","native_binding":{"symbol":"pdg::createSpriteLayerFromSpriterFile","allow_raw_pointers":true,"browser":{"generate":true,"guard":"PDG_SPRITER_SUPPORT"}}}

// @pdg-member {"name":"pdg.cleanupLayer","native_binding":{"symbol":"pdg::cleanupLayer","allow_raw_pointers":true,"browser":{"generate":true}}}

// @pdg-member {"name":"LogManager.initialize","native_binding":{"adapter":"LogManager.initialize"}}

// @pdg-member {"name":"LogManager.writeLogEntry","native_binding":{"adapter":"LogManager.writeLogEntry"}}



// @pdg-member {"name":"ResourceManager.setLanguage","native_binding":{"adapter":"ResourceManager.setLanguage"}}

// @pdg-member {"name":"ResourceManager.getLanguage","native_binding":{"adapter":"ResourceManager.getLanguage"}}

// @pdg-member {"name":"ResourceManager.openResourceFile","native_binding":{"adapter":"ResourceManager.openResourceFile","binding_name":"_openResourceFile"}}

// @pdg-member {"name":"ResourceManager.getImage","native_binding":{"adapter":"ResourceManager.getImage","binding_name":"_getImage"}}

// @pdg-member {"name":"ResourceManager.getImageStrip","native_binding":{"adapter":"ResourceManager.getImageStrip","binding_name":"_getImageStrip"}}

// @pdg-member {"name":"ResourceManager.getString","native_binding":{"adapter":"ResourceManager.getString","binding_name":"_getString"}}

// @pdg-member {"name":"ResourceManager.getResourceSize","native_binding":{"adapter":"ResourceManager.getResourceSize","binding_name":"_getResourceSize"}}

// @pdg-member {"name":"Serializer.serialize_8","native_binding":{"adapter":"Serializer.serialize_8"}}

// @pdg-member {"name":"Serializer.serialize_str","native_binding":{"adapter":"Serializer.serialize_str","binding_name":"_serialize_str"}}

// @pdg-member {"name":"Serializer.serialize_rotr","native_binding":{"binding_name":"_serialize_rotr"}}

// @pdg-member {"name":"Serializer.serialize_quad","native_binding":{"binding_name":"_serialize_quad"}}

// @pdg-member {"name":"Serializer.sizeof_str","native_binding":{"adapter":"Serializer.sizeof_str","binding_name":"_sizeof_str"}}

// @pdg-member {"name":"Serializer.sizeof_rotr","native_binding":{"binding_name":"_sizeof_rotr"}}

// @pdg-member {"name":"Serializer.sizeof_quad","native_binding":{"binding_name":"_sizeof_quad"}}

// @pdg-member {"name":"Serializer.getDataPtr","native_binding":{"adapter":"Serializer.getDataPtr"}}

// @pdg-member {"name":"Deserializer.deserialize_8","native_binding":{"adapter":"Deserializer.deserialize_8"}}

// @pdg-member {"name":"Deserializer.deserialize_8u","native_binding":{"adapter":"Deserializer.deserialize_8"}}

// @pdg-member {"name":"Deserializer.deserialize_str","native_binding":{"adapter":"Deserializer.deserialize_str"}}

// @pdg-member {"name":"Deserializer.deserialize_mem","native_binding":{"adapter":"Deserializer.deserialize_mem"}}

// @pdg-member {"name":"Animated.changeMovementTo","native_binding":{"signature":"pdg::AnimatedBase&(const pdg::Vector&, double, pdg::EasingFunc)"}}

// @pdg-member {"name":"Animated.changeMovementBy","native_binding":{"signature":"pdg::AnimatedBase&(const pdg::Vector&, double, pdg::EasingFunc)"}}

// @pdg-member {"name":"Animated.changeCenterOffsetTo","native_binding":{"signature":"pdg::AnimatedBase&(const pdg::Offset&, double, pdg::EasingFunc)"}}

// @pdg-member {"name":"Animated.changeCenterOffsetBy","native_binding":{"signature":"pdg::AnimatedBase&(const pdg::Offset&, double, pdg::EasingFunc)"}}


// @pdg-member {"name":"SpriteLayer.getSerializedSize","native_binding":{"adapter":"SpriteLayer.getSerializedSize"}}

// @pdg-member {"name":"SpriteLayer.serialize","native_binding":{"adapter":"SpriteLayer.serialize"}}

// @pdg-member {"name":"SpriteLayer.deserialize","native_binding":{"adapter":"SpriteLayer.deserialize"}}

// @pdg-member {"name":"TileLayer.defineTileSet","native_binding":{"binding_name":"_defineTileSet"}}

// @pdg-member {"name":"TileLayer.setWorldSize","native_binding":{"binding_name":"_setWorldSize"}}

// @pdg-member {"name":"TileLayer.getTileTypeAt","native_binding":{"adapter":"TileLayer.getTileTypeAt"}}

// @pdg-member {"name":"TileLayer.setTileTypeAt","native_binding":{"adapter":"TileLayer.setTileTypeAt"}}

// @pdg-member {"name":"TileLayer.getTileTypeAndFacingAt","native_binding":{"adapter":"TileLayer.getTileTypeAndFacingAt"}}

// @pdg-member {"name":"Image.getSubsection","native_binding":{"adapter":"Image.getSubsection","binding_name":"_getSubsection"}}

// @pdg-member {"name":"Attributes.lineStyle","native_binding":{"adapter":"Attributes.lineStyle"}}

// @pdg-member {"name":"Attributes.fitType","native_binding":{"adapter":"Attributes.fitType"}}

// @pdg-member {"name":"Attributes.scale","native_binding":{"signature":"pdg::Attributes&(float, float, const pdg::Point&)"}}

// @pdg-member {"name":"Attributes.transform","native_binding":{"adapter":"Attributes.transform"}}

// @pdg-member {"name":"Attributes.setTransform","native_binding":{"adapter":"Attributes.setTransform"}}

// @pdg-member {"name":"Attributes.blendMode","native_binding":{"adapter":"Attributes.blendMode"}}

// @pdg-member {"name":"Attributes.getLineStyle","native_binding":{"adapter":"Attributes.getLineStyle"}}

// @pdg-member {"name":"Attributes.getGradientType","native_binding":{"adapter":"Attributes.getGradientType"}}

// @pdg-member {"name":"Attributes.getTransform","native_binding":{"adapter":"Attributes.getTransform"}}

// @pdg-member {"name":"Attributes.getBlendMode","native_binding":{"adapter":"Attributes.getBlendMode"}}

// @pdg-member {"name":"Attributes.getFitType","native_binding":{"adapter":"Attributes.getFitType"}}

// @pdg-member {"name":"AnimatedAttributes.changeTransform","native_binding":{"adapter":"AnimatedAttributes.changeTransform"}}

// @pdg-member {"name":"ElementRef.type","native_binding":{"adapter":"ElementRef.type"}}

// @pdg-member {"name":"ElementRef.getControlPoints","native_binding":{"adapter":"ElementRef.getControlPoints","binding_name":"_getControlPoints"}}

// @pdg-member {"name":"ElementRef.getAttributes","native_binding":{"adapter":"ElementRef.getAttributes"}}

// @pdg-member {"name":"pdg.createSpriteLayer","native_binding":{"adapter":"pdg.createSpriteLayer","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.createTileLayer","native_binding":{"adapter":"pdg.createTileLayer","browser":{"generate":true}}}

// @pdg-member {"name":"pdg.createDrawing","native_binding":{"browser":{"generate":true},"symbol":"pdg::Drawing::create"}}

// Custom browser implementation remains in the reviewed manual inventory.
// @pdg-member {"name":"Image.deserialize","native_binding":{"browser":{"generate":false}}}

// Custom browser implementation remains in the reviewed manual inventory.

// Custom browser implementation remains in the reviewed manual inventory.
// @pdg-member {"name":"Image.getSerializedSize","native_binding":{"browser":{"generate":false}}}

// Custom browser implementation remains in the reviewed manual inventory.
// @pdg-member {"name":"Image.serialize","native_binding":{"browser":{"generate":false}}}

// Retained classes use one generated smart-handle registration. Their custom
// fragments contain only specialized ABI adapters and lifecycle support.
// @pdg-class {"name":"Camera","native_binding":{"browser":{"generate":true,"constructors":[{"types":[],"public":true}],"defaults":{"exceptions":"javascript","arguments":"idl"}}}}
// @pdg-class {"name":"Part","native_binding":{"browser":{"generate":true,"defaults":{"exceptions":"javascript","arguments":"idl"}}}}
// @pdg-class {"name":"Collider","native_binding":{"browser":{"generate":true,"defaults":{"exceptions":"javascript","arguments":"idl"}}}}
// @pdg-class {"name":"Particle","native_binding":{"browser":{"generate":true,"constructors":[{"types":[]}],"defaults":{"exceptions":"javascript","arguments":"idl"}}}}
// @pdg-class {"name":"ParticleEmitter","native_binding":{"browser":{"generate":true,"constructors":[{"types":[]}],"defaults":{"exceptions":"javascript","arguments":"idl"}}}}
// @pdg-class {"name":"PhysicsBody","native_binding":{"browser":{"generate":true,"defaults":{"exceptions":"javascript","arguments":"idl"}}}}
// @pdg-class {"name":"PhysicsConstraint","native_binding":{"browser":{"generate":true,"defaults":{"exceptions":"javascript","arguments":"idl"}}}}
// @pdg-class {"name":"AnimationScript","native_binding":{"browser":{"generate":true,"defaults":{"exceptions":"javascript","arguments":"idl"}}}}
// Content methods are unavailable in headless native builds.
// @pdg-member {"name":"Particle.setImage","native_binding":{"browser":{"guard":"!PDG_NO_GUI"}}}
// @pdg-member {"name":"Particle.setDrawing","native_binding":{"browser":{"guard":"!PDG_NO_GUI"}}}

// @pdg-member {"name":"pdg.type_Text","native_binding":{"cast":"int","browser":{"generate":true}}}

// @pdg-member {"name":"Scene.startTimer","native_binding":{"adapter":"Scene.startTimer","browser":{"generate":true}}}
// @pdg-member {"name":"Scene.getTick","native_binding":{"adapter":"Scene.getTick","browser":{"generate":true}}}
// @pdg-member {"name":"Scene.addHandler","native_binding":{"browser":{"generate":false}}}
// @pdg-member {"name":"Scene.removeHandler","native_binding":{"browser":{"generate":false}}}
// @pdg-member {"name":"Scene.clear","native_binding":{"browser":{"generate":false}}}
// @pdg-member {"name":"Scene.blockEvent","native_binding":{"browser":{"generate":false}}}
// @pdg-member {"name":"Scene.unblockEvent","native_binding":{"browser":{"generate":false}}}
// @pdg-member {"name":"Scene.createSpriteLayer","native_binding":{"adapter":"Scene.createSpriteLayer","allow_raw_pointers":true}}
