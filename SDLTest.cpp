#include "wrapperlibrary/Engine.h"
#include "wrapperlibrary/UISystem.h"
#include "wrapperlibrary/Objects.h"

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {

    UIForm form1 = {"form1", true, true, {
        { .type=label,  .title="TEST LABEL",  .rect={ .x=100, .y=100, .w=100, .h=30} },
        { .type=button, .title="TEST BUTTON", .rect={ .x=250, .y=100, .w=100, .h=30} }
    }};

    UIForm form2 = {"form2", true, true, {
        { .type=label,  .title="TEST LABEL",  .rect={ .x=100, .y=200, .w=100, .h=30} },
        { .type=button, .title="TEST BUTTON", .rect={ .x=250, .y=200, .w=100, .h=30} }
    }};

	Engine engine("SDLTest", {
        .windowRect  = { .x=SDL_WINDOWPOS_CENTERED, .y=SDL_WINDOWPOS_CENTERED, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT },
        .windowFlags = SDL_WINDOW_SHOWN
    });

    engine.addForm(form1.getTitle(), &form1);
    engine.addForm(form2.getTitle(), &form2);

    GameObject o1("resources/images/disk.png");
    engine.addObject(&o1);

    return engine.run();
}
