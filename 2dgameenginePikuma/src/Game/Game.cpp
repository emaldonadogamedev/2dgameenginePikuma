#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>

#include "../ECS/ECS.h"

#include "../Logger/Logger.h"

Game::Game()
    :m_isRunning(false)
    ,m_msPreviousFrame(0)
    ,m_isCappingFPS(false)
    ,m_deltaTime(0.f)
    ,m_windowWidth(800)
    ,m_windowHeight(600)
    ,m_sdlWindow(nullptr)
    ,m_sdlRenderer(nullptr)
    ,m_registry(std::make_unique<Registry>())
{
    Logger::Log("Game class constructor called");
}

Game::~Game()
{
    Logger::Log("Game class destructor called");
}

void Game::Initialize()
{
    const int sdlInitResult = SDL_Init(SDL_INIT_EVERYTHING);
    if(sdlInitResult != 0)
    {
        Logger::Error("Error Initializing SDL");
        return;
    }

    SDL_DisplayMode sdlDisplayMode;
    SDL_GetCurrentDisplayMode(0, &sdlDisplayMode);
    m_windowWidth = sdlDisplayMode.w;
    m_windowHeight = sdlDisplayMode.h;

    m_sdlWindow = SDL_CreateWindow(
        "2D Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_windowWidth, 
        m_windowHeight,
        SDL_WINDOW_BORDERLESS);
    if(m_sdlWindow == nullptr)
    {
        Logger::Error("Error creating an SDL window");
        return;
    }

    m_sdlRenderer = SDL_CreateRenderer(
        m_sdlWindow, 
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_sdlRenderer == nullptr)
    {
        Logger::Error("Error creating an SDL renderer");
        return;
    }

    // for real full screen
    SDL_SetWindowFullscreen(m_sdlWindow, SDL_WINDOW_FULLSCREEN);

    m_isRunning = true;
}

void Game::Setup()
{
    Entity tank = m_registry->CreateEntity();
    Entity truck = m_registry->CreateEntity();
}

void Game::Run()
{
    Setup();
    
    while(m_isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput()
{
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent))
    {
        switch(sdlEvent.type)
        {
            case SDL_QUIT: //if user closes window(X button)
                m_isRunning = false;
                break;

            case SDL_KEYDOWN:
                if(sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                    m_isRunning = false;
                break;

            default:
                break;
        }
    }
}

void Game::Update()
{
    if(m_isCappingFPS)
    {
        int timeToWait = MS_PER_FRAME - (SDL_GetTicks() - m_msPreviousFrame);
    
        if(timeToWait > 0 && timeToWait <= MS_PER_FRAME)
        {    
            SDL_Delay(timeToWait);
        }
    }

    m_deltaTime = (SDL_GetTicks() - m_msPreviousFrame)/1000.f;

    // store current frame time
    m_msPreviousFrame = SDL_GetTicks();
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_sdlRenderer, 21, 21, 21, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_sdlRenderer);

    // TODO: render game objects

    SDL_RenderPresent(m_sdlRenderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(m_sdlRenderer);
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}