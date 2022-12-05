/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** MenuButton
*/

#ifndef MENUBUTTON_HPP_
#define MENUBUTTON_HPP_

#include "IGraphic.hpp"
#include "SFML/Config.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class MenuButton {
    public:
        MenuButton(sf::RectangleShape &shape, sf::FloatRect &rect, sf::Text &text) {
            _btn = shape;
            _hitbox = rect;
            _text = text;
        };
        MenuButton(){};
        ~MenuButton(){};
        bool checkMouse(sf::RenderWindow win) {
            if (_hitbox.contains(win.mapPixelToCoords(sf::Mouse::getPosition(win))))
                return (true);
            return (false);
        };
        sf::RectangleShape _btn;
        sf::FloatRect _hitbox;
        sf::Text _text;

    protected:
    private:
};

#endif /* !MENUBUTTON_HPP_ */