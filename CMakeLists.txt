cmake_minimum_required(VERSION 3.20.2)
project(ceres VERSION 0.0.1 LANGUAGES CXX)


# Look in build/cmake for modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# CMake modules
include(custom-utils)


# Main executable
add_executable(ceres src/ceres/main.cpp)

# Compiler options
target_compile_features(ceres PRIVATE cxx_std_17)
target_enable_all_warnings(ceres)

# Set output directiories
set_target_properties(ceres PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release)
set_target_properties(ceres PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/debug)
set_target_properties(ceres PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/bin/releasewdebug)

# Required packages
find_package(SDL2 REQUIRED)

# Link packages
target_link_libraries(ceres PRIVATE SDL2::SDL2)

# Windows specific
if (WIN32)
	# Link SDL2main on windows to allow for a portable main()
	target_compile_definitions(ceres PRIVATE SDL_MAIN_HANDLED)
	target_link_libraries(ceres PRIVATE SDL2::SDL2main)
endif()
