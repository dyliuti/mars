cmake_minimum_required(VERSION 3.6)
project(sample2_xlog_demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sample2_demo src/main.cpp)

if(MSVC)
    set_property(TARGET sample2_demo PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_include_directories(sample2_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_link_libraries(sample2_demo PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/xlog.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcrypto.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libssl.lib
        ws2_32
        crypt32
    )
else()
    message(FATAL_ERROR "sample2 demo currently targets Windows/MSVC only.")
endif()
