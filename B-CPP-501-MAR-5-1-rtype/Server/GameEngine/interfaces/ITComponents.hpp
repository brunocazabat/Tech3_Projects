/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** ITComponent
*/

#ifndef ITCOMPONENT_HPP_
#define ITCOMPONENT_HPP_

#include "IComponents.hpp"

template<typename T>
class ITComponents: public IComponents {
    public:
        virtual ~ITComponents() = default;
        virtual void update(T val) {_value = val;};
        virtual T get() {return _value;};
    protected:
        T _value;
};

#endif /* !ITCOMPONENT_HPP_ */
