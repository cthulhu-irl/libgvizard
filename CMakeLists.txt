cmake_minimum_required(VERSION 3.8)

project(libgvizard CXX)

set(CMAKE_CXX_STANDARD, 17)

include("cmake/setup_vcpkg.cmake")

option(LIBGVIZARD_OPT_GENERATE_DOCS "Generate documentation"  FALSE)
option(LIBGVIZARD_OPT_BUILD_TEST "Build and perform tests" TRUE)
option(LIBGVIZARD_OPT_INSTALL "Generate and install libgvizard target" TRUE)

# Add the cmake folder so the FindSphinx module is found
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(LIBGVIZARD_PUBLIC_HEADER_DIR "${PROJECT_SOURCE_DIR}/include/")

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# -- external libraries

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE EnTT::EnTT)

find_package(range-v3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE range-v3
                                                range-v3-meta
                                                range-v3::meta
                                                range-v3-concepts)

find_package(magic_enum CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE magic_enum::magic_enum)

# --

if(LIBGVIZARD_OPT_GENERATE_DOCS)
  add_subdirectory("docs")
endif()

if(LIBGVIZARD_OPT_BUILD_TEST)
  enable_testing()
  add_subdirectory("tests")
endif()

if(LIBGVIZARD_OPT_INSTALL)
endif()

add_subdirectory("examples")
