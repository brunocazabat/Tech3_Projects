/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "00include.hpp"

int     dannon::bruh::merge(std::list<double> &list1, std::list<double> &list2) {
    int n = 0;
    std::list<double>::iterator it1 = list1.begin();
    std::list<double>::iterator it_end1 = list1.end();
    std::list<double>::iterator it2 = list2.begin();
    std::list<double>::iterator it_end2 = list2.end();

    while (it1 != it_end1 && it2 != it_end2)
    {
        ++n;
        if (*it2 < *it1)
        {
            std::list<double>::iterator next = it2;
            it1._M_node->_M_transfer(it2._M_node, (++next)._M_node);
            it2 = next;
        }
        else
            ++it1;
    }
    if (it2 != it_end2)
        it_end1._M_node->_M_transfer(it2._M_node, it_end2._M_node);

    return (n);
}

int     dannon::bruh::fusion(std::vector<double> list) {
    int n = 0;
    std::vector<std::list<double> > list2;

    for (size_t i = 0; i < list.size(); ++i) {
        if (i % 2 == 0) {
            std::list<double> tmp;
            if (i + 1 >= list.size())
                tmp.push_back(list[i]);
            else {
                tmp.push_back(std::min(list[i], list[i + 1]));
                tmp.push_back(std::max(list[i], list[i + 1]));
            }
            list2.push_back(tmp);
        }
    }
    while (list2.size() > 1) {
        for (int i = 0; i < static_cast <int> (list2.size()); i += 2)
            if (i + 1 < static_cast <int> (list2.size()))
                n += merge(list2[i], list2[i + 1]);
        for (int i = 1; i < static_cast <int> (list2.size()); ++i) {
            std::vector<std::list<double> >::iterator it = list2.begin();
            for (int j = 0; j < i; ++j)
                ++it;
            list2.erase(it);
        }
    }

    return (n + 2);
}