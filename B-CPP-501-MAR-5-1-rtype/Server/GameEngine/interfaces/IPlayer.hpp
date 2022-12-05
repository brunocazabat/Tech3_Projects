/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** IPlayer
*/

#ifndef IPLAYER_HPP_
#define IPLAYER_HPP_

#include "IEntities.hpp"

class IPlayer : public IEntities {
    public:
        virtual ~IPlayer() = default;
        virtual void move(char axis, int value) = 0;
    protected:
        int _count;
};

#endif /* !IPLAYER_HPP_ */