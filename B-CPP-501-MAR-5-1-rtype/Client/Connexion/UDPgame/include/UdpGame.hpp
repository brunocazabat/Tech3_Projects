/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>

#include <iostream>
#include <vector>

class UdpGame {
    public:
        UdpGame(boost::asio::io_service& io_service, int port);
        ~UdpGame();

        std::string read();
        void send(std::string data);

        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint receiver_endpoint;
        int _port;
};
