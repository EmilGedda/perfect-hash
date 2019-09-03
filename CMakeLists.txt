cmake_minimum_required(VERSION 3.8)

project("perfect-hash")

include("cmake/Doctest.cmake")

add_executable(perfect-hash "src/main.cpp")
add_executable(tests "inc/perfect-hash/unordered_map_tests.cpp")
target_compile_features(tests PRIVATE cxx_std_17)
target_link_libraries(tests PRIVATE doctest)
