/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** ClientTcp
*/

#include "../include/BoostClientTcp.hpp"

BoostClientTcp::BoostClientTcp(std::string host, int port):_endpoint(boost::asio::ip::address::from_string(host), port), _socket(_ios)
{
	_socket.connect(_endpoint);
}

BoostClientTcp::~BoostClientTcp()
{
    _socket.close();
}

void BoostClientTcp::send(std::string message)
{
    _socket.send(boost::asio::buffer(message, message.length()));
}

std::string BoostClientTcp::read(bool notif)
{
    std::string message;
    boost::array<char, 128> buf;
    size_t pos = 0;

    if (notif && _socket.available() < 1) {
        return ("");
    }
    _socket.receive(boost::asio::buffer(buf));
    message = buf.data();
    pos = message.find('\n', 0);
    message = message.substr(0, pos + 1);
    return (message);
}