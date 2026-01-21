cmake_minimum_required(VERSION 3.10.0)

if(DEFINED ENV{VCPKG_ROOT})
  message(STATUS "VCPKG_ROOT is set to: $ENV{VCPKG_ROOT}")
else()
  message(FATAL_ERROR "Environment variable VCPKG_ROOT is not set. Please set it to the root of your vcpkg installation.")
endif()

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
else()
  message(STATUS "Using Vcpkg toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
endif()

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
option(SOME_TEST_OPITON "Some test option to play with" ON)

# If you want target to be excluded from the "all" target 
# add_subdirectory(dir_name EXCLUDE_FROM_ALL)
add_subdirectory(example_lib EXCLUDE_FROM_ALL)

# FetchContent is a CMake module that allows you to download and include external content (like libraries)
# directly into your CMake build. It simplifies the process of managing dependencies by automating
# the download, configuration, and inclusion of external projects.
# include(FetchContent)
# set(FMT_INSTALL OFF CACHE BOOL "Disable fmt install" FORCE)
# # Sets the FMT_MODULE cache variable to ON, forcing it to be a boolean type.
# # CACHE: Defines this as a cache variable, which is stored in CMakeCache.txt and persists across CMake runs,
# #        allowing users to modify it via cmake-gui or command line without editing the CMakeLists.txt.
# # FORCE: Overrides any existing value in the cache, ensuring this setting takes precedence even if the variable
# #        was previously set to something else.
# # set(FMT_MODULE ON CACHE BOOL "Enable module" FORCE)
# FetchContent_Declare(
#   fmt
#   GIT_REPOSITORY https://github.com/fmtlib/fmt
#   GIT_TAG 11.2.0)
# FetchContent_MakeAvailable(fmt)

# region example_app
set(app_target example_app)
add_executable(${app_target})
target_sources(${app_target} 
                PRIVATE
                ${PROJECT_SOURCE_DIR}/src/example_app_main.cpp)
target_compile_features(${app_target} PRIVATE cxx_std_11)
# -Wall:            The -Wall flag (short for "Warnings: All") is a compiler option used with 
#                   GCC and Clang to enable a broad set of common warnings. It helps catch potential issues 
#                   like unused variables, implicit type conversions, missing return values, and other common 
#                   programming errors that could lead to bugs or undefined behavior.
# -Wextra:          Enables additional compiler warnings (GCC/Clang) beyond -Wall. 
#                   It helps catch more subtle issues (unused parameters, sign comparisons, etc.).
# -Werror:          Treats all warnings as errors, causing the build to fail on any warning.
# -pedantic:        Enforces strict adherence to the C/C++ standards, issuing warnings for non-standard code.
# -pedantic-errors: Like -pedantic, but treats violations as errors.
target_compile_options(${app_target} PRIVATE -Wall -Wextra -Werror)
target_include_directories(${app_target} 
                           PRIVATE
                           ${PROJECT_BINARY_DIR}/include
                           ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${app_target} PRIVATE example)
# generate config file
configure_file(include/Config.h.in include/Config.h)
install(TARGETS ${app_target} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/install/lib/${app_target})
# endregion example_app

# Example of translation unit preprocessing
# Add a custom target to generate preprocessed output
add_custom_target(preprocess_example_app
  COMMAND ${CMAKE_CXX_COMPILER} -E 
    -I${PROJECT_BINARY_DIR}/include
    -I${PROJECT_SOURCE_DIR}/include
    -I${PROJECT_SOURCE_DIR}/example
    ${PROJECT_SOURCE_DIR}/src/example_app_main.cpp
    > ${PROJECT_BINARY_DIR}/example_app_main.ii
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  COMMENT "Generating preprocessed translation unit for example_app_main.cpp"
)
