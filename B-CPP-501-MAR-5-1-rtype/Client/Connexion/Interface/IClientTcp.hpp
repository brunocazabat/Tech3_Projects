/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** IClientTcp
*/

#ifndef ICLIENTTCP_HPP_
#define ICLIENTTCP_HPP_

#include <iostream>

class IClientTcp {
    public:
        virtual ~IClientTcp() = default;
        virtual void send(std::string message) = 0;
        virtual std::string read(bool notif) = 0;

    protected:
    private:
};

#endif /* !ICLIENTTCP_HPP_ */
