#ifndef TYPES_H
#define TYPES_H

#include <toml.hpp>

struct image_record {
    image_record(const toml::value& v):
        alias    (toml::find_or<std::string> (v, "alias",     std::string(""))),
        fileName (toml::find_or<std::string> (v, "fileName",  std::string(""))),
        blendMode(toml::find_or<std::string> (v, "blendMode", std::string("SDL_BLENDMODE_BLEND")))
        {}
    std::string alias;
    std::string fileName;
    std::string blendMode;
};

struct object_record {
    object_record(const toml::value& v):
        alias(toml::find_or<std::string> (v, "alias", std::string(""))),
        posX (toml::find_or<float>       (v, "posX",  0.0f)),
        posY (toml::find_or<float>       (v, "posY",  0.0f)),
        accX (toml::find_or<float>       (v, "accX",  0.0f)),
        accY (toml::find_or<float>       (v, "accY",  0.0f)),
        velX (toml::find_or<float>       (v, "velX",  0.0f)),
        velY (toml::find_or<float>       (v, "velY",  0.0f))
        {}
    std::string alias;
    float posX, posY, accX, accY, velX, velY;
};


typedef struct ResourceImage {
    std::string fileName;
    SDL_BlendMode blendMode;
    SDL_Texture* texture;
    int w=0;
    int h=0;
} ResourceImage;

enum UIElementType { undefined, panel, tab, label, button };

typedef struct UIElement {
    unsigned char id = 0;
    UIElementType type = undefined;
    std::string title = "";
    std::string hint = "";
    SDL_Rect rect = { .x=0, .y=0, .w=0, .h=0 };
    bool visible = true;
    bool enabled = true;
    bool active = false;
} UIElement;

typedef struct UIRenderingContext {
    SDL_Window*   window          = nullptr;
    SDL_Renderer* renderer        = nullptr;
    TTF_Font*     defaultFont     = nullptr;
    SDL_Color     windowBackgroundColor  = { .r= 150,.g=180, .b= 150,.a=255 };
    SDL_Color     elementBackgroundColor = { .r=125, .g=125, .b=125, .a=255 };
    SDL_Color     fontColor              = { .r=255, .g=255, .b=255, .a=255 };
    SDL_Color     borderColor            = { .r=200, .g=200, .b=200, .a=255 };
    SDL_Rect      windowRect;
    Uint32        windowFlags;
} UIRenderingContext;

typedef std::function<void(const UIElement&, const UIRenderingContext& renderingContext)> UIElementRenderer;


#endif // TYPES_H
