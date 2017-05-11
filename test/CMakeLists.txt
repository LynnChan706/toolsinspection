file(GLOB SRCS "*.c" "*.cpp" "*.cc" )
file(GLOB PUBLIC_HEADERS "*.h" "*.hpp" )

set(_LINKER_LIBS toolsinspection ${_LINKER_LIBS})

ADD_EXECUTABLE(inspectiontest inspectiontest.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    )

target_link_libraries(inspectiontest
    ${_LINKER_LIBS}
    )
