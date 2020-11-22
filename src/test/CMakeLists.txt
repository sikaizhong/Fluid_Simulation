# Target name
set(target unit_tests)
if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MT> #--|
    )
endif()
# Includes
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${EXTERNAL_DIR}/googletest/googlemock/include
    ${EXTERNAL_DIR}/googletest/googletest/include)

# Sources
file(GLOB sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build executable
add_executable(${target}
    ${sources})
target_link_libraries(${target}
PRIVATE
Fluid_Simulation_Lib
gtest
)