cmake_minimum_required(VERSION 3.15)
project(WandererSource)

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
        system/collision/aabb_system.h
        component/aabb.h)

add_library(${WANDERER_LIB_TARGET} ${SOURCE_FILES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${WANDERER_LIB_TARGET} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wdouble-promotion
            -Wswitch-default
            -Wswitch-enum
            -Wunused
            -Wuninitialized
            -Wsuggest-final-types
            -Wsuggest-final-methods
            -Wduplicated-cond
            -Wconversion
            -fno-rtti)
else () # Assume MSVC
    target_compile_options(${WANDERER_LIB_TARGET} PRIVATE
            /EHsc
            /MP
            /W3)
endif ()

wanderer_set_properties(${WANDERER_LIB_TARGET} "Wanderer")

# Add header-only libraries
wanderer_add_header_only_lib(libENTT ${LIBRARY_DIR}/entt ${LIBRARY_DIR}/entt/entt.hpp)
wanderer_add_header_only_lib(libJSON ${LIBRARY_DIR}/json ${LIBRARY_DIR}/json/json.hpp)

wanderer_add_header_only_lib(libOptional
        ${LIBRARY_DIR}/optional
        ${LIBRARY_DIR}/optional/optional.hpp)


#wanderer_add_header_only_lib(libAABB
#        ${LIBRARY_DIR}/aabb
#        ${LIBRARY_DIR}/optional/optional.hpp)

wanderer_add_header_only_lib(libGSL
        ${LIBRARY_DIR}/gsl-lite
        ${LIBRARY_DIR}/gsl-lite/gsl-lite.hpp)

set(BOOST_SOURCES
        ${LIBRARY_DIR}/boost/assert.hpp
        ${LIBRARY_DIR}/boost/config.hpp
        ${LIBRARY_DIR}/boost/current_function.hpp)
wanderer_add_header_only_lib(libBOOST
        ${LIBRARY_DIR}/boost
        ${BOOST_SOURCES})

#set(AABB_SOURCES
#        ${LIBRARY_DIR}/aabb/AABB.h
#        ${LIBRARY_DIR}/aabb/AABB.cc)
#wanderer_add_header_only_lib(libAABB ${LIBRARY_DIR}/aabb ${AABB_SOURCES})

set(NAMED_TYPE_SOURCES
        ${LIBRARY_DIR}/namedtype/named_type.hpp
        ${LIBRARY_DIR}/namedtype/named_type_impl.hpp
        ${LIBRARY_DIR}/namedtype/crtp.hpp
        ${LIBRARY_DIR}/namedtype/underlying_functionalities.hpp)
wanderer_add_header_only_lib(libNamedType ${LIBRARY_DIR}/namedtype ${NAMED_TYPE_SOURCES})

set(SIMPLEVOXELENGINE_TYPE_SOURCES
        ${LIBRARY_DIR}/simplevoxelengine/AABB.h
        ${LIBRARY_DIR}/simplevoxelengine/AABBTree.h
        ${LIBRARY_DIR}/simplevoxelengine/AABBTree.cpp
        ${LIBRARY_DIR}/simplevoxelengine/IAABB.h)
wanderer_add_header_only_lib(libSVEAABB ${LIBRARY_DIR}/simplevoxelengine ${SIMPLEVOXELENGINE_TYPE_SOURCES})


#set(BOX2D_SOURCES
#        ${LIBRARY_DIR}/box2d/b2_broad_phase.cpp
#        ${LIBRARY_DIR}/box2d/b2_chain_shape.cpp
#        ${LIBRARY_DIR}/box2d/b2_circle_shape.cpp
#        ${LIBRARY_DIR}/box2d/b2_collide_circle.cpp
#        ${LIBRARY_DIR}/box2d/b2_collide_edge.cpp
#        ${LIBRARY_DIR}/box2d/b2_collide_polygon.cpp
#        ${LIBRARY_DIR}/box2d/b2_collision.cpp
#        ${LIBRARY_DIR}/box2d/b2_distance.cpp
#        ${LIBRARY_DIR}/box2d/b2_dynamic_tree.cpp
#        ${LIBRARY_DIR}/box2d/b2_edge_shape.cpp
#        ${LIBRARY_DIR}/box2d/b2_polygon_shape.cpp
#        ${LIBRARY_DIR}/box2d/b2_time_of_impact.cpp
#        ${LIBRARY_DIR}/box2d/b2_block_allocator.cpp
#        ${LIBRARY_DIR}/box2d/b2_draw.cpp
#        ${LIBRARY_DIR}/box2d/b2_math.cpp
#        ${LIBRARY_DIR}/box2d/b2_settings.cpp
#        ${LIBRARY_DIR}/box2d/b2_stack_allocator.cpp
#        ${LIBRARY_DIR}/box2d/b2_timer.cpp
#        ${LIBRARY_DIR}/box2d/b2_body.cpp
#        ${LIBRARY_DIR}/box2d/b2_chain_circle_contact.cpp
#        ${LIBRARY_DIR}/box2d/b2_chain_circle_contact.h
#        ${LIBRARY_DIR}/box2d/b2_chain_polygon_contact.cpp
#        ${LIBRARY_DIR}/box2d/b2_chain_polygon_contact.h
#        ${LIBRARY_DIR}/box2d/b2_circle_contact.cpp
#        ${LIBRARY_DIR}/box2d/b2_circle_contact.h
#        ${LIBRARY_DIR}/box2d/b2_contact.cpp
#        ${LIBRARY_DIR}/box2d/b2_contact_manager.cpp
#        ${LIBRARY_DIR}/box2d/b2_contact_solver.cpp
#        ${LIBRARY_DIR}/box2d/b2_contact_solver.h
#        ${LIBRARY_DIR}/box2d/b2_distance_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_edge_circle_contact.cpp
#        ${LIBRARY_DIR}/box2d/b2_edge_circle_contact.h
#        ${LIBRARY_DIR}/box2d/b2_edge_polygon_contact.cpp
#        ${LIBRARY_DIR}/box2d/b2_edge_polygon_contact.h
#        ${LIBRARY_DIR}/box2d/b2_fixture.cpp
#        ${LIBRARY_DIR}/box2d/b2_friction_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_gear_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_island.cpp
#        ${LIBRARY_DIR}/box2d/b2_island.h
#        ${LIBRARY_DIR}/box2d/b2_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_motor_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_mouse_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_polygon_circle_contact.cpp
#        ${LIBRARY_DIR}/box2d/b2_polygon_circle_contact.h
#        ${LIBRARY_DIR}/box2d/b2_polygon_contact.cpp
#        ${LIBRARY_DIR}/box2d/b2_polygon_contact.h
#        ${LIBRARY_DIR}/box2d/b2_prismatic_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_pulley_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_revolute_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_rope_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_weld_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_wheel_joint.cpp
#        ${LIBRARY_DIR}/box2d/b2_world.cpp
#        ${LIBRARY_DIR}/box2d/b2_world_callbacks.cpp
#        ${LIBRARY_DIR}/box2d/b2_rope.cpp
#        ${LIBRARY_DIR}/box2d/b2_block_allocator.h
#        ${LIBRARY_DIR}/box2d/b2_body.h
#        ${LIBRARY_DIR}/box2d/b2_broad_phase.h
#        ${LIBRARY_DIR}/box2d/b2_chain_shape.h
#        ${LIBRARY_DIR}/box2d/b2_circle_shape.h
#        ${LIBRARY_DIR}/box2d/b2_collision.h
#        ${LIBRARY_DIR}/box2d/b2_contact.h
#        ${LIBRARY_DIR}/box2d/b2_contact_manager.h
#        ${LIBRARY_DIR}/box2d/b2_distance.h
#        ${LIBRARY_DIR}/box2d/b2_distance_joint.h
#        ${LIBRARY_DIR}/box2d/b2_draw.h
#        ${LIBRARY_DIR}/box2d/b2_dynamic_tree.h
#        ${LIBRARY_DIR}/box2d/b2_edge_shape.h
#        ${LIBRARY_DIR}/box2d/b2_fixture.h
#        ${LIBRARY_DIR}/box2d/b2_friction_joint.h
#        ${LIBRARY_DIR}/box2d/b2_gear_joint.h
#        ${LIBRARY_DIR}/box2d/b2_growable_stack.h
#        ${LIBRARY_DIR}/box2d/b2_joint.h
#        ${LIBRARY_DIR}/box2d/b2_math.h
#        ${LIBRARY_DIR}/box2d/b2_motor_joint.h
#        ${LIBRARY_DIR}/box2d/b2_mouse_joint.h
#        ${LIBRARY_DIR}/box2d/b2_polygon_shape.h
#        ${LIBRARY_DIR}/box2d/b2_prismatic_joint.h
#        ${LIBRARY_DIR}/box2d/b2_pulley_joint.h
#        ${LIBRARY_DIR}/box2d/b2_revolute_joint.h
#        ${LIBRARY_DIR}/box2d/b2_rope.h
#        ${LIBRARY_DIR}/box2d/b2_rope_joint.h
#        ${LIBRARY_DIR}/box2d/b2_settings.h
#        ${LIBRARY_DIR}/box2d/b2_shape.h
#        ${LIBRARY_DIR}/box2d/b2_stack_allocator.h
#        ${LIBRARY_DIR}/box2d/b2_time_of_impact.h
#        ${LIBRARY_DIR}/box2d/b2_timer.h
#        ${LIBRARY_DIR}/box2d/b2_time_step.h
#        ${LIBRARY_DIR}/box2d/b2_weld_joint.h
#        ${LIBRARY_DIR}/box2d/b2_wheel_joint.h
#        ${LIBRARY_DIR}/box2d/b2_world.h
#        ${LIBRARY_DIR}/box2d/b2_world_callbacks.h
#        ${LIBRARY_DIR}/box2d/box2d.h)
#wanderer_add_header_only_lib(libBox2D ${LIBRARY_DIR}/box2d ${BOX2D_SOURCES})

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
        PUBLIC ${CENTURION_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${STEP_LIBRARY}
        PUBLIC libENTT
        PUBLIC libJSON
        PUBLIC libNamedType
        PUBLIC libOptional
        PUBLIC libGSL
        PUBLIC libSVEAABB
        PUBLIC libBOOST)

add_executable(${WANDERER_EXE_TARGET} main.cpp)

wanderer_set_properties(${WANDERER_EXE_TARGET} "Wanderer")

target_link_libraries(${WANDERER_EXE_TARGET}
        PUBLIC ${WANDERER_LIB_TARGET})

copy_directory_post_build(${WANDERER_EXE_TARGET} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
copy_directory_post_build(${WANDERER_EXE_TARGET} ${RESOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/resource)


