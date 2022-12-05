/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "include/include.hpp"

make::bruh::bruh() {}
make::bruh::~bruh() {}

std::map<std::string, std::vector<std::string>>     make::bruh::getmapper() { return (this->mapper); }

std::map<std::string, std::string>                  make::bruh::getmapper2() { return (this->mapper2); }

std::vector<std::string>                            make::bruh::getWordTabFromFile(std::string fileName)
{
    std::vector<std::string>    wordTab;
    std::fstream                file;
    std::string                 line;

    file.open(fileName);
    if (!file.is_open())
        return (wordTab);
    else
    {
        while (std::getline(file, line))
            wordTab.push_back(line);
    }
    return (wordTab);
}

void                                                make::bruh::dataparser(std::vector<std::string> wordTab)
{
    std::string                                                 clemapper;
    bool                                                        clemapperUsed = false;
    std::map<std::string, std::vector<std::string>>             mapper;
    std::map<std::string, std::string>                          mapper2;
    unsigned long                                               idx;

    for (std::string line : wordTab)
    {
        if ((idx = line.find(':')) != std::string::npos)
        {
            if (idx == 0)
                exit(84);
            clemapper = line.substr(0, idx);
            clemapperUsed = true;
            line = line.substr(idx + 1);
            mapper[clemapper] = splitLine(line, ' ');
        }
        else if (!line.empty())
        {
            if (clemapperUsed && !clemapper.empty())
            {
                mapper2[clemapper] = line;
                clemapper = "";
                clemapperUsed = false;
            }
            else
                exit (84);
        }
    }
    this->mapper = mapper;
    this->mapper2 = mapper2;
}

std::vector<std::string>                            make::bruh::splitLine(std::string line, char sep)
{
    std::stringstream           ss(line);
    std::string                 newLine;
    std::vector<std::string>    vec;

    while (std::getline(ss, newLine, sep))
        vec.push_back(newLine);
    return vec;
}