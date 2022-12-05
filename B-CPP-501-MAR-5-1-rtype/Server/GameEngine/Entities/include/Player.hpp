/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../../interfaces/IPlayer.hpp"
#include "../include/PlayerProjectile.hpp"

class Player : public IPlayer {
    public:
        enum Colors {Cyan, Purple, Green, Red, Blue};
        Player(std::string name, std::pair<int, int> pos, Player::Colors color);
        ~Player();
        void move(char axis, int value) override;
        void update() override;
        void display() override;
        bool hit(int nb) override;
        std::pair<int, int> getPos() override;
        std::string getSprite() override;
        Rect getSpriteRect() override;
        bool isOnFire() override;
        std::shared_ptr<IDEntities> fire() override;
};

#endif /* !PLAYER_HPP_ */