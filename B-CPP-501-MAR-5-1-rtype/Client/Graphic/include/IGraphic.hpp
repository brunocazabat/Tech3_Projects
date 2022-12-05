/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** Interface for Graphic
*/

#ifndef INTERFACE_GRAPHIC_
#define INTERFACE_GRAPHIC_

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <iostream>
#include "strs.hpp"

#include "../../Connexion/Interface/IClientTcp.hpp"
#include "../../Connexion/ClientTcp/include/BoostClientTcp.hpp"
#include "../../Connexion/UDPgame/include/UdpGame.hpp"

class IGraphic {
    public:
        ~IGraphic(){};

        /* Enums */
        enum _menuFocus {
            Nothing = -1,
            Nickname = 0,
            ServerIP = 1,
            Port = 2,
            RoomCode = 3
        };

        enum _screen {
            MainMenu = 10,
            WaitingRoom = 12,
            Join = 11,
            Game = 13
        };

        /** GETTERS **/

        /* Returns the Window's Width */
        int getWidth() const
        {
            return _width;
        }

        /* Returns the Window's Height */
        int getHeight() const
        {
            return _height;
        }

        /* Returns the Player's Nickname */
        std::string getNickname() const
        {
            return _nickname;
        }

        /* Returns the Max FPS */
        int getFPSLimit() const
        {
            return _fpsLimit;
        }

        /* Returns the state of the Game */
        int getGameState() const
        {
            return _screenDisplay;
        }

        /* Returns if the client is an Admin or not */
        bool isAdmin() const {
            return _isAdmin;
        }

        /* Returns if the client is connected to the server */
        bool isConnected() const {
            return _isConnected;
        }

        /* Virtuals */
        virtual bool isWindowOpened() const = 0;
        virtual void getMenuEvents() = 0;
        virtual void display() = 0;
        virtual void checkMouseMenu() = 0;
        virtual void displayNames() = 0;
        virtual void getGameEvents() = 0;
        virtual void setServerInput(std::string serv) {_fromServer = serv;};

    protected:
        int _width;
        int _height;
        int _fpsLimit;
        std::string _nickname;
        _menuFocus _menuUserFocus;
        _screen _screenDisplay;
        std::string _roomCodeString;
        bool _isAdmin;
        bool _isConnected;
        size_t _roomSize;
        std::vector<std::string> _wrNamesString;
        std::string _fromServer;

        IClientTcp *_client;
        UdpGame *_udpClient;

        bool _sent;

    private:

};

#endif /* !INTERFACE_GRAPHIC_ */
