/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "00include.hpp"

int     dannon::bruh::insertion(std::vector<double> list) {
    int n = 0;
    std::list<double> list2;

    for (size_t i = 0; i < list.size(); ++i) {
        if (list2.empty())
            list2.push_back(list[i]);
        else {
            std::list<double>::iterator it = list2.begin();
            while (it != list2.end()) {
                ++n;
                if (*it > list[i]) {
                    list2.insert(it, list[i]);
                    break ;
                }
                ++it;
            }
            if (it == list2.end())
                list2.push_back(list[i]);
        }
    }

    return (n);
}