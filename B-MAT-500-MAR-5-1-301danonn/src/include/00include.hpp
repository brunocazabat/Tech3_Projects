/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <list>
#include <stdio.h>
#include <string.h>

namespace dannon
{
    class bruh
    {
    private:
    protected:
    public:
        std::ifstream ifStream;
        std::vector<double> list;
        std::string line;
        std::string word;
        bruh();
        ~bruh();
        int     main(int ac, char **av);
        int     numb_check(const char *str);
        void    help(char *program);
        void    output();
        int     selection(std::vector<double> list);
        int     insertion(std::vector<double> list);
        int     bubbles(std::vector<double> list);
        int     quick(std::vector<double> list);
        int     merge(std::list<double> &list1, std::list<double> &list2);
        int     fusion(std::vector<double> list);
    };   
} 