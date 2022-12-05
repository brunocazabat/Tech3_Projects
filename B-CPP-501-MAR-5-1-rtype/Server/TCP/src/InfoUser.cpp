/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** InfoUser
*/

#include "../include/InfoUser.hpp"

InfoUser::InfoUser()
{
}

InfoUser::~InfoUser()
{
}

std::string InfoUser::getUsername() const
{
    return (this->_username);
}

void InfoUser::setUsername(std::string username)
{
    this->_username = username;
}

std::string InfoUser::getRoom() const
{
    return (this->_room);
}

void InfoUser::setRoom(std::string room)
{
    this->_room = room;
}

bool InfoUser::getIsCreator() const
{
    return (this->_isCreator);
}

void InfoUser::setIsCreator(bool isCreator)
{
    this->_isCreator = isCreator;
}