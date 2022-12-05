/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "00include.hpp"

int     dannon::bruh::selection(std::vector<double> list) {
    int pos = 0;

    for (size_t bruh = 0; bruh < list.size() - 1; ++bruh) {
        size_t min = bruh;
        for (size_t j = bruh + 1; j < list.size(); ++j) {
            if (list[min] > list[j])
                min = j;
            ++pos;
        }
        if (min != bruh) {
            double tmp = list[min];
            list[min] = list[bruh];
            list[bruh] = tmp;
        }
    }

    return pos;
}