#pragma once

#ifndef ENGINE_H_
#define ENGINE_H_

#include <string>
#include <iostream>
#include <unordered_map>
#include <forward_list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "UISystem.h"
#include "Objects.h"

const char* DEFAULT_FONT = "OpenSans-Regular.ttf";
const int DEFAULT_FONT_SIZE = 20;
const int TARGET_FPS = 60;
constexpr int FRAME_DELAY = 1000 / TARGET_FPS;

class Engine {
private:
    UIRenderingContext renderingContext;
    std::unordered_map<std::string, UIForm*> forms;
    std::forward_list<GameObject*> objects;
    const std::string title;
    bool SDL_initialized = false;
    bool TTF_initialized = false;
public:
    Engine(const std::string title, UIRenderingContext renderingContext): renderingContext(renderingContext), title(title) {}
    ~Engine() {
        // std::cout << "CEngine::~CEngine() started" << std::endl;
        if (renderingContext.defaultFont) { TTF_CloseFont(renderingContext.defaultFont); }
        if (renderingContext.renderer) { SDL_DestroyRenderer(renderingContext.renderer); }
        if (renderingContext.window) { SDL_DestroyWindow(renderingContext.window); }
        if (TTF_initialized) { TTF_Quit(); }
        if (SDL_initialized) { SDL_Quit(); }
        // std::cout << "CEngine::~CEngine() ended" << std::endl;
    }
    void addForm(std::string formName, UIForm* form) { forms.insert({formName, form}); }
    std::unordered_map<std::string, UIForm*>* getForms() { return &forms; }

    void addObject(GameObject* object) { objects.push_front(object); }
    std::forward_list<GameObject*>* getObjects() { return &objects; }

    void renderForms() {
        for (auto& [name, form]: forms) {
            if (form->isActive() && form->isVisible()) {
                form->render(renderingContext);
            }
        }
    }

    void renderObjects() {
        for (GameObject* object: objects) {
            if (object->isActive()) {
                object->render(renderingContext.renderer);
            }
        }
    }

    int run() {

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        SDL_initialized = true;

        if (TTF_Init() != 0) {
            std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
            return 1;
        }
        TTF_initialized = true;

        renderingContext.window = SDL_CreateWindow(
            title.c_str(),
            renderingContext.windowRect.x,
            renderingContext.windowRect.y,
            renderingContext.windowRect.w,
            renderingContext.windowRect.h,
            renderingContext.windowFlags);
        if (!renderingContext.window) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        renderingContext.renderer = SDL_CreateRenderer(renderingContext.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderingContext.renderer) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        renderingContext.defaultFont = TTF_OpenFont(DEFAULT_FONT, DEFAULT_FONT_SIZE);
        if (!renderingContext.defaultFont) {
            std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
            return 1;
        }

        SDL_Event event;
        bool quit = false;
        bool isFullscreen = false;

        while (!quit) {
            Uint32 frameStart = SDL_GetTicks();
            int dX=0, dY=0;
            while (SDL_PollEvent(&event)) {
                quit = (event.type == SDL_QUIT);
                bool KEY_DOW = (event.key.type == SDL_KEYDOWN);
                bool KEY_UP  = (event.key.type == SDL_KEYUP);
                bool KEYBOARD_EVENT = KEY_DOW || KEY_UP;
                if (KEYBOARD_EVENT) {
                    bool CTRL_DOWN = (event.key.keysym.mod & KMOD_LCTRL)
                        || (event.key.keysym.mod & KMOD_RCTRL)
                        || (event.key.keysym.mod & KMOD_CTRL);
                    bool ARROW_KEY = (event.key.keysym.sym == SDLK_RIGHT)
                        || (event.key.keysym.sym == SDLK_LEFT)
                        || (event.key.keysym.sym == SDLK_DOWN)
                        || (event.key.keysym.sym == SDLK_UP);
                    if (KEY_DOW && CTRL_DOWN && event.key.keysym.sym == SDLK_q) {
                        quit = true;
                    } else if (KEY_DOW && CTRL_DOWN && event.key.keysym.sym == SDLK_f) {
                        SDL_SetWindowFullscreen(renderingContext.window, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                        isFullscreen = !isFullscreen;
                    } else if (KEY_DOW && ARROW_KEY) {
                        switch (event.key.keysym.sym) {
                            SDLK_RIGHT: dX =  1; break;
                            SDLK_LEFT:  dX = -1; break;
                            SDLK_DOWN:  dY =  1; break;
                            SDLK_UP:    dY = -1; break;
                        }
                    }
                }
            }

            SDL_SetRenderDrawColor(renderingContext.renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderingContext.renderer);

            renderForms();
            renderObjects();

            SDL_RenderPresent(renderingContext.renderer);

            Uint32 frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < FRAME_DELAY) {
                SDL_Delay(FRAME_DELAY - frameTime);
            }
        }

        std::cout << "****************" << std::endl;
        std::cout << "*** Finished ***" << std::endl;
        std::cout << "****************" << std::endl;

        return 0;
    }

};

#endif /* ENGINE_H_ */
