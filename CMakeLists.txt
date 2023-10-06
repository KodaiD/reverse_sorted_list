CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
project(sorted_list)

message(${CMAKE_SOURCE_DIR})

set(PROJECT_VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer")
option(ENABLE_SANITIZER "enable sanitizer on debug build" ON)
if (ENABLE_SANITIZER)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-sanitize=alignment")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-sanitize-recover=address")
endif ()

file(GLOB SORTED_LIST_SRC
    "${CMAKE_SOURCE_DIR}/main.cc"
)

add_executable(sorted_list ${SORTED_LIST_SRC})

target_compile_options(sorted_list PUBLIC -O3 -Wall)
