file(GLOB SRCS "*.c" "*.cpp" "*.cc" )
file(GLOB PUBLIC_HEADERS "*.h" "*.hpp" )

ADD_LIBRARY(toolsinspection SHARED ${SRCS} ${PUBLIC_HEADERS} )


ADD_DEFINITIONS("-DLOG_INFO")

ADD_DEFINITIONS("-DTOOLSINSPECTION_LIBRARY")

target_link_libraries(toolsinspection
    ${OpenCV_LIBS}
)
