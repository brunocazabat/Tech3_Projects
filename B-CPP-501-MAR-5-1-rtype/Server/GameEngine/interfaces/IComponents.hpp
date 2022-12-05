/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Icomponents
*/

#ifndef ICOMPONENTS_HPP_
#define ICOMPONENTS_HPP_

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <typeinfo>
#include "IFComponents.hpp"

class IComponents {
    public:
        enum Elem {AI, Damage, Life, Position, Speed, Sprite, NotFound};
        typedef IComponents::Elem IElem;
        virtual Elem elem() const {return IElem::NotFound;};
        virtual ~IComponents() = default;
};

#endif /* !ICOMPONENTS_HPP_ */