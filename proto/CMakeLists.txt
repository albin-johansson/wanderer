cmake_minimum_required(VERSION 3.15)

project(wanderer-proto CXX)

find_package(Protobuf CONFIG REQUIRED)

set(PROTO_FILES
    animation.proto
    associated_entity.proto
    chase.proto
    color.proto
    drawable.proto
    float2.proto
    float3.proto
    hitbox.proto
    inventory.proto
    level.proto
    map_object.proto
    movable.proto
    particle.proto
    plant.proto
    point_light.proto
    portal.proto
    rect.proto
    save.proto
    spawnpoint.proto
    tile.proto
    tile_animation.proto
    tile_layer.proto
    tile_object.proto
    tileset.proto
    time_of_day.proto
    trigger.proto
    )

protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${PROTO_FILES})

add_library(${WANDERER_PROTO} ${PROTO_HEADERS} ${PROTO_SOURCES})

target_include_directories(${WANDERER_PROTO} SYSTEM PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${WANDERER_PROTO} PUBLIC
    protobuf::libprotobuf
    protobuf::libprotobuf-lite
    )
