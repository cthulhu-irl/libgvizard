cmake_minimum_required(VERSION 3.8)

add_executable(simple_dot_generator main.cpp)

target_compile_features(simple_dot_generator PRIVATE cxx_std_17)

target_link_libraries(simple_dot_generator PRIVATE libgvizard::libgvizard)
