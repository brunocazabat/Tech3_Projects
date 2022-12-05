/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** IProjectile
*/

#ifndef IPROJECTILE_HPP_
#define IPROJECTILE_HPP_

#include "IDEntities.hpp"

class IProjectile : public IDEntities {
    public:
        virtual ~IProjectile() = default;
        virtual int getDamage() = 0;
        virtual bool canBeHit() = 0;
};

#endif /* !IPROJECTILE_HPP_ */