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

enum UIElementType { undefined, panel, tab, label, button };

typedef struct UIElement {
	unsigned char id = 0;
	UIElementType type = undefined;
	std::string title = "";
	std::string hint = "";
	int x = DEFAULT_ELEMENT_XPOS;
	int y = DEFAULT_ELEMENT_YPOS;
	int w = DEFAULT_ELEMENT_WIDTH;
	int h = DEFAULT_ELEMENT_HEIGHT;
	bool visible = true;
	bool enabled = true;
	bool active = false;
} UIElement;

typedef struct UIRenderingContext {
	SDL_Window*   window          = nullptr;
	SDL_Renderer* renderer        = nullptr;
	TTF_Font*     defaultFont     = nullptr;
	SDL_Color     backgroundColor = { .r=125, .g=125, .b=125, .a=255 };
	SDL_Color     foregroundColor = { .r=255, .g=255, .b=255, .a=255 };
	SDL_Color     borderColor     = { .r=200, .g=200, .b=200, .a=255 };
	SDL_Rect      windowRect;
	Uint32        windowFlags;
} UIRenderingContext;

void renderLabel(const UIElement& element, const UIRenderingContext& renderingContext) {
	SDL_Color color = {125, 125, 125, 255};
	// SDL_Surface* surface = TTF_RenderText_Solid(getFont(), element.title.c_str(), color);
	SDL_Surface* surface = TTF_RenderText_Blended(renderingContext.defaultFont, element.title.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderingContext.renderer, surface);
	SDL_FreeSurface(surface);
	int textWidth, textHeight;
	SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
	SDL_Rect textRect = { .x=element.x, .y=element.y, .w=textWidth, .h=textHeight };
	SDL_RenderCopy(renderingContext.renderer, texture, NULL, &textRect);
	SDL_DestroyTexture(texture);
	// std::cout << "CGUILabel::render() " << element.title << std::endl;
}

void renderButton(const UIElement& element, const UIRenderingContext& renderingContext) {
	SDL_SetRenderDrawColor( renderingContext.renderer, 255, 255, 255, 255 );
	SDL_Rect rect = { .x=element.x, .y=element.y, .w=element.w, .h=element.h };
	SDL_RenderFillRect( renderingContext.renderer, &rect );
	SDL_SetRenderDrawColor( renderingContext.renderer, 0, 0, 0, 255 );
	// std::cout << "CGUIButton::render() " << element.title << std::endl;
}

typedef std::function<void(const UIElement&, const UIRenderingContext& renderingContext)> UIElementRenderer;
std::unordered_map<UIElementType, UIElementRenderer> renderers = {
	{label, renderLabel},
	{button, renderButton}
};

class UIForm {
private:
	std::string title = "undefined";
	bool visible = true;
	bool active = false;
	std::forward_list<UIElement> elements;
public:
	UIForm(std::string title, bool visible, bool active, std::forward_list<UIElement> elements):
		title(title), visible(visible), active(active), elements(elements) {}
	UIForm() {}
	~UIForm() {}

	std::string getTitle() { return title; }
	bool isVisible() { return visible; }
	void setVisible(bool visible) { this->visible = visible; }
	bool isActive() { return active; }
	void setActive(bool active) { this->active = active; }
	void addElement(UIElement element) { elements.push_front(element); }
	std::forward_list<UIElement> getElements() { return elements; }
	void render(const UIRenderingContext& renderingContext) {
		for (UIElement& element: elements) {
			if (element.visible && renderers.count(element.type)) {
				renderers.at(element.type)(element, renderingContext);
			}
		}
	}
};

#endif /* UISYSTEM_H_ */