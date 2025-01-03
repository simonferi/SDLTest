#include "wrapperlibrary/Engine.h"
#include "wrapperlibrary/UISystem.h"
#include "wrapperlibrary/Objects.h"
#include "wrapperlibrary/Resources.h"
#include "wrapperlibrary/Helper.h"

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const std::string DISK = "disk";
const std::string WALL = "wall";

int main(int argc, char* argv[]) {

    UIForm form1 = {"form1", true, true, {
        { .type=label,  .title="TEST LABEL #1",  .rect={ .x=100, .y=20, .w=100, .h=30} },
        { .type=button, .title="TEST BUTTON #1", .rect={ .x=250, .y=20, .w=100, .h=30} }
    }};

    UIForm form2 = {"form2", true, true, {
        { .type=label,  .title="TEST LABEL #2",  .rect={ .x=100, .y=60, .w=100, .h=30} },
        { .type=button, .title="TEST BUTTON #2", .rect={ .x=250, .y=60, .w=100, .h=30} }
    }};

	Engine engine("SDLTest", {
        .windowRect  = { .x=SDL_WINDOWPOS_CENTERED, .y=SDL_WINDOWPOS_CENTERED, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT },
        .windowFlags = SDL_WINDOW_SHOWN
    });

    engine.addForm(form1.title, &form1);
    engine.addForm(form2.title, &form2);

    engine.loadResources(Helper::absolutePath("resources/resources.toml"));

    int result = engine.run();

    return result;
}
