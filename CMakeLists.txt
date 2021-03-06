cmake_minimum_required(VERSION 2.8)
project(SoftwareRasterizer)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
set(SOURCE_FILES src/main.cpp)

add_executable(SoftwareRasterizer ${SOURCE_FILES})
target_link_libraries(SoftwareRasterizer ${SDL2_LIBRARY})

# set warning levels
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4 /WX" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
    endif()
    target_link_libraries(SoftwareRasterizer ${SDL2MAIN_LIBRARY})
endif()
