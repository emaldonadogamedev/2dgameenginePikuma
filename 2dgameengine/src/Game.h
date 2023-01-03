#ifndef GAME_H
#define GAME_H

// SDL Forward declarations
// instead of adding #include <SDL2/SDL.h>
typedef struct SDL_Window SDL_Window;
struct SDL_Renderer;
typedef struct SDL_Renderer SDL_Renderer;

class Game
{
    private:
        bool isRunning;

        int windowWidth;
        int windowHeight;

        SDL_Window* sdlWindow;
        SDL_Renderer* sdlRenderer;

    public:
        Game();
        ~Game();

        void Initialize();
        void Run();

        void ProcessInput();
        void Update();
        void Render();

        void Destroy();
};

#endif