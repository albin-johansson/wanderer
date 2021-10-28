cmake_minimum_required(VERSION 3.15)

project(wanderer-proto CXX)

set(GENERATED_FILES
    generated/animation.pb.cc
    generated/animation.pb.h
    generated/associated_entity.pb.cc
    generated/associated_entity.pb.h
    generated/chase.pb.cc
    generated/chase.pb.h
    generated/color.pb.cc
    generated/color.pb.h
    generated/drawable.pb.cc
    generated/drawable.pb.h
    generated/float2.pb.cc
    generated/float2.pb.h
    generated/float3.pb.cc
    generated/float3.pb.h
    generated/hitbox.pb.cc
    generated/hitbox.pb.h
    generated/inventory.pb.cc
    generated/inventory.pb.h
    generated/level.pb.cc
    generated/level.pb.h
    generated/map_object.pb.cc
    generated/map_object.pb.h
    generated/movable.pb.cc
    generated/movable.pb.h
    generated/particle.pb.cc
    generated/particle.pb.h
    generated/plant.pb.cc
    generated/plant.pb.h
    generated/point_light.pb.cc
    generated/point_light.pb.h
    generated/portal.pb.cc
    generated/portal.pb.h
    generated/rect.pb.cc
    generated/rect.pb.h
    generated/save.pb.cc
    generated/save.pb.h
    generated/spawnpoint.pb.cc
    generated/spawnpoint.pb.h
    generated/tile.pb.cc
    generated/tile.pb.h
    generated/tile_animation.pb.cc
    generated/tile_animation.pb.h
    generated/tile_layer.pb.cc
    generated/tile_layer.pb.h
    generated/tile_object.pb.cc
    generated/tile_object.pb.h
    generated/tileset.pb.cc
    generated/tileset.pb.h
    generated/time_of_day.pb.cc
    generated/time_of_day.pb.h
    generated/trigger.pb.cc
    generated/trigger.pb.h
    )

add_library(${WANDERER_PROTO} ${GENERATED_FILES})

target_include_directories(${WANDERER_PROTO} SYSTEM PUBLIC ${PROTOBUF_INCLUDE_DIRS})

target_link_libraries(${WANDERER_PROTO} PUBLIC ${PROTOBUF_LIBRARIES})
