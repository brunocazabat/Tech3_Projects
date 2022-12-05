/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Thread
*/

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include "../include/Game.hpp"

class Thread {
    public:
        Thread(size_t nb_players, ServerUdp &serv);
        ~Thread();
        void run();

    protected:
    private:
        std::thread *_thread;
        size_t _nbPlayers;
        ServerUdp &_serv;
        Game *_game;
};

#endif /* !THREAD_HPP_ */