/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Position
*/

#include "../include/Position.hpp"

Position::Position(std::pair<int, int> vect)
{
    _value = vect;
}

Position::~Position()
{
}

void Position::updateBySpeed(std::pair<int, int> vect)
{
    _value.first += vect.first;
    _value.second += vect.second;
}