# Copyright(c) 2019 spdlog authors Distributed under the MIT License (http://opensource.org/licenses/MIT)

cmake_minimum_required (VERSION 3.10)
SET (target OpenGLRenderer)
project(${target} CXX)
  ADD_DEFINITIONS (/D   GLEW_STATIC ) ## use static glew library

#use INCLUDE_DIRECTORIES IF YOU WANT THE SUB-SOURCE-TREE CAN TO ACCESS THESE FOLDERS
#INCLUDE_DIRECTORIES(${EXTERNAL_DIR}/glad/include)
# glew  // does not need add_subdirectory, glew is generated directly
set(GLEW_SOURCE ${EXTERNAL_DIR}/glew/src/glew.c
)

set(GLEW_HEADERS  ${EXTERNAL_DIR}/glew/include/
)

set(OPENGL_LIBRARY  # opengl library
opengl32.lib
)
include_directories(${GLEW_HEADERS})
add_library( glew   STATIC
	${GLEW_SOURCE} ${GLEW_HEADERS}
)


set(RENDERER_SRC
camera.h
GLSLShader.h
GLSLShader.cpp
GLSLProgram.h
GLSLProgram.cpp
vertexarrayobject.h
vertexarrayobject.cpp
vertexbuffer.cpp
vertexbuffer.h
indexbuffer.cpp
indexbuffer.h
sphere.cpp
sphere.h
light.h
light.cpp
rendererapi.h
rendererapi.cpp
renderer.h
renderer.cpp


)






add_executable(${target} OpenGLRenderer_main.cpp   ${RENDERER_SRC})
# ---------------------------------------------------------------------------------------
# Example of using pre-compiled library
# ---------------------------------------------------------------------------------------
#https://www.glfw.org/docs/3.3/build_guide.html
target_link_libraries(${target} PUBLIC
glew
 glfw 
 ${OPENGL_LIBRARY}
 loglayer)
target_include_directories(${target} PUBLIC 
${EXTERNAL_DIR}/glad/include
${EXTERNAL_DIR}/glfw/include
${EXTERNAL_DIR}/glm

)
