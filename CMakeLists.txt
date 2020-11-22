cmake_minimum_required (VERSION 3.10)

#use c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project (Fluid_Simulation)
# Compile options
include(cmake/CompileOptions.cmake)
if ((CMAKE_VERSION VERSION_EQUAL 3.3) OR (CMAKE_VERSION VERSION_GREATER 3.3))
    cmake_policy(SET CMP0063 NEW)
endif()
#ouput
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

# Project modules
set(BUILD_GTEST ON CACHE BOOL "" FORCE) #If FORCE is used here, we can not check/uncheck this option in cmake gui;
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#add_subdirectory(external/googletest EXCLUDE_FROM_ALL)
if(BUILD_GTEST)
add_subdirectory(external/googletest)
endif()
INCLUDE_DIRECTORIES (src )
INCLUDE_DIRECTORIES (src/core)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/external/spdlog/include)
SOURCE_GROUP (core REGULAR_EXPRESSION src/core/.*) # all files in core folder will be shown in  a vs folder called core;


# I can use #ifdef PBRT_FLOAT_AS_DOUBLE 
#             typedef double Float;
#           #else 
#             typedef float Float;
# In my code.
# Ungrouped Entries contain marcos with unique prefix;
#If there are multiple marcos with the same prefix, Ungrouped Entries will be replaced by the prefix;
# Check cmake file of spdlog
# OPTION VS SET: option indicates ppl that we can change values while set does not
#Although we can remove the parameter, FORCE, in set to acchive the same consequence;
OPTION(FS_FLOAT_AS_DOUBLE "Use 64-bit floats" OFF)
IF (FS_FLOAT_AS_DOUBLE)
  ADD_DEFINITIONS ( -D FS_FLOAT_AS_DOUBLE )
ENDIF()

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



#We have to generate lib for fluid_simulation
#since we want to link it to unit test;
add_library(Fluid_Simulation_Lib ${FS_CORE_HEADERS} ${FS_CORE_SOURCE})
add_executable(Fluid_Simulation  main.cpp)
target_link_libraries(Fluid_Simulation
Fluid_Simulation_Lib
)

#In spdlog, there is an option called SPDLOG_BUILD_ALL
#If I want to activitate it from the default value
#Put this line 
#This line must be put before the add_subdirectory command;
#SET(SPDLOG_BUILD_ALL ON CACHE BOOL "Use log" FORCE )
#If we do not need to build the target and consider it as a header-only file
# we can use EXCLUDE_FROM_ALL.
add_subdirectory(${PROJECT_SOURCE_DIR}/external/spdlog EXCLUDE_FROM_ALL)
if(BUILD_GTEST)
add_subdirectory(src/test)
endif()
