/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** Room
*/

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <iostream>
#include <vector>
#include "ConnexionTcp.hpp"

class ConnexionTcp;

class Room {
    public:
        Room(std::string code);
        ~Room();
        std::string getCode() const;
        void addMember(boost::shared_ptr<ConnexionTcp> member);
        std::vector<boost::shared_ptr<ConnexionTcp>> &getMember();

    protected:
    private:
        std::string _code;
        std::vector<boost::shared_ptr<ConnexionTcp>> _listMember;
};

#endif /* !ROOM_HPP_ */
