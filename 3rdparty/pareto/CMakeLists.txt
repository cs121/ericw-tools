add_library(pareto INTERFACE)
target_include_directories(pareto INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(pareto::pareto ALIAS pareto)
