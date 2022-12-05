/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "include/include.hpp"

int     bruh::include::help_output(void)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./304pacman file c1 c2" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tfile\tfile describing the board, using the following characters:" << std::endl;
    std::cout << "\t\t\t'0' for an empty square," << std::endl;
    std::cout << "\t\t\t'1' for a wall," << std::endl;
    std::cout << "\t\t\t'F' for the ghost's position," << std::endl;
    std::cout << "\t\t\t'P' for Pacman's position." << std::endl;
    std::cout << "\tc1\tcharacter to display for a wall" << std::endl;
    std::cout << "\tc2\tcharacter to display for an empty space." << std::endl;
    
    return (0);
}

int     bruh::include::error_handler(int ac, char **av, int mode)
{
    switch (mode)
    {
    case (1):
        if (ac == 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
            help_output();
            return (retval = 0);
        }
        if (ac != 4 || !strcmp(av[2], "\0") || !strcmp(av[3], "\0"))
            return (retval = 84);

        break;

    case (2):
        if (wordTab.empty())
		    return (retval = 84);
        if (checker(wordTab) == 84)
            return (retval = 84);
        
        break;
    }

    return (retval = 1);
}


int     bruh::include::checker(const std::vector<std::string> &wordTab)
{
    if (!sizechecker(wordTab))
        return (retval = 84);

    if (!mapchecker(wordTab))
        return (retval = 84);
    return (0);
}

bool    bruh::include::sizechecker(const std::vector<std::string> &wordtab)
{
    unsigned long   size = 0;

    for (const std::string &line : wordtab)
    {
        if (!line.empty() && size != 0)
        {
            if (line.size() != size)
                return (false);
            size = line.size();
        }
        else if (line.empty())
            return (false);
        else if (size == 0)
            size = line.size();
    }
    return (true);
}

bool    bruh::include::mapchecker(const std::vector<std::string> &wordTab)
{
    bool    foundPacman = false;
    bool    foundGhost = false;

    for (const std::string &line : wordTab)
    {
        for (const char &c : line)
        {
            if (c == 'P')
            {
                if (!foundPacman)
                    foundPacman = true;
                else
                    return (false);
            }
            else if (c == 'F')
            {
                if (!foundGhost)
                    foundGhost = true;
                else
                    return (false);
            }
            else if (c < '0' || c > '1')
                return (false);
        }
    }
    return (true);
}