/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** PlayerProjectile
*/

#ifndef PLAYERPROJECTILE_HPP_
#define PLAYERPROJECTILE_HPP_

#include "../../interfaces/IProjectile.hpp"

class PlayerProjectile : public IProjectile {
    public:
        enum TYPES {Classic};
        PlayerProjectile(std::pair<int, int> pos, PlayerProjectile::TYPES type);
        ~PlayerProjectile();
        void update() override;
        void display() override;
        bool hit(int nb) override;
        int getDamage() override;
        bool canBeHit() override {return (false);};
        std::pair<int, int> getPos() override;
        std::string getSprite() override;
        Rect getSpriteRect() override;
    private:
};

#endif /* !PLAYERPROJECTILE_HPP_ */