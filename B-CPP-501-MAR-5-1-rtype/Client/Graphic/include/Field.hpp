/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Field
*/

#ifndef FIELD_HPP_
#define FIELD_HPP_

#include "IGraphic.hpp"
#include "SFML/Config.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class Field {
    public:
        Field(sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor) {
            _field.setPosition(pos);
            _field.setSize(size);
            _field.setOutlineColor(outlineColor);
            _field.setFillColor(fillColor);
            _hitbox.height = size.y;
            _hitbox.width = size.x;
            _hitbox.left = pos.x;
            _hitbox.top = pos.y;
        };
        Field(){};
        ~Field(){};
        sf::RectangleShape _field;
        sf::FloatRect _hitbox;
        sf::Text _text;
        sf::RectangleShape _instPos;
        sf::Text _instruction;

    protected:
    private:
};

#endif /* !FIELD_HPP_ */