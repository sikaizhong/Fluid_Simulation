SET(target loglayer)
add_library(${target}  loglayer.cpp)
target_include_directories(${target} PUBLIC ../logwrapper)