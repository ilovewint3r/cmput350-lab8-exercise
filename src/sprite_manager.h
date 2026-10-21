#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <cassert>
#include <cstddef>
#include <deque>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>

using SpriteID = size_t;

class SpriteManager {
public:
    sf::Texture& registerTexture(const std::string& filepath) {
        auto [iterator, inserted] = textures.try_emplace(filepath, filepath);
        return iterator->second;
    }

    template <typename... Args>
    SpriteID createSprite(Args&&... args) {
        sprites.emplace_back(std::forward<Args>(args)...);
        return sprites.size() - 1;
    }

    Sprite& getSprite(SpriteID id) {
        assert(id < sprites.size());
        return sprites[id];
    }
private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::deque<Sprite> sprites;
};

#endif  // SPRITE_MANAGER_H
