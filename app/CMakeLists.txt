file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(JsonParserApp ${APP_SOURCES})

target_include_directories(JsonParserApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(JsonParserApp PRIVATE JsonParserLib)