#ifndef TYPES_H
#define TYPES_H

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
