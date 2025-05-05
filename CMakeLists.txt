cmake_minimum_required(VERSION 3.10.0)
project(vsc-cpp-cmake-template-project VERSION 0.1.0 LANGUAGES C CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# OPTIONS
option(SOME_TEST_OPITON "Some test option to play with" On)

add_subdirectory(example EXCLUDE_FROM_ALL)

# region TARGET template
set(APP_TARGET example-app)
add_executable(${APP_TARGET})
target_sources(${APP_TARGET} 
                PRIVATE
                ${PROJECT_SOURCE_DIR}/example-app.cpp)
target_compile_features(${APP_TARGET} PRIVATE cxx_std_11)
target_compile_options(${APP_TARGET} PRIVATE -Wall -Wextra -Werror)
target_include_directories(${APP_TARGET} 
                           PRIVATE
                           ${PROJECT_BINARY_DIR}/include
                           ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${APP_TARGET} PRIVATE example)
# endregion TARGET template

# generate config file
configure_file(include/Config.h.in include/Config.h)
