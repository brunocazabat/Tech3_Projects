/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** ParserTcp
*/

#ifndef PARSERTCP_HPP_
#define PARSERTCP_HPP_

#include <iostream>
#include <map>
#include <functional>
#include "InfoUser.hpp"
#include "Room.hpp"
#include "ConnexionTcp.hpp"
#include "../../UDP/include/ServerUDP.hpp"
#include "../../Game/include/Game.hpp"
#include "../../Game/include/Thread.hpp"

#define ROOM_JOINED "100\n"
#define ROOM_CREATED "101"
#define LEAVE_ROOM "102\n"
#define EXIT "103\n"
#define LOGIN_SUCCESS "104\n"
#define GET_MEMBER_SUCCESS "105"
#define START_GAME "200;"
#define WELCOME "220\n"

#define NOT_LOGIN "500\n"
#define LOGIN_ERROR "501\n"
#define ALREADY_IN_ROOM "502\n"
#define ROOM_FULL "503\n"
#define ERROR_CODE_ROOM "504\n"
#define NO_ROOM "505\n"
#define NOT_IN_ROOM "506\n"
#define GET_MEMBER_ERROR "507\n"

class Room;
class ConnexionTcp;

class ParserTcp {
    public:
        ParserTcp();
        ParserTcp(std::vector<boost::shared_ptr<ConnexionTcp>> &listUsers, std::vector<Room> &listRoom, ServerUdp &servUdp, int id);
        ~ParserTcp();
        void setListRoom(std::vector<Room> &listRoom);
        std::string getArgument(std::string input, int i) const;
        std::string parse(std::string input);
        std::map<std::string, std::string (ParserTcp::*)(std::string input)> _command;
    protected:
        bool isCodeAvailable(std::string code);
        std::string generateRoomCode();
        std::string login(std::string input);
        std::string createRoom(std::string input);
        std::string joinRoom(std::string input);
        std::string leaveRoom(std::string input);
        std::string exit(std::string input);
        std::string getMemberRoom(std::string input);
        std::string startGame(std::string input);
        std::vector<Room> &_listRooms;
        std::vector<boost::shared_ptr<ConnexionTcp>> &_listUsers;
        ServerUdp &_servUdp;
        int _id;
    private:
};

#endif /* !PARSERTCP_HPP_ */