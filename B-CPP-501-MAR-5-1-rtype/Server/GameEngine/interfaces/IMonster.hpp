/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** IMonster
*/

#ifndef IMONSTER_HPP_
#define IMONSTER_HPP_

#include "IEntities.hpp"

class IMonster : public IEntities {
    public:
        virtual ~IMonster() = default;
        virtual void updatePlayerPos(std::vector<std::pair<int, int>> pos) {_playerPos = pos;};
        virtual int getDamage() = 0;
        virtual void setPos(int x, int y) = 0;
    protected:
        std::vector<std::pair<int, int>> _playerPos;
};

#endif /* !IMONSTER_HPP_ */