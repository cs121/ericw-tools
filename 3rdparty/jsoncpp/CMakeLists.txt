add_library(jsoncpp_static STATIC
    src/lib_json/json_reader.cpp
    src/lib_json/json_value.cpp
    src/lib_json/json_writer.cpp
)
target_include_directories(jsoncpp_static
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set_target_properties(jsoncpp_static PROPERTIES POSITION_INDEPENDENT_CODE ON)
