find_package(fmt CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(lua CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp game.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt SDL2::SDL2 SDL2_image::SDL2_image ${LUA_LIBRARIES})