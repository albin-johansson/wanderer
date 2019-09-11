cmake_minimum_required(VERSION 3.14)

project(Wanderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES src/main.cpp src/model/model.h src/controller/controller.h src/controller/controller_impl.cpp src/controller/controller_impl.h src/controller/controller_factory.h src/model/model_impl.cpp src/model/model_impl.h src/model/model_factory.h src/view/view.h src/model/objects.h src/view/view_factory.h src/view/view_impl.cpp src/view/view_impl.h)

set(SDL2_ROOT ${PROJECT_SOURCE_DIR}/lib/SDL2)
set(CENTURION_ROOT ${PROJECT_SOURCE_DIR}/lib/Centurion)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/model)
include_directories(${PROJECT_SOURCE_DIR}/src/controller)
include_directories(${PROJECT_SOURCE_DIR}/src/view)

include_directories(${SDL2_ROOT}/include/SDL2)
include_directories(${CENTURION_ROOT}/include)

link_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_SOURCE_DIR}/src/model)
link_directories(${PROJECT_SOURCE_DIR}/src/controller)
link_directories(${PROJECT_SOURCE_DIR}/src/view)

link_directories(${SDL2_ROOT}/lib)
link_directories(${CENTURION_ROOT}/lib)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set(CENTURION_LIB ${CENTURION_ROOT}/lib/libCenturion.a)

target_link_libraries(${PROJECT_NAME}
        LINK_PUBLIC
        mingw32
        ${CENTURION_LIB}
        SDL2main
        SDL2
        SDL2_image
        SDL2_mixer
        SDL2_ttf)