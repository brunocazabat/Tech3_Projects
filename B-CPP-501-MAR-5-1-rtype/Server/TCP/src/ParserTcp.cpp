/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** ParserTcp
*/

#include "../include/ParserTcp.hpp"

ParserTcp::ParserTcp(std::vector<boost::shared_ptr<ConnexionTcp>> &listUsers, std::vector<Room> &listRoom, ServerUdp &servUdp, int id): _listUsers(listUsers), _listRooms(listRoom), _servUdp(servUdp), _id(id)
{
    _command["LOGIN"] = &ParserTcp::login;
    _command["CREATEROOM"] = &ParserTcp::createRoom;
    _command["JOINROOM"] = &ParserTcp::joinRoom;
    _command["LEAVEROOM"] = &ParserTcp::leaveRoom;
    _command["EXIT"] = &ParserTcp::exit;
    _command["STARTGAME"] = &ParserTcp::startGame;
    _command["GETMEMBERROOM"] = &ParserTcp::getMemberRoom;
}

ParserTcp::~ParserTcp()
{
}

void ParserTcp::setListRoom(std::vector<Room> &listRoom)
{
    this->_listRooms = listRoom;
}

std::string ParserTcp::getArgument(std::string input, int i) const
{
    std::string response;
    size_t j = 0;

    while (i > 1) {
        while (input.size() > j && (input.at(j) != ';' && input.at(j) != '\n')) {
            j = j + 1;
        }
        j = j + 1;
        i = i - 1;
    }
    while (input.size() > j && (input.at(j) != ';' && input.at(j) != '\n')) {
        response.push_back(input.at(j));
        j = j + 1;
    }
    return (response);
}

bool ParserTcp::isCodeAvailable(std::string code)
{
    if (code.size() < 5)
        return (false);
    for (int i = 0; i < _listRooms.size(); i++) {
        if (_listRooms.at(i).getCode() == code)
            return (false);
    }
    return (true);
}

std::string ParserTcp::generateRoomCode()
{
    std::string code = "";
    char letter;

    while (!isCodeAvailable(code)) {
        code = "";
        for (int i = 0; i < 5; i++) {
            letter = std::rand() % 26 + 65;
            code.push_back(letter);
        }
    }
    return (code);
}

std::string ParserTcp::parse(std::string input)
{
    std::string argument = getArgument(input, 1);
    std::string toSend;

    auto it = this->_command.find(argument);
    if (it != this->_command.end()) {
        toSend = (this->*it->second)(input);
    } else {
        return ("ERROR\n");
    }
    return (toSend);
}

std::string ParserTcp::login(std::string input)
{
    std::string username = getArgument(input, 2);
    if (username.size() < 1)
        return (LOGIN_ERROR);
    for (size_t i = 0; i < _listUsers.size(); i++) {
        if (_listUsers.at(i)->getId() == _id) {
            _listUsers.at(i)->getInfoUser().setUsername(username);
            return (LOGIN_SUCCESS);
        }
    }
    return ("No user\n");
}

std::string ParserTcp::createRoom(std::string input)
{
    std::string code;

    for (size_t i = 0; i < _listUsers.size(); i++) {
        if (_listUsers.at(i)->getId() == _id) {
            if (_listUsers.at(i)->getInfoUser().getUsername().size() < 1)
                return (NOT_LOGIN);
            else if (_listUsers.at(i)->getInfoUser().getRoom().size() > 0)
                return (ALREADY_IN_ROOM);
            break;
        }
    }
    code = generateRoomCode();
    Room room(code);
    for (size_t i = 0; i < _listUsers.size(); i++) {
        if (_listUsers.at(i)->getId() == _id) {
            room.addMember(_listUsers.at(i));
            _listRooms.push_back(room);
            _listUsers.at(i)->getInfoUser().setIsCreator(true);
            _listUsers.at(i)->getInfoUser().setRoom(code);
        }
    }
    code = ROOM_CREATED + std::string(";") + code + std::string("\n");
    return (code);
}

std::string ParserTcp::joinRoom(std::string input)
{
    for (size_t i = 0; i < _listUsers.size(); i++) {
        if (_listUsers.at(i)->getId() == _id) {
            if (_listUsers.at(i)->getInfoUser().getUsername().size() < 1)
                return (NOT_LOGIN);
            else if (_listUsers.at(i)->getInfoUser().getRoom().size() > 0)
                return (ALREADY_IN_ROOM);
            break;
        }
    }
    std::string code = getArgument(input, 2);
    for (size_t i = 0; i < _listRooms.size(); i++) {
        if (_listRooms.at(i).getCode() == code) {
            if (_listRooms.at(i).getMember().size() < 4) {
                for (size_t j = 0; j < _listUsers.size(); j++) {
                    if (_listUsers.at(j)->getId() == _id) {
                        _listRooms.at(i).addMember(_listUsers.at(j));
                        _listUsers.at(j)->getInfoUser().setRoom(code);
                        _listUsers.at(j)->getInfoUser().setIsCreator(false);
                        return (ROOM_JOINED);
                    }
                }
            } else {
                return (ROOM_FULL);
            }
        } else {
            return (ERROR_CODE_ROOM);
        }
    }
    return (NO_ROOM);
}

