/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** ConnexionTcp
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <algorithm>
#include "ParserTcp.hpp"
#include "InfoUser.hpp"
#include "Room.hpp"
#include "../../UDP/include/ServerUDP.hpp"

class Room;
class ParserTcp;

class ConnexionTcp : public boost::enable_shared_from_this<ConnexionTcp> {  
    public:
        typedef boost::shared_ptr<ConnexionTcp> pointer;
	    static pointer create(boost::asio::io_context &ios, std::vector<ConnexionTcp::pointer> &listUsers, std::vector<Room> &listRooms, ServerUdp &servUdp, int id)
        {
            return pointer(new ConnexionTcp(ios, listUsers, listRooms, servUdp, id));
        }
        ~ConnexionTcp();
        boost::asio::ip::tcp::socket &socket();
        void start();
        InfoUser &getInfoUser();
        int getId() const;
        std::vector<ConnexionTcp::pointer> &getListUsers() const;
        std::vector<Room> &getListRooms() const;
        void sendTcp(std::string message);
    protected:
    private:
        ConnexionTcp(boost::asio::io_context &io_context, std::vector<ConnexionTcp::pointer> &listUsers, std::vector<Room> &listRooms, ServerUdp &servUdp, int id);
        void handleReceive(const boost::system::error_code &error);
        void handleSend(const boost::system::error_code &error);
        boost::asio::ip::tcp::socket _socket;
	    std::string _send;
        boost::asio::streambuf _receive;
        ParserTcp *_parser;
        InfoUser _infoUser;
        std::vector<ConnexionTcp::pointer> &_listUsers;
        std::vector<Room> &_listRooms;
        int _id;
};