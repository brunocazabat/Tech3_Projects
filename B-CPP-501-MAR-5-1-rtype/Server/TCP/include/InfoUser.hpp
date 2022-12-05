/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** InfoUser
*/

#ifndef INFOUSER_HPP_
#define INFOUSER_HPP_

#include <iostream>

class InfoUser {
    public:
        InfoUser();
        ~InfoUser();
        std::string getUsername() const;
        void setUsername(std::string username);
        std::string getRoom() const;
        void setRoom(std::string room);
        bool getIsCreator() const;
        void setIsCreator(bool isCreator);

    protected:
    private:
        std::string _username;
        std::string _room;
        bool _isCreator;
};

#endif /* !INFOUSER_HPP_ */
