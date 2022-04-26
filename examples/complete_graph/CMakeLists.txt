cmake_minimum_required(VERSION 3.8)

add_executable(complete_graph main.cpp)

target_compile_features(complete_graph PRIVATE cxx_std_17)

target_link_libraries(complete_graph PRIVATE libgvizard::libgvizard)
