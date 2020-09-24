cmake_minimum_required(VERSION 3.15)

project(WandererTest CXX)
enable_testing()

set(TEST_FILES
        unittest/test_main.cpp
        unittest/hitbox_test.cpp
        unittest/humanoid_state_test.cpp
        unittest/event_connections_test.cpp
        unittest/aabb_test.cpp
        unittest/vector2_test.cpp)

add_executable(${WANDERER_TEST_TARGET} ${TEST_FILES})
add_dependencies(${WANDERER_TEST_TARGET} ${WANDERER_LIB_TARGET})

set_target_properties(${WANDERER_TEST_TARGET} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

add_library(libCatch INTERFACE)
target_include_directories(libCatch INTERFACE catch)

add_test(NAME ${WANDERER_TEST_TARGET}
        COMMAND ${WANDERER_TEST_TARGET})

target_include_directories(${WANDERER_TEST_TARGET} PUBLIC unittest)

target_include_directories(${WANDERER_TEST_TARGET}
        SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
        SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
        SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
        SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
        SYSTEM PUBLIC ${LIBRARY_DIR}/centurion
        SYSTEM PUBLIC ${LIBRARY_DIR}/json
        SYSTEM PUBLIC ${LIBRARY_DIR}/entt)

target_link_libraries(${WANDERER_TEST_TARGET}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${CENTURION_IMPORT_LIB}
        PUBLIC ${WANDERER_LIB_TARGET}
        PUBLIC libENTT
        PUBLIC libJSON
        PUBLIC libNamedType
        PUBLIC libGSL
        PUBLIC libCatch)

copy_directory_post_build(${WANDERER_TEST_TARGET} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
copy_directory_post_build(${WANDERER_TEST_TARGET} ${RESOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/resource")