#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Helper.h"

enum ResourceType { rtImage, rtFont, rtSound };

class Resource {
protected:
    std::string id;
    ResourceType type;
public:
    Resource(std::string id, ResourceType type): id(id), type(type) {}
    virtual ~Resource() {
        std::cout << "~Resource() (base class destructor called)" << std::endl;
    }
    std::string getId() { return id; }
    ResourceType getType() { return type; }
};


class ResImage : public Resource {
private:
    SDL_BlendMode blendMode;
    SDL_Texture* texture;
    int w=0;
    int h=0;
public:

    ResImage(std::string id, std::string fileName, SDL_BlendMode blendMode, SDL_Renderer* renderer): Resource(id, rtImage), blendMode(blendMode) {
        SDL_Surface* surface = IMG_Load(Helper::absolutePath(fileName).c_str());
        if (!surface) {
            throw std::runtime_error("Image loading failed!");
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            throw std::runtime_error("Texture initialization failed!");
        }
        SDL_SetTextureBlendMode(texture, blendMode);
        w = surface->w;
        h = surface->h;
        SDL_FreeSurface(surface);
    }

    ~ResImage() {
        std::cout << "~ResImage() (derived class destructor called)" << std::endl;
        SDL_DestroyTexture(texture);
    }
};


class ResFont : public Resource {
private:
    TTF_Font* font;
public:
    ResFont(std::string id, std::string fileName, int fontSize): Resource(id, rtFont) {
        font = TTF_OpenFont(Helper::absolutePath(fileName).c_str(), fontSize);
        if (!font) {
            std::stringstream s;
            s << "TTF_OpenFont Error: " << TTF_GetError();
            throw std::runtime_error(s.str());
        }
    }
    ~ResFont() {
        std::cout << "~ResFont() (derived class destructor called)" << std::endl;
        TTF_CloseFont(font);
    }
};

#endif // GAMEOBJECTS_H
