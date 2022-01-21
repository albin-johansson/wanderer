cmake_minimum_required(VERSION 3.15)

project(wanderer-proto CXX)

set(PROTO_FILES
    # TODO
    )

protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${PROTO_FILES})

add_library(${TARGET_WANDERER_PROTO} ${PROTO_HEADERS} ${PROTO_SOURCES})

target_include_directories(${TARGET_WANDERER_PROTO} SYSTEM PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${TARGET_WANDERER_PROTO} PRIVATE protobuf::libprotobuf)
