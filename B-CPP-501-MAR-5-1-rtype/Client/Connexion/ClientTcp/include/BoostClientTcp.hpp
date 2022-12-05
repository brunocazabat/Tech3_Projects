/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** ClientTcp
*/

#ifndef BOOSTCLIENTTCP_HPP_
#define BOOSTCLIENTTCP_HPP_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include "../../Interface/IClientTcp.hpp"

class BoostClientTcp : public IClientTcp {
    public:
        BoostClientTcp(std::string host, int port);
        ~BoostClientTcp();
        void send(std::string message);
        std::string read(bool notif);

    protected:
    private:
        boost::asio::io_service _ios;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::socket _socket;
};

#endif /* !BOOSTCLIENTTCP_HPP_ */
