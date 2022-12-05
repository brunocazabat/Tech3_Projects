/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <string.h>

namespace bruh {
    class include
    {
    public:
        std::vector<std::string>        wordTab;
        int                             retval;
        
        include();
        ~include();

        std::vector<std::string>        getFileContent(std::string fileName);
        int                             main(int ac, char **av);
        int                             error_handler(int ac, char **av, int mode);
        int                             help_output(void);
        int                             checker(const std::vector<std::string> &wordTab);
        bool                            sizechecker(const std::vector<std::string> &wordtab);
        bool                            mapchecker(const std::vector<std::string> &wordTab);
    };
}