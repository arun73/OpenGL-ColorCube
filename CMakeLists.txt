cmake_minimum_required(VERSION 3.1)
project(OpenGL_ColorCube)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

set(SOURCE_FILES main.cpp)
add_executable(OpenGL_ColorCube ${SOURCE_FILES})

########################################################
# Linking
#########################################################
target_link_libraries(OpenGL_ColorCube ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )