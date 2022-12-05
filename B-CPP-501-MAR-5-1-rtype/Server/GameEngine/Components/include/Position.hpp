/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include "../../interfaces/ITComponents.hpp"

class Position: public ITComponents<std::pair<int, int>> {
    public:
        Position(std::pair<int, int> vect);
        ~Position();
        Elem elem() const override {return (IElem::Position);};
        void updateBySpeed(std::pair<int, int> vect);

    protected:
    private:
};

#endif /* !POSITION_HPP_ */