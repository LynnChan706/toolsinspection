#In order to complete,Please read README.md first if you never use cmake previously

cmake_minimum_required(VERSION 2.8.7)
project (toolsinspect)

# ---[ Dependencies
include(cmake/Dependencies.cmake)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

if(MSVC)
   if(${CMAKE_BUILD_TYPE} STREQUAL "Debug" )
        message("Build model : Debug ")
        add_definitions(/MDd)
        set(CMAKE_DEBUG_POSTFIX "d")
    else()
        message("Build model : Release ")
        add_definitions(/MD)
   endif()
endif(MSVC)

add_subdirectory(src)
add_subdirectory(test)
