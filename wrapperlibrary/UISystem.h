#pragma once

#ifndef UISYSTEM_H_
#define UISYSTEM_H_

#define DEFAULT_ELEMENT_XPOS 100;
#define DEFAULT_ELEMENT_YPOS 100;
#define DEFAULT_ELEMENT_HEIGHT 100;
#define DEFAULT_ELEMENT_WIDTH 100;

#include <string>
#include <functional>
#include <forward_list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Types.h"

class UIForm {
private:
    std::forward_list<UIElement> elements;
    std::unordered_map<UIElementType, UIElementRenderer> renderers = {
        {label, UIForm::renderLabel},
        {button, UIForm::renderButton}
    };
public:
    std::string title = "undefined";
    bool visible = false;
    bool active = false;

    UIForm(std::string title, bool visible, bool active, std::forward_list<UIElement> elements):
        title(title), visible(visible), active(active), elements(elements) {}
    UIForm() {}
    ~UIForm() {}

    void addElement(UIElement element) { elements.push_front(element); }
    std::forward_list<UIElement> getElements() { return elements; }

    void render(const UIRenderingContext& renderingContext) {
        for (UIElement& element: elements) {
            if (element.visible && renderers.count(element.type)) {
                renderers.at(element.type)(element, renderingContext);
            }
        }
    }

    static void renderLabel(const UIElement& element, const UIRenderingContext& renderingContext) {
        SDL_Surface* surface = TTF_RenderText_Blended(renderingContext.defaultFont, element.title.c_str(), renderingContext.fontColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderingContext.renderer, surface);
        SDL_FreeSurface(surface);
        int textWidth, textHeight;
        SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect textRect = { .x=element.rect.x, .y=element.rect.y, .w=textWidth, .h=textHeight };
        SDL_RenderCopy(renderingContext.renderer, texture, NULL, &textRect);
        SDL_DestroyTexture(texture);
        // std::cout << "UIForm::renderLabel() " << element.title << std::endl;
    }

    static void renderButton(const UIElement& element, const UIRenderingContext& renderingContext) {
        SDL_SetRenderDrawColor( renderingContext.renderer,
                                renderingContext.elementBackgroundColor.r,
                                renderingContext.elementBackgroundColor.g,
                                renderingContext.elementBackgroundColor.b,
                                renderingContext.elementBackgroundColor.a);
        SDL_RenderFillRect( renderingContext.renderer, &element.rect );
        SDL_SetRenderDrawColor( renderingContext.renderer,
                                renderingContext.windowBackgroundColor.r,
                                renderingContext.windowBackgroundColor.g,
                                renderingContext.windowBackgroundColor.b,
                                renderingContext.windowBackgroundColor.a);
        // std::cout << "UIForm::renderButton() " << element.title << std::endl;
    }

};

#endif /* UISYSTEM_H_ */
