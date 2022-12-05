/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** SFMLgraph
*/

#ifndef SFMLGRAPH_HPP_
#define SFMLGRAPH_HPP_

#include "MenuButton.hpp"
#include "Field.hpp"
#include "Sprite.hpp"


class SFMLgraph: public IGraphic {
    public:
        SFMLgraph();
        ~SFMLgraph();

        MenuButton setBox(sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor = sf::Color::White, sf::Color outlineColor = sf::Color::Transparent, int outlineThickness = 1);
        sf::Text setText(sf::Vector2f pos, std::string string, sf::Color fillColor = sf::Color::Black, int size = 30);
        sf::RectangleShape setRect(sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor = sf::Color::White, sf::Color outlineColor = sf::Color::Transparent, int outline = 1);
        Sprite createSprite(std::string &id, sf::Vector2f pos, std::string path, sf::IntRect rect);
        void updateSprite(Sprite &sprite, sf::Vector2f pos, sf::IntRect rect);
        /* Getters */


        /* Overrides */
        bool isWindowOpened() const;
        void getMenuEvents();
        void display();
        void initMap();
        void checkMouseMenu();
        void displayNames();
        void getGameEvents();

        std::vector<std::string> cutString(std::string str, char c);
        void checkSprite(std::string entity);
        void parse();


    private:
        /* Overall Vars */
        sf::RenderWindow _window;
        sf::Font _menuFont;
        sf::Event _event;

        /* buttons */
        std::map<std::string, MenuButton> _buttonMap;
        std::map<std::string, Field> _fieldsMap;
        std::map<std::string, Sprite> _spriteMap;
        std::map<std::string, Sprite> _background;

        /* Menu Nickname Vars */
        sf::String _playerInputNickname;

        /* Menu Server IP Vars */
        sf::String _playerInputIP;

        /* Menu Port Vars */
        sf::String _playerInputPort;

        /* Menu Room Code Vars */
        sf::String _playerInputRoomCode;

        /* Vectors to display Player's names */
        std::vector<sf::RectangleShape> _namesBox;
        std::vector<sf::Text> _wrNames;
        sf::Clock _refreshTimer;

        boost::asio::io_service _io;
};

#endif /* !SFMLGRAPH_HPP_ */
