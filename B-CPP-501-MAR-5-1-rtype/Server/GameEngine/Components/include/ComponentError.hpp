/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** ComponentError
*/

#ifndef COMPONENTERROR_HPP_
#define COMPONENTERROR_HPP_

#include <iostream>

class ComponentError {
    public:
        ComponentError(std::string);
        ~ComponentError();

    protected:
    private:
        std::string _err;
};

#endif /* !COMPONENTERROR_HPP_ */