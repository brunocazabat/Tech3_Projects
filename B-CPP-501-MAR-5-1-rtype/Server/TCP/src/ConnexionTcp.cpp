/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** ConnexionTcp
*/

#include "../include/ConnexionTcp.hpp"

ConnexionTcp::ConnexionTcp(boost::asio::io_context &io_context, std::vector<ConnexionTcp::pointer> &listUsers, std::vector<Room> &listRooms, ServerUdp &servUdp, int id): _socket(io_context), _listUsers(listUsers), _listRooms(listRooms), _parser(new ParserTcp(listUsers, listRooms, servUdp, id)), _id(id)
{
}

ConnexionTcp::~ConnexionTcp()
{
	delete(_parser);
}

boost::asio::ip::tcp::socket &ConnexionTcp::socket()
{
	return this->_socket;
}

void ConnexionTcp::start()
{
	this->_send = WELCOME;
	boost::asio::async_write(this->_socket, boost::asio::buffer(this->_send), boost::bind(&ConnexionTcp::handleReceive, shared_from_this(), boost::asio::placeholders::error));
}	
					
void ConnexionTcp::handleReceive(const boost::system::error_code &error)
{
	this->_send = "";
	boost::asio::async_read_until(this->_socket, _receive, '\n', boost::bind(&ConnexionTcp::handleSend, shared_from_this(), boost::asio::placeholders::error));
}

void ConnexionTcp::handleSend(const boost::system::error_code &error)
{
	std::string str(boost::asio::buffers_begin(_receive.data()), boost::asio::buffers_end(_receive.data()));
	for(unsigned int i=0; i < str.size(); i++) {
    	if(str[i] == '\r' || str[i] == '\n') {
        	str.erase(i,1);
			i = i - 1;
    	}
   	}
	std::cout << str << std::endl;
	_receive.consume(_receive.size());
	this->_send = this->_parser->parse(str);
	if (this->_send == "Exit\n") {
		for (size_t i = 0; i < _listUsers.size(); i++) {
			if (_listUsers.at(i)->getId() == _id) {
				_listUsers.erase(_listUsers.begin() + i);
			}
		}
		return;
	}
	boost::asio::async_write(this->_socket, boost::asio::buffer(this->_send), boost::bind(&ConnexionTcp::handleReceive, shared_from_this(), boost::asio::placeholders::error));
}

InfoUser &ConnexionTcp::getInfoUser()
{
	return (this->_infoUser);
}

int ConnexionTcp::getId() const
{
	return (this->_id);
}

std::vector<ConnexionTcp::pointer> &ConnexionTcp::getListUsers() const
{
	return (this->_listUsers);
}

std::vector<Room> &ConnexionTcp::getListRooms() const
{
	return (this->_listRooms);
}

void ConnexionTcp::sendTcp(std::string message)
{
	boost::asio::write(this->_socket, boost::asio::buffer(message));
}