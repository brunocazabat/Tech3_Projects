/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "00include.hpp"

int     dannon::bruh::bubbles(std::vector<double> list) {
    int n = 0;

    for (size_t j = list.size() - 2; j + 1 > 0; --j) {
        for (size_t i = 0; i < j + 1; ++i) {
            ++n;
            if (list[i] > list[i + 1]) {
                double tmp = list[i];
                list[i] = list[i + 1];
                list[i + 1] = tmp;
            }
        }
    }

    return (n);
}