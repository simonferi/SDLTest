#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include "Resources.h"

class GameObject {
public:
    std::string resourceAlias;
    ResourceImage* resourceImage;
    bool active = true;
    SDL_FPoint acceleration = { .x=0.0f, .y=0.0f };
    SDL_FPoint velocity     = { .x=0.0f, .y=0.0f };
    SDL_FPoint position     = { .x=0.0f, .y=0.0f };
    SDL_Rect   srcRect      = { .x=0, .y=0, .w=0, .h=0 };
    SDL_Rect   dstRect      = { .x=0, .y=0, .w=0, .h=0 };

    // constructor with resourceAlias argument
    GameObject(std::string resourceAlias): resourceAlias(resourceAlias) {}

    // copy constructor
    GameObject(const GameObject& other):
        resourceAlias(other.resourceAlias),
        resourceImage(other.resourceImage),
        active       (other.active),
        acceleration (other.acceleration),
        velocity     (other.velocity),
        position     (other.position),
        srcRect      (other.srcRect),
        dstRect      (other.dstRect)
        {}

    ~GameObject() {}

    void setResourceImage(ResourceImage* resourceImage) {
        this->resourceImage = resourceImage;
        srcRect.w = resourceImage->w;
        srcRect.h = resourceImage->h;
        dstRect.w = resourceImage->w;
        dstRect.h = resourceImage->h;
    }

    void render(SDL_Renderer* renderer) {
        dstRect.x = static_cast<int>(round(position.x));
        dstRect.y = static_cast<int>(round(position.y));
        SDL_RenderCopy(renderer, resourceImage->texture, &srcRect, &dstRect);
    }

    void update(float deltaTime) {
        // Update velocity based on acceleration
        velocity.x += acceleration.x * deltaTime;
        velocity.y += acceleration.y * deltaTime;

        // Update position based on velocity
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
        // std::cout << "deltaTime:" << deltaTime << "; position.x:" << position.x << "; position.y:" << position.y << std::endl;
    }
};

#endif // OBJECTS_H
