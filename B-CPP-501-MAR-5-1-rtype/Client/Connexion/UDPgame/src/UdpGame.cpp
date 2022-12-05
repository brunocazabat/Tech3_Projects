/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "../include/UdpGame.hpp"

using boost::asio::ip::udp;

UdpGame::UdpGame(boost::asio::io_service &io_service, int port): _socket(io_service)
{
    _socket.open(udp::v4());
    _port = port;
}

UdpGame::~UdpGame()
{
    _socket.close();
}

std::string UdpGame::read()
{
    //WAIT FOR INFO FROM SERV
    boost::array<char, 256> recv_buf;
    udp::endpoint sender_endpoint = udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), _port);

	_socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
    std::cout << sender_endpoint << ": " << recv_buf.data() << "(readed from client)\n";
    return (recv_buf.data());
}

void UdpGame::send(std::string data)
{
    //SEND BACK COMMANDS TO SERV

    boost::shared_ptr<std::string> message(new std::string(data));

    _socket.send_to(boost::asio::buffer(*message), udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), _port));
    std::cout << udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), _port) << ": " << *message << "(Sended from client)\n";
}