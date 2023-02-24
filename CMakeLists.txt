cmake_minimum_required(VERSION 2.8)
project(kiwi)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/yaml-cpp)

include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

include_directories(.)
# include_directories(/apps/kiwi/include)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/yaml-cpp/include)
# link_directories(/apps/kiwi/lib)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(LIB_SRC
    kiwi/address.cc
    kiwi/bytearray.cc
    kiwi/config.cc
    kiwi/fd_manager.cc
    kiwi/fiber.cc
    kiwi/http/http.cc
    kiwi/http/http_connection.cc
    kiwi/http/http_parser.cc
    kiwi/http/http_session.cc
    kiwi/http/http_server.cc
    kiwi/http/servlet.cc
    kiwi/hook.cc
    kiwi/iomanager.cc
    kiwi/log.cc
    kiwi/scheduler.cc
    kiwi/socket.cc
    kiwi/socket_stream.cc
    kiwi/stream.cc
    kiwi/tcp_server.cc
    kiwi/timer.cc
    kiwi/thread.cc
    kiwi/util.cc
    )

ragelmaker(kiwi/http/http11_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/kiwi/http)
ragelmaker(kiwi/http/httpclient_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/kiwi/http)
ragelmaker(kiwi/uri.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/kiwi)

add_library(kiwi SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(kiwi) #__FILE__
#add_library(kiwi_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (kiwi_static PROPERTIES OUTPUT_NAME "kiwi")

find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)
#set(LIBS ${LIBS} kiwi)
#set(LIBS ${LIBS} dl)
#set(LIBS ${LIBS} ${YAMLCPP})
#set(LIBS ${LIBS} ${PTHREAD})

set(LIBS
        kiwi
        dl
        pthread
        yaml-cpp)

kiwi_add_executable(test1 "tests/test.cc" kiwi "${LIBS}")
kiwi_add_executable(test_config "tests/test_config.cc" kiwi "${LIBS}")
kiwi_add_executable(test_thread "tests/test_thread.cc" kiwi "${LIBS}")
kiwi_add_executable(test_util "tests/test_util.cc" kiwi "${LIBS}")
kiwi_add_executable(test_fiber "tests/test_fiber.cc" kiwi "${LIBS}")
kiwi_add_executable(test_scheduler "tests/test_scheduler.cc" kiwi "${LIBS}")
kiwi_add_executable(test_iomanager "tests/test_iomanager.cc" kiwi "${LIBS}")
kiwi_add_executable(test_hook "tests/test_hook.cc" kiwi "${LIBS}")
kiwi_add_executable(test_address "tests/test_address.cc" kiwi "${LIBS}")
kiwi_add_executable(test_socket "tests/test_socket.cc" kiwi "${LIBS}")
kiwi_add_executable(test_bytearray "tests/test_bytearray.cc" kiwi "${LIBS}")
kiwi_add_executable(test_http "tests/test_http.cc" kiwi "${LIBS}")
kiwi_add_executable(test_http_parser "tests/test_http_parser.cc" kiwi "${LIBS}")
kiwi_add_executable(test_tcp_server "tests/test_tcp_server.cc" kiwi "${LIBS}")
kiwi_add_executable(echo_server "examples/echo_server.cc" kiwi "${LIBS}")
kiwi_add_executable(test_http_server "tests/test_http_server.cc" kiwi "${LIBS}")
kiwi_add_executable(test_http_connection "tests/test_http_connection.cc" kiwi "${LIBS}")
kiwi_add_executable(test_uri "tests/test_uri.cc" kiwi "${LIBS}")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
