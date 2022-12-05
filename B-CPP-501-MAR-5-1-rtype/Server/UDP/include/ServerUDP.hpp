/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** ServerUDP
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>

#include <iostream>
#include <vector>

class ServerUdp {
    public:
        ServerUdp(boost::asio::io_service& io_service, int port);
        ~ServerUdp();
    
        std::string read();
        void send(std::string data);
        int getPort() const;
        
        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint _remote;
        boost::asio::ip::udp::endpoint _endpoint;
        int _port;
};