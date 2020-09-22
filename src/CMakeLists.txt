cmake_minimum_required(VERSION 3.15)

project(WandererSrc CXX)

function(wanderer_set_properties [target [outputName]])
    set_target_properties(${ARGV0} PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            OUTPUT_NAME ${ARGV1})
endfunction()

set(SOURCE_FILES
        doxygen_docs.h

        core/wanderer_stdinc.h
        core/game.h
        core/game.cpp
        core/application.cpp
        core/application.h
        core/game_loop.h
        core/game_loop.cpp
        core/direction.h
        core/game_constants.h

        core/add_humanoid_state_dependencies.cpp
        core/add_humanoid_state_dependencies.h
        core/event_connections.cpp
        core/event_connections.h

        core/resource/image_loader.cpp
        core/resource/image_loader.h
        core/resource/image_cache.h

        core/math/vector_2.h
        core/math/random_utils.h
        core/math/math_utils.h

        utility/input.cpp
        utility/input.h

        component/player.h
        component/movable.h
        component/hitbox.h
        component/humanoid_state.h
        component/binds.h
        component/animated.h
        component/tilemap.h
        component/tile_layer.h
        component/tileset.h
        component/tile.h
        component/animated_tile.h
        component/render_bounds.h
        component/depth_drawable.h
        component/game_object.h
        component/viewport.h
        component/map_position.h
        component/aabb.h

        component/event/begin_attack_event.h
        component/event/end_attack_event.h
        component/event/begin_humanoid_move_event.h
        component/event/end_humanoid_move_event.h

        system/render_depth_drawables_system.cpp
        system/render_depth_drawables_system.h
        system/movement_system.cpp
        system/movement_system.h
        system/interpolation_system.h
        system/interpolation_system.cpp
        system/animation_system.cpp
        system/animation_system.h
        system/ground_layer_rendering_system.cpp
        system/ground_layer_rendering_system.h
        system/render_bounds_system.cpp
        system/render_bounds_system.h
        system/movable_depth_drawables_system.cpp
        system/movable_depth_drawables_system.h
        system/hitbox_system.cpp
        system/hitbox_system.h

        system/viewport/viewport_system.cpp
        system/viewport/viewport_system.h
        system/viewport/make_viewport_system.cpp
        system/viewport/make_viewport_system.h

        system/tile/tile_animation_system.cpp
        system/tile/tile_animation_system.h
        system/tile/tile_rendering_system.cpp
        system/tile/tile_rendering_system.h

        system/layer/layer_rendering_system.cpp
        system/layer/layer_rendering_system.h

        system/humanoid/humanoid_animation_system.cpp
        system/humanoid/humanoid_animation_system.h
        system/humanoid/humanoid_state_system.cpp
        system/humanoid/humanoid_state_system.h
        system/humanoid/humanoid_factory_system.cpp
        system/humanoid/humanoid_factory_system.h
        system/humanoid/humanoid_attack_event_handler.cpp
        system/humanoid/humanoid_attack_event_handler.h
        system/humanoid/humanoid_move_event_handler.cpp
        system/humanoid/humanoid_move_event_handler.h

        system/input/input_system.cpp
        system/input/input_system.h
        system/input/move_input_system.cpp
        system/input/move_input_system.h
        system/input/idle_input_system.cpp
        system/input/idle_input_system.h

        parse/tile/make_tile.cpp
        parse/tile/make_tile.h
        parse/tile/make_map.h
        parse/tile/make_map.cpp
        parse/tile/make_tileset.cpp
        parse/tile/make_tileset.h

        system/collision/aabb_system.cpp
        system/collision/aabb_system.h)

add_library(${WANDERER_LIB_TARGET} ${SOURCE_FILES})

target_compile_options(${WANDERER_LIB_TARGET} PRIVATE
        /EHsc
        /MP
        /W3)

wanderer_set_properties(${WANDERER_LIB_TARGET} "Wanderer")

add_header_only_lib(libENTT ${LIBRARY_DIR}/entt ${LIBRARY_DIR}/entt/entt.hpp)
add_header_only_lib(libJSON ${LIBRARY_DIR}/json ${LIBRARY_DIR}/json/json.hpp)

set(GSL_SOURCES
        ${LIBRARY_DIR}/microsoft/gsl
        ${LIBRARY_DIR}/microsoft/gsl_algorithm
        ${LIBRARY_DIR}/microsoft/gsl_assert
        ${LIBRARY_DIR}/microsoft/gsl_byte
        ${LIBRARY_DIR}/microsoft/gsl_util
        ${LIBRARY_DIR}/microsoft/multi_span
        ${LIBRARY_DIR}/microsoft/pointers
        ${LIBRARY_DIR}/microsoft/span
        ${LIBRARY_DIR}/microsoft/span_ext
        ${LIBRARY_DIR}/microsoft/string_span)
add_header_only_lib(libGSL ${LIBRARY_DIR}/microsoft ${GSL_SOURCES})

set(BOOST_SOURCES
        ${LIBRARY_DIR}/boost/assert.hpp
        ${LIBRARY_DIR}/boost/config.hpp
        ${LIBRARY_DIR}/boost/current_function.hpp)
add_header_only_lib(libBOOST ${LIBRARY_DIR}/boost ${BOOST_SOURCES})

set(NAMED_TYPE_SOURCES
        ${LIBRARY_DIR}/namedtype/named_type.hpp
        ${LIBRARY_DIR}/namedtype/named_type_impl.hpp
        ${LIBRARY_DIR}/namedtype/crtp.hpp
        ${LIBRARY_DIR}/namedtype/underlying_functionalities.hpp)
add_header_only_lib(libNamedType ${LIBRARY_DIR}/namedtype ${NAMED_TYPE_SOURCES})

# Library directories
target_include_directories(${WANDERER_LIB_TARGET}
        SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
        SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
        SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
        SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
        SYSTEM PUBLIC ${LIBRARY_DIR}/centurion
        SYSTEM PUBLIC ${LIBRARY_DIR}/step)

# Wanderer directories
target_include_directories(${WANDERER_LIB_TARGET}
        PUBLIC core
        PUBLIC core/math
        PUBLIC core/resource
        PUBLIC component
        PUBLIC component/event
        PUBLIC system
        PUBLIC system/input
        PUBLIC system/humanoid
        PUBLIC system/tile
        PUBLIC system/layer
        PUBLIC system/viewport
        PUBLIC system/collision
        PUBLIC utility
        PUBLIC parse
        PUBLIC parse/tile
        PUBLIC parse/menu)

#target_compile_definitions(${WANDERER_LIB} PUBLIC WANDERER_DEBUG)

target_link_libraries(${WANDERER_LIB_TARGET}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${CENTURION_IMPORT_LIB}
        PUBLIC libENTT
        PUBLIC libJSON
        PUBLIC libNamedType
        PUBLIC libGSL
        PUBLIC libBOOST)

add_executable(${WANDERER_EXE_TARGET} WIN32 main.cpp)

wanderer_set_properties(${WANDERER_EXE_TARGET} "Wanderer")

target_link_libraries(${WANDERER_EXE_TARGET}
        PUBLIC ${WANDERER_LIB_TARGET})

copy_directory_post_build(${WANDERER_EXE_TARGET} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
copy_directory_post_build(${WANDERER_EXE_TARGET} ${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resource)


