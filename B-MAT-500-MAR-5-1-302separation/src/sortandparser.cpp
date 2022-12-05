/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "include/include.hpp"

int     separation::bruh::comp_twonames(char **av)
{
    if (!strcmp(av[2], av[3]))
        return (final_output(av, 0, 1));
    if (!nameExists(av[2]) || !nameExists(av[3]))
        return (final_output(av, 0, 2));
    int id = nameId(av[2]);
    done.push_back(id);
    search(id, av[3], -1);
    if (dat.size() == 0)
        return (final_output(av, -1, 1));
    else {
        int min = dat[0];
        for (long unsigned int i = 0; i < dat.size(); i++)
            if (dat[i] < min)
                min = dat[i];
        return (final_output(av, min, 1));
    }
}

int     separation::bruh::listnameparser(void)
{
    if (line.find(delim) != std::string::npos) {
        size_t pos = 0;
        std::string token;
        while ((pos = line.find(delim)) != std::string::npos) {
            token = line.substr(0, pos);
            if (!nameExists(token))
                names.push_back(token);
            l1.push_back(token);
            line.erase(0, pos + delim.length());
        }
        if (!nameExists(line))
            names.push_back(line);
        l2.push_back(line);
    }
    return (0);
}

void    separation::bruh::firstnamesort(void)
{
    for (long unsigned int y = 0; y < names.size(); y++) {
        std::vector<std::string> vec;
        for (long unsigned int i = 0; i < l1.size() && i < l2.size(); i++) {
            if (names[y] == l1[i])
                vec.push_back(l2[i]);
            else if (names[y] == l2[i])
                vec.push_back(l1[i]);
        }
        links.push_back(vec);
    }
}

void    separation::bruh::dualnamesort(void)
{
    bool printed = false;
    for (int i = names.size() - 1; i >= 0; i--)
        std::cout << names[i] << std::endl;
    std::cout << std::endl;
    for (int x = links.size() - 1; x >= 0; x--) {
        for (int k = names.size() - 1; k >= 0; k--) {
            for (int y = links[x].size() - 1; y >= 0; y--)
                if (links[x][y].compare(names[k]) == 0) {
                    std::cout << "1";
                    if (k != 0)
                        std::cout << " ";
                    printed = true;
                    break;
                }
            if (!printed) {
                std::cout << "0";
                if (k != 0)
                std::cout << " ";   
            }
            printed = false;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}