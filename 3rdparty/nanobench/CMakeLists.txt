add_library(nanobench INTERFACE)
target_include_directories(nanobench INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(nanobench::nanobench ALIAS nanobench)
