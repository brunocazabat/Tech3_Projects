/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include <iostream>
#include "include/include.hpp"
#include "include/computepac.hpp"

bruh::include::include() {}
bruh::include::~include() {}
bruh::computepac::computepac(const std::vector<std::string> &wordTab) { this->initBasMap(wordTab); }
bruh::computepac::~computepac() {}


std::vector<std::string>        bruh::include::getFileContent(std::string fileName)
{
    std::ifstream               file;
    std::vector<std::string>    wordTabfromfile;
    std::string                 line;

    file.open(fileName);
    if (file.is_open())
        while (std::getline(file, line))
            wordTabfromfile.push_back(line);

    return (wordTabfromfile);
}

int         main(int ac, char **av)
{
    bruh::include b;

    if (b.error_handler(ac, av, 1) != 1)
	    return (b.retval);

    b.wordTab = b.getFileContent(av[1]);

    if (b.error_handler(ac, av, 2) != 1)
	    return (b.retval);

	bruh::computepac pacman(b.wordTab);
	pacman.compute();
	pacman.MapPrinter(av[2][0], av[3][0]);
    
    return (0);
}