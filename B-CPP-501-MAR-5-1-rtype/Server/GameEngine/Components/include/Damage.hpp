/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Damage
*/

#ifndef DAMAGE_HPP_
#define DAMAGE_HPP_

#include "../../interfaces/ITComponents.hpp"

class Damage: public ITComponents<int> {
    public:
        Damage(int value);
        ~Damage();
        Elem elem() const override {return (IElem::Damage);};
};

#endif /* !DAMAGE_HPP_ */