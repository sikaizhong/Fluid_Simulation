cmake_minimum_required (VERSION 3.10)

#use c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project (Fluid_Simulation)
# Annoying compiler-specific details
IF(MSVC)
  ADD_DEFINITIONS (/D  _CRT_SECURE_NO_WARNINGS)  ## add macro
  ADD_DEFINITIONS (/D  _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING )
ENDIF()

#ouput
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

INCLUDE_DIRECTORIES (src )
INCLUDE_DIRECTORIES (src/core)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/external/spdlog/include)

SET ( FS_CORE_HEADERS
src/core/core.h
src/loglayer.h
)
SET ( FS_CORE_SOURCE
src/core/core.cpp
src/loglayer.cpp

)

FILE ( GLOB FS_SOURCE
  src/ext/*
  
  )


SOURCE_GROUP (core REGULAR_EXPRESSION src/core/.*) # all files in core folder will be shown in  a vs folder called core;
add_executable(Fluid_Simulation  main.cpp   ${FS_CORE_HEADERS} ${FS_CORE_SOURCE})
#In spdlog, there is an option called SPDLOG_BUILD_ALL
#If I want to activitate it from the default value
#Put this line 
#This line must be put before the add_subdirectory command;
#SET(SPDLOG_BUILD_ALL ON CACHE BOOL "Use log" FORCE )
add_subdirectory(${PROJECT_SOURCE_DIR}/external/spdlog)#header only
