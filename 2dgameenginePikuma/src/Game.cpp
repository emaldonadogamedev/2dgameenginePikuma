#include "Game.h"

#include <SDL.h>

#include <iostream>

Game::Game()
    :isRunning(false)
{
}

Game::~Game()
{
}

void Game::Initialize()
{
    const int sdlInitResult = SDL_Init(SDL_INIT_EVERYTHING);
    if(sdlInitResult != 0)
    {
        std::cerr<<"Error Initializing SDL";
        return;
    }

    SDL_DisplayMode sdlDisplayMode;
    SDL_GetCurrentDisplayMode(0, &sdlDisplayMode);
    windowWidth = sdlDisplayMode.w;
    windowHeight = sdlDisplayMode.h;

    sdlWindow = SDL_CreateWindow(
        "2D Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth, 
        windowHeight,
        SDL_WINDOW_BORDERLESS);
    if(sdlWindow == nullptr)
    {
        std::cerr<<"Error creating an SDL window";
        return;
    }

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
    if(sdlRenderer == nullptr)
    {
        std::cerr<<"Error creating an SDL renderer";
        return;
    }

    isRunning = true;
}

void Game::Run()
{
    while(isRunning)
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
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if(sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                    isRunning = false;
                break;

            default:
                break;
        }
    }
}

void Game::Update()
{
    //TODO: Update game objects
}

void Game::Render()
{
    SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(sdlRenderer);

    // TODO: Render all Game Objects

    SDL_RenderPresent(sdlRenderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}