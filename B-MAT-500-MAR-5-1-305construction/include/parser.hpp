/*
** EPITECH PROJECT, 2020
** B-MAT-500-MAR-5-1-305construction-bruno.cazabat
** File description:
** parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <fstream>
#include <algorithm>
#include "task.hpp"

class Parser
{
    public:
        Parser(std::string filename);
        ~Parser();
        void run();
        void printTasks();
        void officialPrint();
        void graphPrint(std::vector<Task>);
        void levelDetermination();
        void eDater();
        void lDater();
        void assignPrerequisites();
    private:
        void parseLine(std::string line);
        std::ifstream openFile(std::string filename);
        std::ifstream ifs_;
        std::vector<Task*> taskList;
        std::vector<std::vector<Task*>> levels;
        int totalDuration;
};


#endif /* !PARSER_HPP_ */
