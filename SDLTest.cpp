#include "wrapperlibrary/Engine.h"
#include "wrapperlibrary/UISystem.h"
#include "wrapperlibrary/Objects.h"
#include "wrapperlibrary/Resources.h"
#include "wrapperlibrary/Helper.h"

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const std::string DISK = "d";
const std::string WALL = "w";

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

    ResourceImages resImages;
    resImages.add(DISK, Helper::absolutePath("resources/images/disk.png"), SDL_BLENDMODE_BLEND);
    resImages.add(WALL, Helper::absolutePath("resources/images/wall.png"), SDL_BLENDMODE_BLEND);
    engine.setResourceImages(&resImages);

    GameObject o1(DISK, { .x=300.0f, .y=300.0f });
    o1.acceleration = { .x=  0.0f, .y= 10.0f };
    o1.velocity     = { .x=  0.0f, .y=-50.0f };
    engine.addObject(&o1);

    GameObject o2(DISK, { .x=320.0f, .y=300.0f });
    engine.addObject(&o2);

    GameObject* staticObjects[80];
    int j=0, k=0;
    for ( int i=0; i<80; ++i ) {
        GameObject* pObject = new GameObject(WALL);
        j++;
        if (i % 5 == 0) k++;
        if (i % 20 == 0) j=0;
        pObject->position = { .x=60.0f + j*32, .y=100.0f + k*20 };
        engine.addObject(pObject);
        staticObjects[i] = pObject;
    }

    int result = engine.run();

    for ( int i=0; i<80; ++i ) {
        delete staticObjects[i];
        staticObjects[i] = nullptr;
    }

    return result;
}
