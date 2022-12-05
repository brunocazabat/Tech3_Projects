/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** ServerTCP
*/

#ifndef SERVERTCP_HPP_
#define SERVERTCP_HPP_

#include <iostream>
#include <vector>
#include "ConnexionTcp.hpp"
#include "Room.hpp"
#include "../../UDP/include/ServerUDP.hpp"

class ServerTcp {
    public:
        ServerTcp(boost::asio::io_service& io_service, int port, ServerUdp &servUdp);
        ~ServerTcp();
    protected:
    private:
        void startAccept();
        void handleAccept(ConnexionTcp::pointer new_connection, const boost::system::error_code& error);
        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::io_context &_io_context;
        std::vector<ConnexionTcp::pointer> _listUsers;
        std::vector<Room> _listRooms;
        ServerUdp &_servUdp;
};

#endif /* !SERVERTCP_HPP_ */