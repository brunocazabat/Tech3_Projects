/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Speed
*/

#include "../include/Speed.hpp"

Speed::Speed(std::pair<int, int> value)
{
    _value = value;
}

Speed::~Speed()
{
}

void Speed::updateX(int x)
{
    _value.first = x;
}

void Speed::updateY(int y)
{
    _value.first = y;
}