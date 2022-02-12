cmake_minimum_required(VERSION 3.8)

file(GLOB test_sources "*.cpp")

add_executable(tests ${test_sources})

target_compile_features(tests PRIVATE cxx_std_17)

target_compile_options(tests PRIVATE -g -O0 -Wall -Wextra -Wpedantic)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(tests PRIVATE
                      Catch2::Catch2
                      Catch2::Catch2WithMain
                      libgvizard::libgvizard)

# -- coverage

if(FALSE)

target_link_libraries(tests PRIVATE gcov)

set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/RunAdder.dir)
message("-- Source files will be at: ${CMAKE_SOURCE_DIR}")
message("-- Object files will be output to: ${OBJECT_DIR}")

target_compile_options(tests PRIVATE
    -fprofile-arcs -ftest-coverage --coverage
    -fno-inline -fno-inline-small-functions -fno-default-inline)

add_custom_target(gcoverage
  COMMAND mkdir -p coverage
  COMMAND ${CMAKE_MAKE_PROGRAM} tests
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET gcoverage
  COMMAND echo "=================== GCOV ===================="
  COMMAND gcov -b ${CMAKE_SOURCE_DIR}/include/**.hpp -o ${OBJECT_DIR}
    | grep -A 5 ".hpp" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
)

add_dependencies(gcoverage tests)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

add_custom_target(scrub
  COMMAND ${CMAKE_MAKE_PROGRAM} clean
  COMMAND rm -f ${OBJECT_DIR}/*.gcno
  COMMAND rm -f ${OBJECT_DIR}/*.gcda
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

endif()

include(CTest)
include(Catch)

catch_discover_tests(tests)
