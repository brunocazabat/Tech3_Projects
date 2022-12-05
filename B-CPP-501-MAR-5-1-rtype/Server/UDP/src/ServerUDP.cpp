/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** ServerUDP
*/

#include "../include/ServerUDP.hpp"

ServerUdp::ServerUdp(boost::asio::io_service &io_service, int port) : _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), port))
{
    _port = port;
}

ServerUdp::~ServerUdp()
{
    _socket.close();
}

std::string ServerUdp::read()
{
    //WAIT FOR ORDERS FROM CLIENT
    boost::array<char, 512> recv_buf;

	_socket.receive_from(boost::asio::buffer(recv_buf), _remote);
    _endpoint = _remote;
    std::cout << _remote << ": " << recv_buf.data() << "(Readed from server)\n";
    return (recv_buf.data());
}

void ServerUdp::send(std::string data)
{
    //SEND BACK SCORE/POS/INFO(data) TO CLIENT

    data = "Server;" + data;

    boost::shared_ptr<std::string> message(new std::string(data));

    _socket.send_to(boost::asio::buffer(*message), _endpoint);
    std::cout << _endpoint << ": " << *message << "(Sended from server)\n";
}

int ServerUdp::getPort() const
{
    return (_port);
}