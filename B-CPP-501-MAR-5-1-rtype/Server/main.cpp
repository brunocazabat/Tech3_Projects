/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** main
*/

#include "TCP/include/ServerTcp.hpp"
#include "UDP/include/ServerUDP.hpp"

int main(int argc, char **argv)
{
	std::srand(std::time(nullptr));
    try {
		boost::asio::io_service io_contextUdp;
		std::cout << "Starting UDP Server" << std::endl;
		ServerUdp gameserv(io_contextUdp, std::atoi(argv[2]));
		io_contextUdp.run();
        std::cout << "Starting TCP Server" << std::endl;
		boost::asio::io_context io_context;
		ServerTcp *server = new ServerTcp(io_context, std::atoi(argv[1]), gameserv);
		io_context.run();
	} catch (std::exception& e) { std::cerr << e.what() << std::endl; }

    return (0);
}