/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Speed
*/

#ifndef SPEED_HPP_
#define SPEED_HPP_

#include "../../interfaces/ITComponents.hpp"

class Speed: public ITComponents<std::pair<int, int>> {
    public:
        Speed(std::pair<int, int> value);
        ~Speed();
        Elem elem() const override {return (IElem::Speed);};
        void updateX(int x);
        void updateY(int y);

    protected:
    private:
};

#endif /* !SPEED_HPP_ */