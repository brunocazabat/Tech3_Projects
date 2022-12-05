/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

namespace separation
{
    class bruh
    {
    private:
    protected:
    public:
        int retval;
        std::vector<std::string> names;
        std::vector<std::string> l1;
        std::vector<std::string> l2;
        std::vector<std::vector<std::string>> links;
        std::vector<int> done;
        std::vector<int> dat;
        std::string delim;
        std::string line;
        std::vector<std::string> data;
        bruh();
        ~bruh();
        int     comp_twonames(char **av);
        int     listnameparser(void);
        void    firstnamesort(void);
        void    dualnamesort(void);
        int     error_handler(int ac, char **av, int mode);
        int     main(int ac, char **av);
        int     help_output(char **av);
        int     error_output(void);
        int     final_output(char **av, int to_string, int mode);
        int     nameId(std::string name);
        bool    isDone(int id);
        void    search(int id, std::string person, int value);
        bool    validNb(std::string value);
        bool    nameExists(std::string name);
    };   
} 