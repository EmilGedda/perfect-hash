include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    projdoctest
    PREFIX ${CMAKE_BINARY_DIR}/doctest
    GIT_REPOSITORY https://github.com/onqtam/doctest.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(projdoctest source_dir)

set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")
add_library(doctest INTERFACE)

add_dependencies(doctest projdoctest)
target_compile_features(doctest INTERFACE cxx_std_17)
target_include_directories(doctest INTERFACE ${DOCTEST_INCLUDE_DIR})