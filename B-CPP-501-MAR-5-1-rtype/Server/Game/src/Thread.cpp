/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Thread
*/

#include "../include/Thread.hpp"

Thread::Thread(size_t nb_players, ServerUdp &serv): _nbPlayers(nb_players), _serv(serv)
{
    _thread = new std::thread(&Thread::run, this);
}

Thread::~Thread()
{
    if (_thread->joinable())
		_thread->join();
}

void Thread::run()
{
    _game = new Game(_nbPlayers, _serv);
}