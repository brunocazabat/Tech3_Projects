/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** SMFLgraph
*/

#include "../include/SFMLgraph.hpp"


/* Default Constructor, creates a 1280x720 Window */
SFMLgraph::SFMLgraph()
{
    _width = 1280;
    _height = 720;
    _fpsLimit = 30;
    _menuUserFocus = Nothing;
    _screenDisplay = MainMenu;
    _isAdmin = false;
    _isConnected = false;
    _roomSize = 0;
    _playerInputNickname = DEFAULT_USER;
    _playerInputIP = DEFAULT_IP;
    _playerInputPort = DEFAULT_PORT;
    _playerInputRoomCode = DEFAULT_CODE;

    _window.create(sf::VideoMode(_width, _height), WINDOW_NAME);
    _window.setFramerateLimit(_fpsLimit);
    _menuFont.loadFromFile(MENU_FONT_PATH);
    initMap();
}

SFMLgraph::~SFMLgraph()
{
    if (_window.isOpen())
        _window.close();

    // Clearing Vectors and Maps
    // _wrNamesString.clear();
    // _namesBox.clear();
    // _wrNames.clear();
    // _buttonMap.clear();
    // _fieldsMap.clear();
    // _spriteMap.clear();
    // _background.clear();

    // delete _client;
    // delete _udpClient;
}


/* Overrides */

/* Returns "true" if the Window is Opened, "false" if it is not */
bool SFMLgraph::isWindowOpened() const
{
    if (_window.isOpen())
        return true;
    else
        return false;
}

/* Creates a Button */
MenuButton SFMLgraph::setBox(sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, int outlineThickness)
{
    MenuButton but;

    if (outlineColor != sf::Color::Transparent) {
        but._btn.setOutlineThickness(outlineThickness);
        but._btn.setOutlineColor(outlineColor);
    }
    but._btn.setFillColor(fillColor);
    but._btn.setSize(size);
    but._btn.setPosition(pos);
    but._hitbox.width = size.x;
    but._hitbox.height = size.y;
    but._hitbox.left = pos.x;
    but._hitbox.top = pos.y;
    return (but);
}

/* Creates a Text */
sf::Text SFMLgraph::setText(sf::Vector2f pos, std::string string, sf::Color fillColor, int size)
{
    sf::Text text;
    text.setFont(_menuFont);
    text.setCharacterSize(size);
    text.setString(string);
    text.setFillColor(fillColor);
    text.setPosition(pos);
    return (text);
}

/* Create a RectangleShape */
sf::RectangleShape SFMLgraph::setRect(sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, int outline)
{
    sf::RectangleShape rect;

    if (outlineColor != sf::Color::Transparent) {
        rect.setOutlineThickness(outline);
        rect.setOutlineColor(outlineColor);
    }

    rect.setSize(size);
    rect.setPosition(pos);
    rect.setFillColor(fillColor);
    return (rect);
}

/* Displays the name in the Waiting Room */
void SFMLgraph::displayNames() {


    sf::Time elapsed = _refreshTimer.getElapsedTime();

    if (elapsed.asSeconds() > 3.0) {

        _client->send("GETMEMBERROOM\n");
        std::string names = _client->read(false);


        std::string delimiter = ";";
        size_t pos = names.find(delimiter);
        int posy = 100;

        names.erase(0, pos + delimiter.length());

        while ((pos = names.find(delimiter)) != std::string::npos) {
            _wrNamesString.push_back(names.substr(0, pos));
            names.erase(0, pos + delimiter.length());
        }

        _wrNamesString.push_back(names.substr(0, names.length() - 1));

        if (_wrNamesString.size() != _roomSize) {
            _namesBox.clear();
            _wrNames.clear();
            pos = 0;
            while (pos != _wrNamesString.size()) {

                _namesBox.push_back(setRect(sf::Vector2f(490, posy), sf::Vector2f(300, 40), sf::Color::White, sf::Color(128, 128, 128, 255), 5));
                if (_nickname == _wrNamesString.at(pos)) {
                    _wrNames.push_back(setText(sf::Vector2f(500, posy), _wrNamesString.at(pos), sf::Color(0, 0, 102, 255)));
                    if (pos == 0) {
                        _isAdmin = true;
                    } else
                        _isAdmin = false;
                }
                else
                    _wrNames.push_back(setText(sf::Vector2f(500, posy), _wrNamesString.at(pos)));
                posy += 100;
                pos++;
            }

            _roomSize = _wrNamesString.size();

        }

        _refreshTimer.restart();
        _wrNamesString.clear();
    }
}


