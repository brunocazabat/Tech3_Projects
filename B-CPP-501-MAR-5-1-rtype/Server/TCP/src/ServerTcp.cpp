/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** ServerTCP
*/

#include "../include/ServerTcp.hpp"

ServerTcp::ServerTcp(boost::asio::io_context &io_context, int port, ServerUdp &servUdp):_io_context(io_context) , _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), _servUdp(servUdp)
{
    this->startAccept();
}

ServerTcp::~ServerTcp()
{
}

void ServerTcp::startAccept()
{
    static int id = 1;
    ConnexionTcp::pointer new_connection = ConnexionTcp::create(_io_context, _listUsers, _listRooms, _servUdp, id);

    id = id + 1;
    _acceptor.async_accept(new_connection->socket(), boost::bind(&ServerTcp::handleAccept, this, new_connection, boost::asio::placeholders::error));
}

void ServerTcp::handleAccept(ConnexionTcp::pointer new_connection, const boost::system::error_code& error)
{
    if (!error)
    {
		std::cout << "new client" << std::endl;
        _listUsers.push_back(new_connection);
      	new_connection->start();
    }
    startAccept();
}