#ifndef GAME_H
#define GAME_H

#include <memory>

// SDL Forward declarations
// instead of adding #include <SDL2/SDL.h>
typedef struct SDL_Window SDL_Window;
struct SDL_Renderer;
typedef struct SDL_Renderer SDL_Renderer;

const int FRAMES_PER_SECOND = 60;
const int MS_PER_FRAME = 1000 / FRAMES_PER_SECOND;

class Registry;

class Game
{
    public:
        Game();
        ~Game();

        void Initialize();
        void Setup();
        void Run();

        void ProcessInput();
        void Update();
        void Render();

        void Destroy();

    private:
        bool m_isRunning;

        int m_msPreviousFrame;
        bool m_isCappingFPS;
        float m_deltaTime;

        int m_windowWidth;
        int m_windowHeight;

        SDL_Window* m_sdlWindow;
        SDL_Renderer* m_sdlRenderer;

        std::unique_ptr<Registry> m_registry;
};

#endif