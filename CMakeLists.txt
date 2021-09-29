cmake_minimum_required(VERSION 3.15)

project(wanderer
    VERSION 0.1.0
    LANGUAGES CXX
    HOMEPAGE_URL "https://github.com/albin-johansson/wanderer")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 23)

include(Utilities)
include(Dependencies)

# Helper variables for directory paths
set(WANDERER_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/resources)
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)
set(GENERATED_PROTOBUF_DIR ${PROJECT_SOURCE_DIR}/proto/generated)

# The various targets used
set(WANDERER_LIB_TARGET libWanderer)
set(WANDERER_TEST_TARGET testWanderer)
set(WANDERER_EXE_TARGET Wanderer)

if (WIN32)
  find_env_var(SDL2DIR SDL2)
  find_env_var(SDL2IMAGEDIR SDL2_image)
  find_env_var(SDL2MIXERDIR SDL2_mixer)
  find_env_var(SDL2TTFDIR SDL2_ttf)
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_library(wandererproto
    ${GENERATED_PROTOBUF_DIR}/animated.pb.cc
    ${GENERATED_PROTOBUF_DIR}/animated.pb.h
    ${GENERATED_PROTOBUF_DIR}/area.pb.cc
    ${GENERATED_PROTOBUF_DIR}/area.pb.h
    ${GENERATED_PROTOBUF_DIR}/associated_entity.pb.cc
    ${GENERATED_PROTOBUF_DIR}/associated_entity.pb.h
    ${GENERATED_PROTOBUF_DIR}/chase.pb.cc
    ${GENERATED_PROTOBUF_DIR}/chase.pb.h
    ${GENERATED_PROTOBUF_DIR}/color.pb.cc
    ${GENERATED_PROTOBUF_DIR}/color.pb.h
    ${GENERATED_PROTOBUF_DIR}/depth_drawable.pb.cc
    ${GENERATED_PROTOBUF_DIR}/depth_drawable.pb.h
    ${GENERATED_PROTOBUF_DIR}/float2.pb.cc
    ${GENERATED_PROTOBUF_DIR}/float2.pb.h
    ${GENERATED_PROTOBUF_DIR}/float3.pb.cc
    ${GENERATED_PROTOBUF_DIR}/float3.pb.h
    ${GENERATED_PROTOBUF_DIR}/hitbox.pb.cc
    ${GENERATED_PROTOBUF_DIR}/hitbox.pb.h
    ${GENERATED_PROTOBUF_DIR}/inventory.pb.cc
    ${GENERATED_PROTOBUF_DIR}/inventory.pb.h
    ${GENERATED_PROTOBUF_DIR}/movable.pb.cc
    ${GENERATED_PROTOBUF_DIR}/movable.pb.h
    ${GENERATED_PROTOBUF_DIR}/object.pb.cc
    ${GENERATED_PROTOBUF_DIR}/object.pb.h
    ${GENERATED_PROTOBUF_DIR}/particle.pb.cc
    ${GENERATED_PROTOBUF_DIR}/particle.pb.h
    ${GENERATED_PROTOBUF_DIR}/plant.pb.cc
    ${GENERATED_PROTOBUF_DIR}/plant.pb.h
    ${GENERATED_PROTOBUF_DIR}/point_light.pb.cc
    ${GENERATED_PROTOBUF_DIR}/point_light.pb.h
    ${GENERATED_PROTOBUF_DIR}/portal.pb.cc
    ${GENERATED_PROTOBUF_DIR}/portal.pb.h
    ${GENERATED_PROTOBUF_DIR}/rect.pb.cc
    ${GENERATED_PROTOBUF_DIR}/rect.pb.h
    ${GENERATED_PROTOBUF_DIR}/save.pb.cc
    ${GENERATED_PROTOBUF_DIR}/save.pb.h
    ${GENERATED_PROTOBUF_DIR}/spawnpoint.pb.cc
    ${GENERATED_PROTOBUF_DIR}/spawnpoint.pb.h
    ${GENERATED_PROTOBUF_DIR}/tile.pb.cc
    ${GENERATED_PROTOBUF_DIR}/tile.pb.h
    ${GENERATED_PROTOBUF_DIR}/tile_animation.pb.cc
    ${GENERATED_PROTOBUF_DIR}/tile_animation.pb.h
    ${GENERATED_PROTOBUF_DIR}/tile_layer.pb.cc
    ${GENERATED_PROTOBUF_DIR}/tile_layer.pb.h
    ${GENERATED_PROTOBUF_DIR}/tile_object.pb.cc
    ${GENERATED_PROTOBUF_DIR}/tile_object.pb.h
    ${GENERATED_PROTOBUF_DIR}/tilemap.pb.cc
    ${GENERATED_PROTOBUF_DIR}/tilemap.pb.h
    ${GENERATED_PROTOBUF_DIR}/tileset.pb.cc
    ${GENERATED_PROTOBUF_DIR}/tileset.pb.h
    ${GENERATED_PROTOBUF_DIR}/time_of_day.pb.cc
    ${GENERATED_PROTOBUF_DIR}/time_of_day.pb.h
    ${GENERATED_PROTOBUF_DIR}/trigger.pb.cc
    ${GENERATED_PROTOBUF_DIR}/trigger.pb.h
    )
target_include_directories(wandererproto SYSTEM PUBLIC ${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(wandererproto PUBLIC ${PROTOBUF_LIBRARIES})

add_subdirectory(src)
add_subdirectory(test)