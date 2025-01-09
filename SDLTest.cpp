#include <iostream>
#include <forward_list>
#include "wrapperlibrary/GameObjects.h"
#include "wrapperlibrary/Engine.h"
#include "wrapperlibrary/UISystem.h"
#include "wrapperlibrary/Objects.h"
#include "wrapperlibrary/Resources.h"
#include "wrapperlibrary/Helper.h"

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void test(SDL_Renderer* renderer) {
    std::forward_list<Resource*> resources;
    resources.push_front(new ResImage("i1", "resources/images/wall.png", SDL_BLENDMODE_NONE, renderer));
    resources.push_front(new ResFont("f1", "resources/fonts/OpenSans-Regular.ttf", 20));

    for (auto resource: resources) {
        std::cout << "resource.id = " << resource->getId() << std::endl;
    }

    for (auto resource: resources) {
        delete resource;
    }
}

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) { throw std::runtime_error(SDL_GetError()); }
    if (TTF_Init() != 0) { throw std::runtime_error(TTF_GetError()); }

    SDL_Window* window = SDL_CreateWindow("SDLTest",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) { throw std::runtime_error(SDL_GetError()); }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) { throw std::runtime_error(SDL_GetError()); }

    test(renderer);

    Engine engine("SDLTest", {
        .window = window,
        .renderer = renderer,
        .windowRect  = { .x=SDL_WINDOWPOS_CENTERED, .y=SDL_WINDOWPOS_CENTERED, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT },
        .windowFlags = SDL_WINDOW_SHOWN
    });

    UIForm form1 = {"form1", true, true, {
        { .type=label,  .title="TEST LABEL #1",  .rect={ .x=100, .y=20, .w=100, .h=30} },
        { .type=button, .title="TEST BUTTON #1", .rect={ .x=250, .y=20, .w=100, .h=30} }
    }};

    UIForm form2 = {"form2", true, true, {
        { .type=label,  .title="TEST LABEL #2",  .rect={ .x=100, .y=60, .w=100, .h=30} },
        { .type=button, .title="TEST BUTTON #2", .rect={ .x=250, .y=60, .w=100, .h=30} }
    }};

    engine.addForm(form1.title, &form1);
    engine.addForm(form2.title, &form2);

    engine.loadResources(Helper::absolutePath("resources/resources.toml"));

    int result = engine.run();

    return result;
}
