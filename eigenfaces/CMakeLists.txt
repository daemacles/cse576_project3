cmake_minimum_required (VERSION 2.6)

project (eigenfaces)
set (CMAKE_BUILD_TYPE Debug)

include_directories ("${PROJECT_SOURCE_DIR}/code")

file(GLOB eigenfaces_src "${PROJECT_SOURCE_DIR}/code/*.cpp")
add_executable (main ${eigenfaces_src})

if( MSVC )
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
else()
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7 )
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
    target_link_libraries (main m)
endif()

