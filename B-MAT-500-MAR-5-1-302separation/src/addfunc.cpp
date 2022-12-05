/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "include/include.hpp"

int         separation::bruh::nameId(std::string name)
{
    for (long unsigned int i = 0; i < names.size(); i++)
        if (!names[i].compare(name))
            return (i);
    return (-1);
}

bool        separation::bruh::isDone(int id)
{
    for (long unsigned int i = 0; i < done.size(); i++)
        if(done[i] == id)
            return (true);
    return (false);
}

void        separation::bruh::search(int id, std::string person, int value)
{
    std::vector<std::string> l = links[id];
    for (long unsigned int i = 0; i < l.size(); i++)
        if (!l[i].compare(person))
            dat.push_back(value + 1);
    for (long unsigned int i = 0; i < l.size(); i++) {
        int _id = nameId(l[i]);
        if (!isDone(_id)) {
            done.push_back(_id);
            search(_id, person, value + 1);
        }
    }
}

bool        separation::bruh::validNb(std::string value)
{
    for (long unsigned int i = 0; i < value.size(); i++)
        if(!(value[i] >= '0' && value[i] <= '9'))
            return (false);
    return (true);
}

bool        separation::bruh::nameExists(std::string name)
{
    for (long unsigned int i = 0; i < names.size(); i++)
        if (names[i] == name)
            return (true);
    return (false);
}