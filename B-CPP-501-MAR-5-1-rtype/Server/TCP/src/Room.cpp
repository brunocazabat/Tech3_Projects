/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** Room
*/

#include "../include/Room.hpp"

Room::Room(std::string code): _code(code)
{
}

Room::~Room()
{
}

std::string Room::getCode() const
{
    return (this->_code);
}

void Room::addMember(boost::shared_ptr<ConnexionTcp> member)
{
    this->_listMember.push_back(member);
}

std::vector<boost::shared_ptr<ConnexionTcp>> &Room::getMember()
{
    return (this->_listMember);
}