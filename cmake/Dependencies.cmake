set(_LINKER_LIBS "")

# ---[ OpenCV
find_package(OpenCV QUIET COMPONENTS core highgui imgproc calib3d)
if(NOT OpenCV_FOUND) # if not OpenCV 3.x, then imgcodecs are not found
find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc calib3d)
endif()
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})
list(APPEND _LINKER_LIBS ${OpenCV_LIBS})

# message("opencv list:" ${_LINKER_LIBS})
message(STATUS "OpenCV found (${OpenCV_CONFIG_PATH})")
add_definitions(-DUSE_OPENCV)

