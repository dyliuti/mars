cmake_minimum_required(VERSION 3.6)
project(xlog_example)

set(CMAKE_CXX_STANDARD 14)

set(LIB2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_subdirectory(${LIB2_DIR} ${CMAKE_BINARY_DIR}/xlog)

add_executable(xlog_example main.cpp)

target_link_libraries(xlog_example PRIVATE xlog)
target_include_directories(xlog_example PRIVATE
    ${LIB2_DIR}
    ${LIB2_DIR}/mars
    ${LIB2_DIR}/mars/comm/windows
)
