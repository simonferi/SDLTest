#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameObject {
private:
    bool active = true;
    std::string fileName;
    SDL_Point position = { .x=0, .y=0 };
    SDL_FPoint velocity = { .x=0.0f, .y=0.0f };
    SDL_Rect srcRect = { .x=0, .y=0, .w=0, .h=0 };
	SDL_Rect dstRect = { .x=0, .y=0, .w=0, .h=0 };
    SDL_Texture* texture;
public:
    GameObject(std::string fileName): fileName(fileName) {}
    GameObject(SDL_Texture* texture): texture(texture) {}
    ~GameObject() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

    bool isActive() { return active; }
    void setActive(bool active) { this->active = active; }

    void setPosition(SDL_Point newPosition) { position = newPosition; }
    SDL_Point getPosition() { return position; }

    void setVelocity(SDL_FPoint newVelocity) { velocity = newVelocity; }
    SDL_FPoint getVelocity() { return velocity; }

    void loadImage(SDL_Renderer* renderer) {
        SDL_Surface* surface = IMG_Load(fileName.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        srcRect.w = surface->w;
        srcRect.h = surface->h;
        dstRect.w = surface->w;
        dstRect.h = surface->h;
        SDL_FreeSurface(surface);
    }

    void render(SDL_Renderer* renderer) {
        if (!texture) {
            loadImage(renderer);
        }
        dstRect.x = position.x;
        dstRect.y = position.y;
        SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
    }
};

#endif // OBJECTS_H
