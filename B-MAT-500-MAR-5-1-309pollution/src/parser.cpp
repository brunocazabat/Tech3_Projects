/*
** EPITECH PROJECT, 2021
** 300pollution
** File description:
** parser
*/

#include "parser.hpp"


bool isNumber(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
        if (std::isdigit(str[i]) == false)
            return false;
    return true;
}

bool isFloat(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
        if (std::isdigit(str[i]) == false && str[i] != '.')
            return false;
    return true;
}

Parser::Parser(char **av)
{
    if (isNumber(av[1]) == false)
        exit(84);
    if (isFloat(av[3]) == false)
        exit(84);
    if (isFloat(av[4]) == false)
        exit(84);
}


void Parser::printResults()
{
    std::cout << "results" << std::endl;
}
