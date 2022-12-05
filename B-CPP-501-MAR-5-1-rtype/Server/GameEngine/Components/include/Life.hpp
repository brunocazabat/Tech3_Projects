/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Life
*/

#ifndef LIFE_HPP_
#define LIFE_HPP_

#include "../../interfaces/ITComponents.hpp"

class Life: public ITComponents<int> {
    public:
        Life(int value);
        ~Life();
        Elem elem() const override {return (IElem::Life);};
        void operator-=(int nb);

    protected:
    private:
};

#endif /* !LIFE_HPP_ */