std::string ParserTcp::leaveRoom(std::string input)
{
    for (size_t i = 0; i < _listUsers.size(); i++) {
        if (_listUsers.at(i)->getId() == _id) {
            if (_listUsers.at(i)->getInfoUser().getUsername().size() < 1)
                return (NOT_LOGIN);
            else if (_listUsers.at(i)->getInfoUser().getRoom().size() < 1)
                return (NOT_IN_ROOM);
            else {
                for (size_t j = 0; j < _listRooms.size(); j++) {
                    if (_listRooms.at(j).getCode() == _listUsers.at(i)->getInfoUser().getRoom()) {
                        _listUsers.at(i)->getInfoUser().setRoom("");
                        if (_listRooms.at(j).getMember().size() == 1) {
                            _listRooms.erase(_listRooms.begin() + j);
                            return (LEAVE_ROOM);
                        }
                        for (size_t k = 0; k < _listRooms.at(j).getMember().size(); k++) {
                            if (_listRooms.at(j).getMember().at(k)->getId() == _listUsers.at(i)->getId()) {
                                _listRooms.at(j).getMember().erase(_listRooms.at(j).getMember().begin() + k);
                                _listRooms.at(j).getMember().at(0)->getInfoUser().setIsCreator(true);
                            }
                        }
                        _listUsers.at(i)->getInfoUser().setIsCreator(false);
                        return (LEAVE_ROOM);
                    }
                }
            }
        }
    }
    return (LEAVE_ROOM);
}

std::string ParserTcp::exit(std::string input)
{
    for (size_t i = 0; i < _listUsers.size(); i++) {
        if (_listUsers.at(i)->getId() == _id) {
            if (_listUsers.at(i)->getInfoUser().getRoom().size() > 0) {
                for (size_t j = 0; j < _listRooms.size(); j++) {
                    if (_listRooms.at(j).getCode() == _listUsers.at(i)->getInfoUser().getRoom()) {
                        _listUsers.at(i)->getInfoUser().setRoom("");
                        if (_listRooms.at(j).getMember().size() == 1) {
                            _listRooms.erase(_listRooms.begin() + j);
                            return (EXIT);
                        }
                        for (size_t k = 0; k < _listRooms.at(j).getMember().size(); k++) {
                            if (_listRooms.at(j).getMember().at(k)->getId() == _listUsers.at(i)->getId()) {
                                _listRooms.at(j).getMember().erase(_listRooms.at(j).getMember().begin() + k);
                                _listRooms.at(j).getMember().at(0)->getInfoUser().setIsCreator(true);
                            }
                        }
                        _listUsers.at(i)->getInfoUser().setIsCreator(false);
                        return (EXIT);
                    }
                }
            }
        }
    }
    return (EXIT);
}

std::string ParserTcp::startGame(std::string input)
{
    for (size_t i = 0; i < _listUsers.size(); i++) {
        if (_listUsers.at(i)->getId() == _id) {
            for (size_t j = 0; j < _listRooms.size(); j++) {
                if (_listRooms.at(i).getCode() == _listUsers.at(i)->getInfoUser().getRoom()) {
                    Thread *thread = new Thread(_listRooms.at(i).getMember().size(), _servUdp);
                    for (size_t k = 0; k < _listRooms.at(i).getMember().size(); k++) {
                        if (k != 0) {
                            _listRooms.at(i).getMember().at(k)->sendTcp(START_GAME + std::to_string(_servUdp.getPort()) + "\n");
                        }
                    }
                }
            }
        }
    }
    return (START_GAME + std::to_string(_servUdp.getPort()) + "\n");
}

std::string ParserTcp::getMemberRoom(std::string input)
{
    std::string result = GET_MEMBER_ERROR;
    
    for (size_t i = 0; i < _listUsers.size(); i++) {
        if (_listUsers.at(i)->getId() == _id) {
            for (size_t j = 0; j < _listRooms.size(); j++) {
                std::cout << _listRooms.size() << std::endl;
                if (_listRooms.at(j).getCode() == _listUsers.at(i)->getInfoUser().getRoom()) {
                    result = GET_MEMBER_SUCCESS;
                    for (size_t k = 0; k < _listRooms.at(j).getMember().size(); k++) {
                        result = result + ";" + _listRooms.at(j).getMember().at(k)->getInfoUser().getUsername();
                    }
                    result = result + "\n";
                    return (result);
                }
            }
        }
    }
    return (result);
}