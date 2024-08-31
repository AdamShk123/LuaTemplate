#include <lua.hpp>
#include "../include/game.hpp"

namespace LuaTemplate {

Game::Game()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::string error = SDL_GetError();
        throw std::runtime_error(error.c_str());
    }

    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_FULLSCREEN);
    m_window = SDL_CreateWindow("Lua", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, window_flags);
    if(!m_window)
    {
        std::string error = SDL_GetError();
        throw std::runtime_error(error.c_str());
    }

    auto flags = (IMG_InitFlags)(IMG_INIT_JPG | IMG_INIT_PNG);
    auto result = IMG_Init(flags);
    if(result != flags)
    {
        std::string error = IMG_GetError();
        throw std::runtime_error(error.c_str());
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if(!m_renderer)
    {
        std::string error = SDL_GetError();
        throw std::runtime_error(error.c_str());
    }
}

Game::~Game()
{
    IMG_Quit();

    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    SDL_Quit();
}

std::optional<Texture> Game::loadTexture(const std::string& path)
{
    Texture texture {};

    texture.data = IMG_LoadTexture(m_renderer, path.c_str());
    fmt::println("{}", SDL_GetError());
    if(texture.data)
    {
        SDL_QueryTexture(texture.data, &texture.format, nullptr, &texture.w, &texture.h);
        return texture;
    }

    return std::nullopt;
}

int add_two(lua_State *lua)
{
    int a = lua_tointeger(lua, 1);
    int b = lua_tointeger(lua, 2);
    fmt::println("a: {}, b: {}, sum: {}", a, b, a + b);
    lua_pushinteger(lua, a + b);
    return 1;
};

int sum(int a, int b)
{
    return a + b;
}

void Game::run()
{
    // Lua C API

//    lua_State *lua = luaL_newstate();
//    luaL_openlibs(lua);
//
//    // load Lua script
//    int result = luaL_dofile(lua, "src/main.lua");
//    if(result == LUA_OK)
//    {
//        fmt::println("script loaded successfully\n");
//    }
//    else
//    {
//        fmt::println("failed to load script\n");
//        return;
//    }
//
//    // read an integer global variable
//    lua_getglobal(lua, "a");
//    if(lua_isinteger(lua, -1))
//    {
//        int a = lua_tointeger(lua, -1);
//        fmt::println("a: {}\n", a);
//    }
//
//    // read a table global variable
//    lua_getglobal(lua, "entity");
//    if(lua_istable(lua, -1))
//    {
//        lua_pushstring(lua, "name");
//        lua_gettable(lua, -2);
//        std::string name = lua_tostring(lua, -1);
//        fmt::println("name: {}", name);
//        lua_pop(lua, 1);
//
//        lua_pushstring(lua, "id");
//        lua_gettable(lua, -2);
//        std::string id = lua_tostring(lua, -1);
//        fmt::println("id: {}\n", id);
//        lua_pop(lua, 1);
//    }
//
//    // call lua functions, pass arguments to it, and get the return value
//    lua_getglobal(lua, "add_two");
//    if(lua_isfunction(lua, -1))
//    {
//        int a = 3;
//        int b = 5;
//        int sum;
//
//        lua_pushinteger(lua, a);
//        lua_pushinteger(lua, b);
//        lua_pcall(lua, 2, 1, 0);
//
//        sum = lua_tointeger(lua, -1);
//        lua_pop(lua, 1);
//        fmt::println("sum: {}\n", sum);
//    }
//
//    // register C++ function and call it from Lua
//    lua_register(lua, "add_two_cpp", &add_two);
//    result = luaL_dostring(lua, "return add_two_cpp(3,5);");
//    if(result == LUA_OK)
//    {
//        fmt::println("sum: {}\n", lua_tointeger(lua, -1));
//    }
//    lua_close(lua);

    // Sol Library API

//    sol::state lua;
//    lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::io, sol::lib::math, sol::lib::table, sol::lib::coroutine);
//
//    // load Lua script
//    try
//    {
//        auto result = lua.safe_script_file("src/main.lua");
//        fmt::println("script loaded successfully\n");
//    }
//    catch(const sol::error& e)
//    {
//        fmt::println("{}\n", e.what());
//        return;
//    }
//
//    // read an integer global variable
//    std::optional<int> a = lua["a"];
//    if(a)
//    {
//        fmt::println("a: {}\n", a.value());
//    }
//
//    // call lua functions, pass arguments to it, and get the return value
//    std::optional<sol::function> add_two = lua["add_two"];
//    if(add_two)
//    {
//        int a = 3;
//        int b = 5;
//
//        int sum = add_two.value()(a, b);
//        fmt::println("sum: {}\n", sum);
//    }
//
//    // read a table global variable
//    std::optional<sol::table> entities = lua["entities"];
//    if(entities)
//    {
//        for(auto entry : entities.value())
//        {
//            sol::table entity = entry.second.as<sol::table>();
//
//            for(auto property : entity)
//            {
//                sol::object key = property.first;
//                sol::object value = property.second;
//
//                std::string sKey = key.as<std::string>();
//                if(sKey == "name")
//                {
//                    std::string val = value.as<std::string>();
//                    fmt::println("name: {}", val);
//                }
//                else if(sKey == "id")
//                {
//                    int val = value.as<int>();
//                    fmt::println("id: {}", val);
//                }
//                else if(sKey == "texture")
//                {
//                    std::string val = value.as<std::string>();
//                    fmt::println("texture: {}", val);
//                }
//            }
//            fmt::println("");
//        }
//    }
//
//    lua["sum_cpp"] = sum;
//    lua.script("result = sum_cpp(3,5)");
//    fmt::println("sum: {}", lua["result"].get<int>());

    // Game Engine-Like Example

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::coroutine, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::io);

    sol::table entity;

    try
    {
        entity = lua.safe_script_file("src/entity.lua");
    }
    catch(const sol::error& e)
    {
        fmt::println("{}", e.what());
        return;
    }

    entity["init"](entity);

    std::string imagePath = "textures/awesomeface.png";
    std::optional<Texture> t0 = loadTexture(imagePath);

    SDL_Event e;

    bool quit = false;

    while(!quit)
    {
        uint32_t start_time = SDL_GetTicks();

        while(SDL_PollEvent(&e) != 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_WINDOWEVENT:
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF); // set renderer color to white
        SDL_RenderClear(m_renderer); // clear screen

        entity["process"](entity, (int)m_delta);
        sol::table props = entity["props"];
        sol::object x = props["x"];
        sol::object y = props["y"];

        SDL_Rect src_rect = {0, 0, t0->w, t0->h};
        SDL_Rect dst_rect = {(int)x.as<float>(), (int)y.as<float>(), t0->w, t0->h};
        SDL_RenderCopy(m_renderer, t0->data, &src_rect, &dst_rect);

        SDL_RenderPresent(m_renderer);

        uint32_t stop_time = SDL_GetTicks();

        m_delta = (float)(stop_time - start_time);

//        fmt::println("fps: {}", 1000 / m_delta);
    }
}

}


