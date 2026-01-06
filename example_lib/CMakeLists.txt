# Example of the INTERFACE library
set(app_target example)
add_library(${app_target} INTERFACE)

target_include_directories(${app_target}
    INTERFACE
    .
)

target_sources(${app_target}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Example.cpp
)

# Example how to use external dependency
# cmake_policy(SET CMP0167 NEW)
find_package(Boost 1.83.0 REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost libriary was found")
    target_include_directories(${app_target} 
                               INTERFACE
                               ${Boost_INCLUDE_DIRS})
    target_link_libraries(${app_target} INTERFACE ${Boost_LIBRARIES})
else()
    message(STATUS "Boost libriary was not found")
endif()
