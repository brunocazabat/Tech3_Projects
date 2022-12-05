/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "00include.hpp"

int     dannon::bruh::quick(std::vector<double> list) {
    if (list.size() < 2)
        return (0);
    int n = 0;
    int pivot = 0;
    std::vector<double> left;
    std::vector<double> right;

    for (int i = 0; i < static_cast <int> (list.size()); ++i) {
        if (i != pivot) {
            ++n;
            if (list[i] < list[pivot])
                left.push_back(list[i]);
            if (list[i] >= list[pivot])
                right.push_back(list[i]);
        }
    }
    n += quick(left);
    n += quick(right);

    return (n);
}