# Keep third-party cache options and install rules outside PDG's CMake project.
include(ExternalProject)
set(pdg_wt_build "${PDG_SOURCE_DIR}/build/webtransport/desktop-${BUILD_SUBDIR}")
set(pdg_wt_args -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
foreach(name CMAKE_C_COMPILER CMAKE_CXX_COMPILER CMAKE_OSX_SYSROOT CMAKE_OSX_ARCHITECTURES CMAKE_OSX_DEPLOYMENT_TARGET CMAKE_TOOLCHAIN_FILE CMAKE_MSVC_RUNTIME_LIBRARY)
    if(DEFINED ${name} AND NOT "${${name}}" STREQUAL "")
        list(APPEND pdg_wt_args "-D${name}=${${name}}")
    endif()
endforeach()
# Optional source overrides support offline builds without sharing platform objects.
foreach(name PICOQUIC PICOTLS MBEDTLS CJSON)
    if(DEFINED FETCHCONTENT_SOURCE_DIR_${name})
        list(APPEND pdg_wt_args "-DFETCHCONTENT_SOURCE_DIR_${name}=${FETCHCONTENT_SOURCE_DIR_${name}}")
    endif()
endforeach()
set(pdg_wt_archive "${pdg_wt_build}/${CMAKE_STATIC_LIBRARY_PREFIX}pdg_webtransport_all${CMAKE_STATIC_LIBRARY_SUFFIX}")
ExternalProject_Add(pdg-webtransport-build
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sys/webtransport"
    BINARY_DIR "${pdg_wt_build}"
    CMAKE_ARGS ${pdg_wt_args}
    # The default recursive build inherits Make's jobserver; the bundle is ALL.
    BUILD_ALWAYS TRUE INSTALL_COMMAND "" BUILD_BYPRODUCTS "${pdg_wt_archive}")
add_library(pdg-webtransport-native STATIC IMPORTED GLOBAL)
set_target_properties(pdg-webtransport-native PROPERTIES IMPORTED_LOCATION "${pdg_wt_archive}")
add_dependencies(pdg-webtransport-native pdg-webtransport-build)
target_link_libraries(pdg pdg-webtransport-native)
target_compile_definitions(pdg PRIVATE PDG_USE_WEBTRANSPORT)
if(APPLE)
    target_link_libraries(pdg "-framework Security" "-framework CoreFoundation")
elseif(WIN32)
    target_link_libraries(pdg crypt32 ws2_32)
else()
    find_package(Threads REQUIRED)
    target_link_libraries(pdg Threads::Threads)
endif()

add_custom_command(TARGET pdg POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/sys/webtransport/THIRD_PARTY_NOTICES.txt" "$<TARGET_FILE_DIR:pdg>/WebTransport-Licenses.txt")
