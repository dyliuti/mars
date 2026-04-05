cmake_minimum_required(VERSION 3.6)
project(xlog)

set(LIB2_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

set(BOOST_SRC
    mars/boost/throw_exception.cpp
    mars/boost/libs/filesystem/src/codecvt_error_category.cpp
    mars/boost/libs/filesystem/src/operations.cpp
    mars/boost/libs/filesystem/src/path.cpp
    mars/boost/libs/filesystem/src/path_traits.cpp
    mars/boost/libs/filesystem/src/portability.cpp
    mars/boost/libs/filesystem/src/utf8_codecvt_facet.cpp
    mars/boost/libs/filesystem/src/windows_file_codecvt.cpp
    mars/boost/libs/iostreams/src/mapped_file.cpp
    mars/boost/libs/system/src/error_code.cpp
)

file(GLOB_RECURSE ZSTD_SRC
    ${LIB2_DIR}/mars/zstd/lib/common/*.c
    ${LIB2_DIR}/mars/zstd/lib/compress/*.c
    ${LIB2_DIR}/mars/zstd/lib/decompress/*.c
)

set(XLOG_SRC
    mars/xlog/src/appender.cc
    mars/xlog/src/formater.cc
    mars/xlog/src/log_base_buffer.cc
    mars/xlog/src/log_zlib_buffer.cc
    mars/xlog/src/log_zstd_buffer.cc
    mars/xlog/src/xlogger_interface.cc
    mars/xlog/crypt/log_crypt.cc
    mars/xlog/crypt/micro-ecc-master/uECC.c
    mars/comm/assert/__assert.c
    mars/comm/adler32.c
    mars/comm/autobuffer.cc
    mars/comm/mmap_util.cc
    mars/comm/ptrbuffer.cc
    mars/comm/strutil.cc
    mars/comm/tickcount.cc
    mars/comm/time_utils.c
    mars/comm/xlogger/xloggerbase.c
    mars/comm/xlogger/xlogger.cc
    mars/comm/xlogger/xlogger_category.cc
    mars/comm/xlogger/loginfo_extract.c
)

if(MSVC)
    file(GLOB ZLIB_SRC ${LIB2_DIR}/mars/comm/windows/zlib/*.c)
    list(APPEND XLOG_SRC
        mars/comm/windows/projdef.cc
        mars/comm/windows/unistd.cpp
        mars/comm/windows/thread/thread-interupte.cpp
        mars/comm/windows/xlogger_threadinfo.cpp
        mars/comm/windows/sys/time.c
        mars/xlog/unix/ConsoleLog.cc
        ${ZLIB_SRC}
    )
    add_definitions(-D_WIN32 -DWIN32 -DUNICODE -D_UNICODE -DNOMINMAX -D_LIB -D__WIN32__)
    add_definitions(-DXLOGGER_TAG="mars::xlog")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FI${LIB2_DIR}/mars/comm/projdef.h /std:c++14")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   /FI${LIB2_DIR}/mars/comm/projdef.h")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    add_definitions(-DXLOGGER_TAG="mars::xlog")
    find_package(ZLIB REQUIRED)
    list(APPEND XLOG_SRC mars/xlog/unix/ConsoleLog.cc)
endif()

add_library(xlog STATIC ${XLOG_SRC} ${ZSTD_SRC} ${BOOST_SRC})

target_include_directories(xlog PUBLIC
    ${LIB2_DIR}
    ${LIB2_DIR}/mars
    ${LIB2_DIR}/mars/xlog
    ${LIB2_DIR}/mars/xlog/src
    ${LIB2_DIR}/mars/xlog/crypt
    ${LIB2_DIR}/mars/xlog/crypt/micro-ecc-master
    ${LIB2_DIR}/mars/comm
    ${LIB2_DIR}/mars/comm/xlogger
    ${LIB2_DIR}/mars/openssl/include
)

# zstd internal headers
include_directories(
    ${LIB2_DIR}/mars/zstd/lib
    ${LIB2_DIR}/mars/zstd/lib/common
)

if(MSVC)
    target_include_directories(xlog PUBLIC
        ${LIB2_DIR}/mars/comm/windows
        ${LIB2_DIR}/mars/comm/windows/zlib
    )
    target_link_libraries(xlog PUBLIC
        ${LIB2_DIR}/mars/openssl/openssl_lib_windows/x64/libcrypto.lib
        ${LIB2_DIR}/mars/openssl/openssl_lib_windows/x64/libssl.lib
        ws2_32.lib
        crypt32.lib
    )
elseif(UNIX)
    target_link_libraries(xlog ${ZLIB_LIBRARIES})
    target_include_directories(xlog PUBLIC ${ZLIB_INCLUDE_DIRS})
endif()
