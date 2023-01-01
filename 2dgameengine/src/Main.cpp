#include <iostream>

#include <SDL2/SDL.h> // main SDL features
#include <SDL2/SDL_image.h> // working with images
#include <SDL2/SDL_ttf.h> // for dealing with true-type fonts
#include <SDL2/SDL_mixer.h> // for dealing with audio

#include <glm/glm.hpp> // base glm file for the cool math

#include <imgui/imgui.h> // UI and debug UI

#include <sol/sol.hpp> // for binding Lua to C++

int main()
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    SDL_Init(SDL_INIT_EVERYTHING);

    std::cout << "Hello, world!" << std::endl;

    return 0;
}
