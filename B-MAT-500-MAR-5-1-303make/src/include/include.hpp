/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <string>
#include <map>

namespace make
{
    class bruh
    {
    /* components dump */
    public:
        std::map<std::string, std::vector<std::string>>     mapper;
        std::map<std::string, std::string>                  mapper2;
        std::map<std::string, std::vector<std::string>> _mapper;
        std::map<std::string, std::string>              _mapper2;
        std::vector<std::vector<int>>                   matrix;
        std::vector<std::string>                        RightTab;
        std::vector<std::string>                        LeftTab;
        std::vector<std::string>                        arbre;
        std::vector<std::string>                        loopChecker;
        std::vector<std::string>                        filess;
        bool                                            first;
        int retval;

    /* functions dump */
    public:
        bruh();
        ~bruh();
        int     error_handler(int ac, char **av, int mode);
        int     main(int ac, char **av);
        int     help_output(void);
        int     error_output(void);
        void    dataparser(std::vector<std::string> wordTab);
        std::vector<std::string>    getWordTabFromFile(std::string fileName);
        std::vector<std::string>    splitLine(std::string line, char sep);
        std::map<std::string, std::vector<std::string>>     getmapper(void);
        std::map<std::string, std::string>                  getmapper2(void);
        void    compile(std::map<std::string, std::vector<std::string>> const &mapper, std::map<std::string, std::string> mapper2, std::string file);
        void    matrixcreate(unsigned long x, unsigned long y);
        void    drawer1(std::string file, std::string aff);
        void    drawer2(std::string file, std::string aff);
        void    drawer3(std::string resolver);
        void    drawer4(void);
        void    matrixchecker(void);
        void    loopchecker(void);
    };
} 