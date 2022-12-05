/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Life
*/

#include "../include/Life.hpp"

Life::Life(int value)
{
    _value = value;
}

Life::~Life()
{
}

void Life::operator-=(int nb)
{
    _value -= nb;
}