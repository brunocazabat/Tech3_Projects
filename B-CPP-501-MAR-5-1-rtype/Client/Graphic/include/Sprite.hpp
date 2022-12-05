/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "IGraphic.hpp"
#include "SFML/Config.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class Sprite {
    public:
        Sprite() {};

        /* This Constructor needs a "new" to work apparently */
        Sprite(std::string id, std::string path, sf::IntRect rect, sf::Vector2f pos = sf::Vector2f(0, 0)) {

            if (!_texture.loadFromFile(path)) {
                // Error loading the Texture
                std::cerr << "Couldn't load path: " << path << std::endl;
            }

            _sprite.setTexture(_texture);
            _sprite.setPosition(pos);
            _sprite.setTextureRect(rect);
            _hitbox = _sprite.getGlobalBounds();
            _id = id;

        }
        ~Sprite() {};

        /* Move Sprites */
        void moveSprite(sf::Vector2f move) {
            _sprite.move(move);
        }

        /* Loads and sets a texture to a sprite at a given position (0,0 if none) */
        void loadTexture(std::string path, sf::Vector2f pos = sf::Vector2f(0, 0)) {
            if (!_texture.loadFromFile(path)) {
                // Error loading the Texture
                std::cerr << "Couldn't load path: " << path << std::endl;
            }

            _sprite.setTexture(_texture);
            _sprite.setPosition(pos);
        }

        /* Linear Scales the Sprite */
        void setSpriteScale(sf::Vector2f scale)
        {
            _sprite.setScale(scale);
        }

        /* Sets an IntRect to the sprite's texture */
        void setRect(sf::IntRect rect) {
            _sprite.setTextureRect(rect);
        }

        /* Sets the sprite to a new position */
        void setPosition(sf::Vector2f pos) {
            _sprite.setPosition(pos);
        }

        void setId(std::string id) {
            _id = id;
        }

        sf::Sprite _sprite;
        sf::FloatRect _hitbox;
        sf::Texture _texture;
        std::string _id;


    protected:
    private:
};

#endif /* !SPRITE_HPP_ */
