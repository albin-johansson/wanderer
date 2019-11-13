cmake_minimum_required(VERSION 3.15)
project(${CMAKE_PROJECT_NAME}_src)

set(SOURCE_FILES
        service/bool_converter.h

        controller/key_state_manager.cpp
        controller/key_state_manager.h
        controller/wanderer_controller.h
        controller/wanderer_controller_impl.cpp
        controller/wanderer_controller_impl.h
        controller/wanderer_controller_factory.h

        controller/gameloop/game_loop.h
        controller/gameloop/smooth_fixed_timestep_loop.cpp
        controller/gameloop/smooth_fixed_timestep_loop.h

        core/wanderer_core.h
        core/wanderer_core_impl.cpp
        core/wanderer_core_impl.h
        core/wanderer_core_factory.h
        core/tickable.h
        core/objects.h
        core/game_object.h
        core/drawable.h
        core/direction.h

        core/math/rectangle.cpp
        core/math/rectangle.h
        core/math/vector_2.cpp
        core/math/vector_2.h

        core/entities/entity.h
        core/entities/player.cpp
        core/entities/player.h
        core/entities/movable_object.h
        core/entities/movable_delegate.cpp
        core/entities/movable_delegate.h

        core/tiles/tile.h
        core/tiles/tile_map.cpp
        core/tiles/tile_map.h
        core/tiles/grass_tile.cpp
        core/tiles/grass_tile.h
        core/tiles/abstract_tile.cpp
        core/tiles/abstract_tile.h

        core/bad_state_exception.cpp
        core/bad_state_exception.h
        core/input.cpp
        core/input.h
        core/viewport.cpp
        core/viewport.h

        core/entities/entitystate/entity_moving_state.cpp
        core/entities/entitystate/entity_moving_state.h
        core/entities/entitystate/entity_state.h
        core/entities/entitystate/entity_state_machine.h
        core/entities/entitystate/entity_state_id.h
        core/entities/entitystate/entity_idle_state.cpp
        core/entities/entitystate/entity_idle_state.h
        core/entities/entitystate/entity_state_machine_impl.cpp
        core/entities/entitystate/entity_state_machine_impl.h

        visuals/window.h
        visuals/window.cpp
        visuals/renderer.h
        visuals/renderer.cpp
        visuals/image.cpp
        visuals/image.h
        visuals/animation.cpp
        visuals/animation.h visuals/image_generator.cpp visuals/image_generator.h core/entities/entitystate/entity_draw_delegate.cpp core/entities/entitystate/entity_draw_delegate.h core/entities/entity_sheet.cpp core/entities/entity_sheet.h)

# Prepares the Wanderer "library", which excludes linking and the main.cpp file
add_library(${WANDERER_LIB} ${SOURCE_FILES})

target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} PUBLIC controller)
target_include_directories(${WANDERER_LIB} PUBLIC controller/gameloop)
target_include_directories(${WANDERER_LIB} PUBLIC core)
target_include_directories(${WANDERER_LIB} PUBLIC visuals)
target_include_directories(${WANDERER_LIB} PUBLIC util)
target_include_directories(${WANDERER_LIB} PUBLIC service)
target_include_directories(${WANDERER_LIB} PUBLIC core/math)
target_include_directories(${WANDERER_LIB} PUBLIC core/tiles)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities/entitystate)

# Prepares the actual executable
add_executable(${WANDERER_EXECUTABLE} main.cpp)

target_link_directories(${WANDERER_EXECUTABLE} PUBLIC ${SDL2_LIBRARY})
target_link_directories(${WANDERER_EXECUTABLE} PUBLIC ${SDL2_IMAGE_LIBRARIES})
target_link_directories(${WANDERER_EXECUTABLE} PUBLIC ${SDL2_MIXER_LIBRARIES})
target_link_directories(${WANDERER_EXECUTABLE} PUBLIC ${SDL2_TTF_LIBRARIES})

target_link_libraries(${WANDERER_EXECUTABLE}
        mingw32
        ${WANDERER_LIB}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})

# Copies all of the files in the bin folder and puts them next to the executable
add_custom_command(TARGET ${WANDERER_EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${BINARIES_DIR}"
        ${CMAKE_BINARY_DIR}/src)

# Copies all of the resources and puts the in the build folder
add_custom_command(TARGET ${WANDERER_EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        ${CMAKE_BINARY_DIR}/src/resources)

