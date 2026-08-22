cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED PDG_SOURCE_DIR)
    get_filename_component(PDG_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
endif()

if(NOT DEFINED RELEASE_TAG OR RELEASE_TAG STREQUAL "")
    if(DEFINED ENV{GITHUB_REF_NAME} AND NOT "$ENV{GITHUB_REF_NAME}" STREQUAL "")
        set(RELEASE_TAG "$ENV{GITHUB_REF_NAME}")
    else()
        message(FATAL_ERROR "RELEASE_TAG is required (for example: -DRELEASE_TAG=v1.0.0).")
    endif()
endif()

file(STRINGS "${PDG_SOURCE_DIR}/VERSION" PDG_VERSION_FILE LIMIT_COUNT 1)
string(STRIP "${PDG_VERSION_FILE}" PDG_VERSION_FILE)

file(READ "${PDG_SOURCE_DIR}/CMakeLists.txt" PDG_ROOT_CMAKE)
string(REGEX MATCH
    "[Pp][Rr][Oo][Jj][Ee][Cc][Tt][ \t\r\n]*\\([ \t\r\n]*PDG[ \t\r\n]+VERSION[ \t\r\n]+([0-9]+\\.[0-9]+\\.[0-9]+)"
    PDG_PROJECT_MATCH
    "${PDG_ROOT_CMAKE}"
)
set(PDG_CMAKE_VERSION "${CMAKE_MATCH_1}")

if(PDG_CMAKE_VERSION STREQUAL "")
    message(FATAL_ERROR "Could not read the PDG project version from CMakeLists.txt.")
endif()

if(NOT RELEASE_TAG MATCHES "^v?([0-9]+\\.[0-9]+\\.[0-9]+)$")
    message(FATAL_ERROR "Release tag '${RELEASE_TAG}' must have the form vMAJOR.MINOR.PATCH.")
endif()
set(PDG_TAG_VERSION "${CMAKE_MATCH_1}")

if(NOT PDG_VERSION_FILE STREQUAL PDG_CMAKE_VERSION)
    message(FATAL_ERROR
        "Version mismatch: VERSION contains '${PDG_VERSION_FILE}', but CMakeLists.txt declares '${PDG_CMAKE_VERSION}'."
    )
endif()

if(NOT PDG_VERSION_FILE STREQUAL PDG_TAG_VERSION)
    message(FATAL_ERROR
        "Version mismatch: tag '${RELEASE_TAG}' represents '${PDG_TAG_VERSION}', but the project version is '${PDG_VERSION_FILE}'."
    )
endif()

message(STATUS "Validated PDG release ${RELEASE_TAG} (version ${PDG_VERSION_FILE})")