/* Returns KeyPressed while in game and checks if Window is closed */
void SFMLgraph::getMenuEvents()
{
    std::string messageServer;

    while (_window.pollEvent(_event)) {
        if ((_event.type == sf::Event::KeyPressed) && (_event.key.code == sf::Keyboard::Escape))
            _window.close();

        if (_event.type == sf::Event::Closed) {
            _window.close();
            if (_isConnected) {
                _client->send("EXIT\n");
                _client->read(false);
            }
        }

        if (_event.type == sf::Event::MouseButtonPressed) {

            if (_screenDisplay == MainMenu) {
                if (_fieldsMap["Nick"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
                    _menuUserFocus = Nickname;
                } else if (_fieldsMap["ServIP"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
                    _menuUserFocus = ServerIP;
                } else if (_buttonMap["Connect"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
                    _client = new BoostClientTcp(_playerInputIP.toAnsiString(), std::atoi(_playerInputPort.toAnsiString().c_str()));
                    _client->read(false);
                    _client->send("LOGIN;" + _playerInputNickname.toAnsiString() + "\n");
                    _nickname.assign(_playerInputNickname.toAnsiString());
                    messageServer = _client->read(false);
                    if (messageServer == LOGIN_SUCCESS) {
                        _screenDisplay = Join;
                        _isConnected == true;
                    }
                } else if (_fieldsMap["Port"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
                    _menuUserFocus = Port;
                } else if (_buttonMap["Quit"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
                    _window.close();
                    if (_isConnected) {
                        _client->send("EXIT\n");
                        _client->read(false);
                    }
                } else {
                    _menuUserFocus = Nothing;
                }

            } else if (_screenDisplay == Join) {
                if (_buttonMap["Create"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
                    _client->send("CREATEROOM\n");
                    _roomCodeString = _client->read(false);
                    if (_roomCodeString != NOT_LOGIN && _roomCodeString != ALREADY_IN_ROOM && _roomCodeString != ERROR_CODE_ROOM) {
                        _screenDisplay = WaitingRoom;

                        std::string delimiter = ";";
                        size_t pos = _roomCodeString.find(delimiter);

                        _roomCodeString.erase(0, pos + delimiter.length());

                        _fieldsMap["RoomCode"]._text.setString(_roomCodeString);

                        sf::FloatRect rectBounds = _buttonMap["WaitingRoomCode"]._btn.getGlobalBounds();
                        sf::FloatRect textBounds = _fieldsMap["RoomCode"]._text.getGlobalBounds();

                        _fieldsMap["RoomCode"]._text.setPosition((rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2)), 650);

                        _buttonMap["Quit"]._btn.setPosition(850, 650);
                        _buttonMap["Quit"]._hitbox.left = 850;
                        rectBounds = _buttonMap["Quit"]._btn.getGlobalBounds();
                        textBounds = _buttonMap["Quit"]._text.getGlobalBounds();
                        _buttonMap["Quit"]._text.setPosition((rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2)), 650);


                    }
                } else if (_fieldsMap["RoomCode"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
                    _menuUserFocus = RoomCode;
                } else if (_buttonMap["Quit"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
                    _client->send("EXIT\n");
                    _client->read(false);
                    _window.close();
                } else if (_buttonMap["Join"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {

                    _client->send("JOINROOM;" + _playerInputRoomCode.toAnsiString() + "\n");
                    messageServer = _client->read(false);
                    if (messageServer != NOT_LOGIN && messageServer != ALREADY_IN_ROOM && messageServer != ROOM_FULL && messageServer != ERROR_CODE_ROOM && messageServer != NO_ROOM) {
                        _screenDisplay = WaitingRoom;

                        _fieldsMap["RoomCode"]._text.setString(_playerInputRoomCode.toAnsiString());

                        sf::FloatRect rectBounds = _buttonMap["WaitingRoomCode"]._btn.getGlobalBounds();
                        sf::FloatRect textBounds = _fieldsMap["RoomCode"]._text.getGlobalBounds();

                        _fieldsMap["RoomCode"]._text.setPosition((rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2)), 650);

                        _buttonMap["Quit"]._btn.setPosition(850, 650);
                        _buttonMap["Quit"]._hitbox.left = 850;
                        rectBounds = _buttonMap["Quit"]._btn.getGlobalBounds();
                        textBounds = _buttonMap["Quit"]._text.getGlobalBounds();
                        _buttonMap["Quit"]._text.setPosition((rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2)), 650);
                    }
                } else {
                    _menuUserFocus = Nothing;
                }

            } else if (_screenDisplay == WaitingRoom) {

                messageServer = _client->read(true);

                if (messageServer != "") {
                    int port = 0;
                    std::string delimiter = ";";
                    size_t _pos = messageServer.find(delimiter);

                    messageServer.erase(0, _pos + delimiter.length());
                    port = std::stoi(messageServer);

                    _udpClient = new UdpGame(_io, port);

                    std::string cmd = _nickname + ";" + "z";

                    _udpClient->send(cmd);

                    _screenDisplay = Game;
                }

                if (_buttonMap["Quit"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
                    _client->send("EXIT\n");
                    _client->read(false);
                    _window.close();
                }

                if (_buttonMap["Start"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
                    _client->send("STARTGAME\n");
                    messageServer = _client->read(false);

                    int port = 0;
                    std::string delimiter = ";";
                    size_t _pos = messageServer.find(delimiter);

                    messageServer.erase(0, _pos + delimiter.length());
                    port = std::stoi(messageServer);

                    _udpClient = new UdpGame(_io, port);

                    std::string cmd = _nickname + ";" + "z";

                    _udpClient->send(cmd);

                    _screenDisplay = Game;
                }

            }
        }

        if (_event.type == sf::Event::TextEntered) {

            if (_screenDisplay == MainMenu) {

                if (_menuUserFocus == Nickname) {
                    if (_event.text.unicode == '\b') {
                        if (_playerInputNickname.getSize() > 0) {
                            _playerInputNickname.erase(_playerInputNickname.getSize() - 1, 1);
                            _fieldsMap["Nick"]._text.setString(_playerInputNickname);
                        }
                    } else {
                        _playerInputNickname += _event.text.unicode;
                        _fieldsMap["Nick"]._text.setString(_playerInputNickname);
                    }
                }

                if (_menuUserFocus == ServerIP) {
                    if (_event.text.unicode == '\b') {
                        if (_playerInputIP.getSize() > 0) {
                            _playerInputIP.erase(_playerInputIP.getSize() - 1, 1);
                            _fieldsMap["ServIP"]._text.setString(_playerInputIP);
                        }
                    } else {
                        _playerInputIP += _event.text.unicode;
                        _fieldsMap["ServIP"]._text.setString(_playerInputIP);
                    }
                }

                if (_menuUserFocus == Port) {
                    if (_event.text.unicode == '\b') {
                        if (_playerInputPort.getSize() > 0) {
                            _playerInputPort.erase(_playerInputPort.getSize() - 1, 1);
                            _fieldsMap["Port"]._text.setString(_playerInputPort);
                        }
                    } else if (_playerInputPort.getSize() < 4) {
                        _playerInputPort += _event.text.unicode;
                        _fieldsMap["Port"]._text.setString(_playerInputPort);
                    }
                }

            } else if (_screenDisplay == Join) {

                if (_menuUserFocus == RoomCode) {
                    if (_event.text.unicode == '\b') {
                        if (_playerInputRoomCode.getSize() > 0) {
                            _playerInputRoomCode.erase(_playerInputRoomCode.getSize() - 1, 1);
                            _fieldsMap["RoomCode"]._text.setString(_playerInputRoomCode);
                        }
                    } else if (_playerInputRoomCode.getSize() < 5) {
                        _playerInputRoomCode += _event.text.unicode;
                        _fieldsMap["RoomCode"]._text.setString(_playerInputRoomCode);
                    }
                }

            }

        }
    }
}

void SFMLgraph::initMap()
{
    _buttonMap.insert(std::pair<std::string, MenuButton>("Connect", setBox(sf::Vector2f(340, 500), sf::Vector2f(210, 40), sf::Color::Black, sf::Color::White, 1)));
    _buttonMap.insert(std::pair<std::string, MenuButton>("Join", setBox(sf::Vector2f(340, 500), sf::Vector2f(175, 40), sf::Color::Black, sf::Color::White, 1)));
    _buttonMap.insert(std::pair<std::string, MenuButton>("Create", setBox(sf::Vector2f(525, 500), sf::Vector2f(175, 40), sf::Color::Black, sf::Color::White, 1)));
    _buttonMap.insert(std::pair<std::string, MenuButton>("WaitingRoomCode", setBox(sf::Vector2f(530, 650), sf::Vector2f(220, 40), sf::Color::White, sf::Color(128, 128, 128, 255), 5)));
    _buttonMap.insert(std::pair<std::string, MenuButton>("Quit", setBox(sf::Vector2f(710, 650), sf::Vector2f(110, 40), sf::Color::Black, sf::Color::White, 1)));
    // Change START Position, it's really bad
    _buttonMap.insert(std::pair<std::string, MenuButton>("Start", setBox(sf::Vector2f(240, 650), sf::Vector2f(140, 40), sf::Color::Black, sf::Color::White, 1)));
    _buttonMap.insert(std::pair<std::string, MenuButton>("Score", setBox(sf::Vector2f(30, 30), sf::Vector2f(150, 40), sf::Color::White, sf::Color::Black, 3)));

    _fieldsMap.insert(std::pair<std::string, Field>("Nick", Field(sf::Vector2f(340, 100), sf::Vector2f(600, 40), sf::Color::White, sf::Color::Black)));
    _fieldsMap.insert(std::pair<std::string, Field>("ServIP", Field(sf::Vector2f(340, 200), sf::Vector2f(600, 40), sf::Color::White, sf::Color::Black)));
    _fieldsMap.insert(std::pair<std::string, Field>("Port", Field(sf::Vector2f(340, 300), sf::Vector2f(600, 40), sf::Color::White, sf::Color::Black)));
    _fieldsMap.insert(std::pair<std::string, Field>("RoomCode", Field(sf::Vector2f(340, 400), sf::Vector2f(600, 40), sf::Color::White, sf::Color::Black)));

    _background.insert(std::pair<std::string, Sprite>("MenuBG", Sprite()));
    _background.insert(std::pair<std::string, Sprite>("WrBG", Sprite()));

    _background["MenuBG"].loadTexture(MENU_BG_PATH);
    _background["MenuBG"].setSpriteScale(sf::Vector2f(0.25, 0.25));
    _background["WrBG"].loadTexture(WR_BG_PATH);
    _background["WrBG"].setSpriteScale(sf::Vector2f(0.67, 0.67));

    _buttonMap["Connect"]._text = setText(sf::Vector2f(350, 500), CONNECT, sf::Color::White);
    _buttonMap["Join"]._text = setText(sf::Vector2f(350, 500), JOIN, sf::Color::White);
    _buttonMap["Create"]._text = setText(sf::Vector2f(535, 500), CREATE, sf::Color::White);
    _buttonMap["Quit"]._text = setText(sf::Vector2f(720, 650), QUIT, sf::Color::White);
    _buttonMap["Start"]._text = setText(sf::Vector2f(250, 650), START_GAME, sf::Color::White);
    _buttonMap["Score"]._text = setText(sf::Vector2f(40, 30), std::string("0"));
    // Centering the Score Text
    sf::FloatRect rectBounds = _buttonMap["Score"]._btn.getGlobalBounds();
    sf::FloatRect textBounds = _buttonMap["Score"]._text.getGlobalBounds();
    // _buttonMap["Score"]._text.setPosition((rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2)), 650);

    // Fields Map
    _fieldsMap["Nick"]._text = setText(sf::Vector2f(500, 100), DEFAULT_USER, sf::Color::Black);
    _fieldsMap["Nick"]._instruction = setText(sf::Vector2f(350, 100), ENTER_NAME);
    _fieldsMap["ServIP"]._text = setText(sf::Vector2f(580, 200), DEFAULT_IP, sf::Color::Black);
    _fieldsMap["ServIP"]._instruction = setText(sf::Vector2f(350, 200), ENTER_IP);
    _fieldsMap["Port"]._text = setText(sf::Vector2f(500, 300), DEFAULT_PORT, sf::Color::Black);
    _fieldsMap["Port"]._instruction = setText(sf::Vector2f(350, 300), ENTER_PORT);
    _fieldsMap["RoomCode"]._text = setText(sf::Vector2f(500, 400), DEFAULT_CODE, sf::Color::Black);
    _fieldsMap["RoomCode"]._instruction = setText(sf::Vector2f(350, 400), ENTER_CODE);

}

/* Check where the Mouse is on the screen */
void SFMLgraph::checkMouseMenu()
{

    /* _buttonMap.insert(std::pair<std::string, MenuButton>("LaeveRoom", MenuButton())); */

    if (_screenDisplay == MainMenu) {
        _fieldsMap["Nick"]._field.setFillColor(sf::Color::White);
        _fieldsMap["ServIP"]._field.setFillColor(sf::Color::White);
        _buttonMap["Connect"]._btn.setFillColor(sf::Color::Black);
        _buttonMap["Connect"]._text.setFillColor(sf::Color::White);
        _buttonMap["Quit"]._btn.setFillColor(sf::Color::Black);
        _buttonMap["Quit"]._text.setFillColor(sf::Color::White);
        _fieldsMap["Port"]._field.setFillColor(sf::Color::White);
        if (_fieldsMap["Nick"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _fieldsMap["Nick"]._field.setFillColor(sf::Color(222, 222, 222, 255));
        } else if (_fieldsMap["ServIP"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _fieldsMap["ServIP"]._field.setFillColor(sf::Color(222, 222, 222, 255));
        } else if (_buttonMap["Connect"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _buttonMap["Connect"]._btn.setFillColor(sf::Color(222, 222, 222, 255));
            _buttonMap["Connect"]._text.setFillColor(sf::Color::Black);
        } else if (_fieldsMap["Port"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _fieldsMap["Port"]._field.setFillColor(sf::Color(222, 222, 222, 255));
        } else if (_buttonMap["Quit"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _buttonMap["Quit"]._btn.setFillColor(sf::Color(222, 222, 222, 255));
            _buttonMap["Quit"]._text.setFillColor(sf::Color::Black);
        }
    } else if (_screenDisplay == Join) {
        _buttonMap["Create"]._btn.setFillColor(sf::Color::Black);
        _buttonMap["Create"]._text.setFillColor(sf::Color::White);
        _buttonMap["Quit"]._btn.setFillColor(sf::Color::Black);
        _buttonMap["Quit"]._text.setFillColor(sf::Color::White);
        _fieldsMap["RoomCode"]._field.setFillColor(sf::Color::White);
        _buttonMap["Join"]._btn.setFillColor(sf::Color::Black);
        _buttonMap["Join"]._text.setFillColor(sf::Color::White);
        if (_buttonMap["Create"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _buttonMap["Create"]._btn.setFillColor(sf::Color(222, 222, 222, 255));
            _buttonMap["Create"]._text.setFillColor(sf::Color::Black);
        } else if (_buttonMap["Quit"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _buttonMap["Quit"]._btn.setFillColor(sf::Color(222, 222, 222, 255));
        } else if (_fieldsMap["RoomCode"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _fieldsMap["RoomCode"]._field.setFillColor(sf::Color(222, 222, 222, 255));
        } else if (_buttonMap["Quit"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _buttonMap["Quit"]._btn.setFillColor(sf::Color(222, 222, 222, 255));
            _buttonMap["Quit"]._text.setFillColor(sf::Color::Black);
        } else if (_buttonMap["Join"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _buttonMap["Join"]._btn.setFillColor(sf::Color(222, 222, 222, 255));
            _buttonMap["Join"]._text.setFillColor(sf::Color::Black);
        }
    } else if (_screenDisplay == WaitingRoom) {
        _buttonMap["Quit"]._btn.setFillColor(sf::Color::Black);
        _buttonMap["Quit"]._text.setFillColor(sf::Color::White);
        _buttonMap["Start"]._btn.setFillColor(sf::Color::Black);
        _buttonMap["Start"]._text.setFillColor(sf::Color::White);
        if (_buttonMap["Quit"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _buttonMap["Quit"]._btn.setFillColor(sf::Color(222, 222, 222, 255));
            _buttonMap["Quit"]._text.setFillColor(sf::Color::Black);
        } else if (_buttonMap["Start"]._hitbox.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)))) {
            _buttonMap["Start"]._btn.setFillColor(sf::Color(222, 222, 222, 255));
            _buttonMap["Start"]._text.setFillColor(sf::Color::Black);
        }
    }
}


/* Creates a sprite to display */
Sprite SFMLgraph::createSprite(std::string &id, sf::Vector2f pos, std::string path, sf::IntRect rect)
{
    Sprite newSprite;

    // Loads the texture from a file (path) and set the sprite's position
    newSprite.loadTexture(path, pos);

    // Sets a Rect in the SpriteSheet
    newSprite.setRect(rect);

    // Sets the Sprite's ID
    newSprite.setId(id);

    return newSprite;
}

/* Updates the Player's Sprite */
void SFMLgraph::updateSprite(Sprite &sprite, sf::Vector2f pos, sf::IntRect rect)
{
    // Updates the position (using move should be cleaner)
    sprite.setPosition(pos);

    // Updates the Rect in the SpriteSheet
    sprite.setRect(rect);
}

/* Function to get the events while in game */
void SFMLgraph::getGameEvents()
{
    std::string serv;
    std::string cmd;

    while (_window.pollEvent(_event)) {

        if (_event.type == sf::Event::Closed) {
            _window.close();
            // DC'ing Client if connected
            if (_isConnected) {
                _client->send("EXIT\n");
                _client->read(false);
            }
        }
    }

    // if (_isConnected) {
    //     // Receiving what UDP sent
    //     serv = _udpClient->read();
    //     std::cout << serv << std::endl;
    //     if (!serv.empty()) {
    //         _fromServer = serv;
    //         parse();
    //     }
    // }

    _sent = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        // Right key is pressed
        std::string cmd = _nickname + ";" + "d";
        _udpClient->send(cmd);
        _sent = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        // Left key is pressed
        std::string cmd = _nickname + ";" + "q";
        _udpClient->send(cmd);
        _sent = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        // Up key is pressed
        std::string cmd = _nickname + ";" + "z";
        _udpClient->send(cmd);
        _sent = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        // Down key is pressed
        std::string cmd = _nickname + ";" + "s";
        _udpClient->send(cmd);
        _sent = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        // Space key is pressed
        std::string cmd = _nickname + ";" + " ";
        _udpClient->send(cmd);
        _sent = true;

    }

    if (_sent) {
        _fromServer = _udpClient->read();
        if (!_fromServer.empty())
            parse();
    }
}

std::vector<std::string> SFMLgraph::cutString(std::string str, char c)
{
    std::vector<std::string> tmp;
    size_t i = 0;

    while (!str.empty()) {
        if (str.find(c) != std::string::npos)
            tmp.push_back(str.substr(0, str.find(c)));
        else {
            tmp.push_back(str);
            return (tmp);
        }
        str = str.substr(str.find(c) + 1);
    }
    return (tmp);
}

void SFMLgraph::checkSprite(std::string entity)
{
    //Username:x:y:path:xs:ys:xsize:ysize
    std::vector<std::string> elem = cutString(entity, ':');

    if (elem.size() != 8)
        return;
    for (std::map<std::string, Sprite>::iterator it = _spriteMap.begin(); it != _spriteMap.end(); it++) {
        if (it->first == elem.at(0)) {
            updateSprite(it->second, sf::Vector2f(std::stoi(elem.at(1)), std::stoi(elem.at(2))), sf::IntRect(std::stoi(elem.at(4)), std::stoi(elem.at(5)), std::stoi(elem.at(6)), std::stoi(elem.at(7))));
            return;
        }
    }
    _spriteMap.insert(std::pair<std::string, Sprite>(elem.at(0), Sprite()));
    _spriteMap[elem.at(0)].loadTexture(elem.at(3));
    _spriteMap[elem.at(0)].setPosition(sf::Vector2f(std::stoi(elem.at(1)), std::stoi(elem.at(2))));
    _spriteMap[elem.at(0)].setRect(sf::IntRect(std::stoi(elem.at(4)), std::stoi(elem.at(5)), std::stoi(elem.at(6)), std::stoi(elem.at(7))));
}

void SFMLgraph::parse()
{
    std::vector<std::string> tab = cutString(_fromServer, ';');
    std::vector<std::string> tmp;

    for (size_t k = 1; k < 4 && tab.size() > k; k++) {
        tmp = cutString(tab.at(k), ',');
        if (!tmp.at(0).empty() && (std::strcmp(tmp.at(0).c_str(), "Player") || std::strcmp(tmp.at(0).c_str(), "Monster"))) {
            tmp.erase(tmp.begin());
            for (size_t i = 0; i < tmp.size(); i++)
                checkSprite(tmp.at(i));
        } else if (!tmp.at(0).empty() && std::strcmp(tmp.at(0).c_str(), "Score")) {
            tmp.erase(tmp.begin());
            _buttonMap["Score"]._text.setString(sf::String(tmp.at(0)));
        }
        tmp.clear();
    }
}


/* Displays the Main Menu */
void SFMLgraph::display()
{
    /* Clearing the WIndow */
    _window.clear();

    if (_screenDisplay == MainMenu) {

        _window.draw(_background["MenuBG"]._sprite);

        _window.draw(_fieldsMap["Nick"]._field);
        _window.draw(_fieldsMap["Nick"]._instruction);
        _window.draw(_fieldsMap["Nick"]._text);

        _window.draw(_fieldsMap["ServIP"]._field);
        _window.draw(_fieldsMap["ServIP"]._instruction);
        _window.draw(_fieldsMap["ServIP"]._text);

        _window.draw(_fieldsMap["Port"]._field);
        _window.draw(_fieldsMap["Port"]._instruction);
        _window.draw(_fieldsMap["Port"]._text);

        _window.draw(_buttonMap["Connect"]._btn);
        _window.draw(_buttonMap["Connect"]._text);
        _window.draw(_buttonMap["Quit"]._btn);
        _window.draw(_buttonMap["Quit"]._text);

    } else if (_screenDisplay == Join) {

        _window.draw(_background["MenuBG"]._sprite);

        _window.draw(_fieldsMap["RoomCode"]._field);
        _window.draw(_fieldsMap["RoomCode"]._instruction);

        _window.draw(_fieldsMap["RoomCode"]._text);
        _window.draw(_buttonMap["Create"]._btn);
        _window.draw(_buttonMap["Create"]._text);

        _window.draw(_buttonMap["Join"]._btn);
        _window.draw(_buttonMap["Join"]._text);
        _window.draw(_buttonMap["Quit"]._btn);
        _window.draw(_buttonMap["Quit"]._text);
    } else if (_screenDisplay == WaitingRoom) {

        _window.draw(_background["WrBG"]._sprite);

        _window.draw(_buttonMap["WaitingRoomCode"]._btn);
        _window.draw(_fieldsMap["RoomCode"]._text);

        if (_isAdmin) {
            _window.draw(_buttonMap["Start"]._btn);
            _window.draw(_buttonMap["Start"]._text);
        }

        size_t i = 0;
        while (i < _namesBox.size()) {
            _window.draw(_namesBox.at(i));
            _window.draw(_wrNames.at(i));
            i++;
        }
        _window.draw(_buttonMap["Quit"]._btn);
        _window.draw(_buttonMap["Quit"]._text);
    } else if (_screenDisplay == Game) {

        _window.draw(_background["WrBG"]._sprite);

        _window.draw(_buttonMap["Score"]._btn);
        _window.draw(_buttonMap["Score"]._text);

        // Displaying the Game's Sprites
        for (std::map<std::string, Sprite>::iterator it = _spriteMap.begin(); it != _spriteMap.end(); it++) {
            _window.draw(it->second._sprite);
        }
    }

    /* Displaying */
    _window.display();
}
