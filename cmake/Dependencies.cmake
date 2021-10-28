include(FetchContent)

set(JSON_INCLUDE_DIRS "${LIBRARY_DIR}/nlohmann" CACHE INTERNAL "")

# Centurion
FetchContent_Declare(centurion
     GIT_REPOSITORY "https://github.com/albin-johansson/centurion.git"
     GIT_TAG "cmake-package")

FetchContent_MakeAvailable(centurion)

set(CENTURION_INCLUDE_DIRS "${centurion_SOURCE_DIR}/src" CACHE INTERNAL "")
set(CENTURION_LIBRARIES centurion CACHE INTERNAL "")

# Google Protocol Buffers
FetchContent_Declare(protobuf
    GIT_REPOSITORY "https://github.com/protocolbuffers/protobuf.git"
    GIT_TAG "v3.18.0"
    SOURCE_SUBDIR cmake)

set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(protobuf_WITH_ZLIB OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(protobuf)

set(PROTOBUF_INCLUDE_DIRS "${protobuf_SOURCE_DIR}/src" CACHE INTERNAL "")
set(PROTOBUF_LIBRARIES protobuf::libprotobuf CACHE INTERNAL "")

# Google Test
FetchContent_Declare(googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "master")

set(googletest_gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)