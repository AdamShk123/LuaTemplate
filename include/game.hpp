#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include <fmt/core.h>
#include <fmt/color.h>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <string>
#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <cstdint>
#include <ranges>
#include <vector>
#include <optional>

namespace LuaTemplate {

struct Texture {
    SDL_Texture *data;
    uint32_t format;
    int w;
    int h;
};

class Game
{
private:
    float m_delta = 0.0f;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
//    lua_State *m_lua;

public:
    Game();
    ~Game();

    void run();
    std::optional<Texture> loadTexture(const std::string& path);
};

}

#endif

