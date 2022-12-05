/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** BasicProjectile
*/

#ifndef BASICPROJECTILE_HPP_
#define BASICPROJECTILE_HPP_

#include "../../interfaces/IProjectile.hpp"

class BasicProjectile: public IProjectile {
    public:
        BasicProjectile(std::pair<int, int> pos, int damages);
        ~BasicProjectile();
        void update() override;
        void display() override;
        bool hit(int nb) override;
        int getDamage() override;
        bool canBeHit() override {return (false);};
        std::pair<int, int> getPos() override;
        std::string getSprite() override;
        Rect getSpriteRect() override;
};

#endif /* !BASICPROJECTILE_HPP_ */