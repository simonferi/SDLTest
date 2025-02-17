#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <stdexcept>
#include <unordered_map>
#include <SDL2/SDL_image.h>
#include <toml.hpp>
#include "Types.h"
#include "Helper.h"

class ResourceImages {
private:
    std::unordered_map<std::string, ResourceImage> map;
public:
    // default constructor
    ResourceImages() {}

    // constructor with TOML file
    ResourceImages(std::string tomlFile) {
        const auto root    = toml::parse(tomlFile);
        const auto records = toml::find<std::vector<image_record>>(root, "images");
        for (auto& [alias, fileName, blendMode]: records) {
            std::cout << "alias:" << alias << " fileName:" << fileName << " blendMode:" << blendMode << std::endl;
            add(alias, Helper::absolutePath(fileName), (blendMode == "SDL_BLENDMODE_BLEND") ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
        }
    }

    ~ResourceImages() {
        for (const auto& [key, image]: map) {
            if (image.texture) {
                SDL_DestroyTexture(image.texture);
            }
        }
    }

    void add(std::string alias, std::string fileName, SDL_BlendMode blendMode) {
        map.insert({alias, { .fileName=fileName, .blendMode=blendMode }});
    }

    ResourceImage* get(std::string key) {
        return &map.at(key);
    }

    void loadImage(SDL_Renderer* renderer, ResourceImage& image) {
        if (!image.texture) {
            SDL_Surface* surface = IMG_Load(image.fileName.c_str());
            if (!surface) {
                throw std::runtime_error("Image loading failed!");
            }
            image.texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (!image.texture) {
                throw std::runtime_error("Texture initialisation failed!");
            }
            SDL_SetTextureBlendMode(image.texture, image.blendMode);
            image.w = surface->w;
            image.h = surface->h;
            SDL_FreeSurface(surface);
            // std::cout << "image loaded:" << image.fileName << std::endl;
        }
    }

    void loadImages(SDL_Renderer* renderer) {
        for (auto& [key, image]: map) {
            loadImage(renderer, image);
        }
    }

};

#endif // RESOURCES_H
