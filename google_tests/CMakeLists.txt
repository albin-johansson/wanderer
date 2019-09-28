project(GoogleTests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SRC_FILES objects_test.cpp vector_2_test.cpp direction_test.cpp)

add_executable(Google_Tests_run ${SRC_FILES})

target_link_libraries(Google_Tests_run gtest gtest_main)