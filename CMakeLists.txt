cmake_minimum_required(VERSION 3.8)

project("perfect-hash")

include("cmake/Doctest.cmake")

add_executable(perfect-hash "src/main.cpp")

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS "inc/**/*_tests.cpp")
add_executable(tests ${test_sources})
target_compile_features(tests PRIVATE cxx_std_17)
target_link_libraries(tests PRIVATE doctest)
