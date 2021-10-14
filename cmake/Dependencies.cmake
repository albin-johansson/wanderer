include(FetchContent)

# JSON
FetchContent_Declare(json
    GIT_REPOSITORY "https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent"
    GIT_TAG "v3.10.3"
    )

FetchContent_MakeAvailable(json)

set(JSON_INCLUDE_DIRS "${json_SOURCE_DIR}/include/nlohmann" CACHE INTERNAL "")
set(JSON_LIBRARIES nlohmann_json CACHE INTERNAL "")

# Centurion
FetchContent_Declare(centurion
     GIT_REPOSITORY "https://github.com/albin-johansson/centurion.git"
     GIT_TAG "cmake-package"
     )

set(CEN_TESTS OFF)
set(CEN_EXAMPLES OFF)
set(CEN_MOCK_FRIENDLY_MODE OFF)

FetchContent_MakeAvailable(centurion)

message("Centurion source dir: ${centurion_SOURCE_DIR}")
set(CENTURION_INCLUDE_DIRS "${centurion_SOURCE_DIR}/src" CACHE INTERNAL "")
set(CENTURION_LIBRARIES libcenturion CACHE INTERNAL "")

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