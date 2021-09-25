cmake_minimum_required(VERSION 3.15)

project(wanderer-io CXX)

set(WANDERER_IO_SOURCES

    ${PROJECT_SOURCE_DIR}/directories.cpp
    ${PROJECT_SOURCE_DIR}/directories.hpp
    ${PROJECT_SOURCE_DIR}/rune_configuration.cpp
    ${PROJECT_SOURCE_DIR}/rune_configuration.hpp

    ${PROJECT_SOURCE_DIR}/parsing/common.hpp
    ${PROJECT_SOURCE_DIR}/parsing/common.cpp
    ${PROJECT_SOURCE_DIR}/parsing/csv.cpp
    ${PROJECT_SOURCE_DIR}/parsing/csv.hpp
    ${PROJECT_SOURCE_DIR}/parsing/parse_ir.hpp
    ${PROJECT_SOURCE_DIR}/parsing/parse_layers.cpp
    ${PROJECT_SOURCE_DIR}/parsing/parse_layers.hpp
    ${PROJECT_SOURCE_DIR}/parsing/parse_tilesets.cpp
    ${PROJECT_SOURCE_DIR}/parsing/parse_tilesets.hpp
    ${PROJECT_SOURCE_DIR}/parsing/parse_world.cpp
    ${PROJECT_SOURCE_DIR}/parsing/parse_world.hpp

    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_container.cpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_container.hpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_hitbox.cpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_hitbox.hpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_light.cpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_light.hpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_object_layer.cpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_object_layer.hpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_plant.cpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_plant.hpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_portal.cpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_portal.hpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_spawnpoint.cpp
    ${PROJECT_SOURCE_DIR}/parsing/objects/parse_spawnpoint.hpp

    ${PROJECT_SOURCE_DIR}/parsing/tiles/make_tile_matrix.cpp
    ${PROJECT_SOURCE_DIR}/parsing/tiles/make_tile_matrix.hpp
    ${PROJECT_SOURCE_DIR}/parsing/tiles/parse_ground_layer.cpp
    ${PROJECT_SOURCE_DIR}/parsing/tiles/parse_ground_layer.hpp
    ${PROJECT_SOURCE_DIR}/parsing/tiles/parse_tile.cpp
    ${PROJECT_SOURCE_DIR}/parsing/tiles/parse_tile.hpp
    ${PROJECT_SOURCE_DIR}/parsing/tiles/parse_tile_layer.cpp
    ${PROJECT_SOURCE_DIR}/parsing/tiles/parse_tile_layer.hpp
    ${PROJECT_SOURCE_DIR}/parsing/tiles/parse_tile_objects.cpp
    ${PROJECT_SOURCE_DIR}/parsing/tiles/parse_tile_objects.hpp

    ${PROJECT_SOURCE_DIR}/saves/delete_save.cpp
    ${PROJECT_SOURCE_DIR}/saves/delete_save.hpp
    ${PROJECT_SOURCE_DIR}/saves/load_game.cpp
    ${PROJECT_SOURCE_DIR}/saves/load_game.hpp
    ${PROJECT_SOURCE_DIR}/saves/parse_save_file.cpp
    ${PROJECT_SOURCE_DIR}/saves/parse_save_file.hpp
    ${PROJECT_SOURCE_DIR}/saves/save_game.cpp
    ${PROJECT_SOURCE_DIR}/saves/save_game.hpp

    PARENT_SCOPE)