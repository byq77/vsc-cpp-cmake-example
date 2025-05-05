# Example of the INTERFACE library
add_library(example INTERFACE)

target_include_directories(example
    INTERFACE
    .
)

target_sources(example
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Example.cpp
)

# Example how to use external dependency
cmake_policy(SET CMP0167 NEW)
find_package(Boost 1.83.0 REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost libriary was found")
    target_include_directories(example 
                               INTERFACE
                               ${Boost_INCLUDE_DIRS})
    target_link_libraries(example INTERFACE ${Boost_LIBRARIES})
else()
    message(STATUS "Boost libriary was not found")
endif()
