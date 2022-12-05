/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** FirstMob
*/

#ifndef FIRSTMOB_HPP_
#define FIRSTMOB_HPP_

#include "../../interfaces/IMonster.hpp"
#include "BasicProjectile.hpp"

class FirstMob: public IMonster {
    public:
        FirstMob();
        ~FirstMob();
        void setPos(int x, int y) override;
        void randVertSpeed();
        void update() override;
        void display() override;
        bool hit(int nb) override;
        int getDamage() override;
        std::pair<int, int> getPos() override;
        std::string getSprite() override;
        Rect getSpriteRect() override;
        bool isOnFire() override;
        std::shared_ptr<IDEntities> fire() override;

    private:
        int _count;
};

/*extern "C"
{
    IDEntities *entryPoint()
    {
        return (new FirstMob());
    }
}*/

#endif /* !FIRSTMOB_HPP_ */