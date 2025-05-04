file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS 
    src/data/*.cpp
    src/core/*.cpp
)

add_library(JsonParserLib STATIC ${LIB_SOURCES})

target_include_directories(JsonParserLib PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/data>
)

target_include_directories(JsonParserLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/core>
)