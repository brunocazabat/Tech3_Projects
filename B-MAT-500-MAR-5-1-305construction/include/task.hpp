/*
** EPITECH PROJECT, 2020
** B-MAT-500-MAR-5-1-305construction-bruno.cazabat
** File description:
** task
*/

#ifndef TASK_HPP_
#define TASK_HPP_

#include <iostream>
#include <vector>

class Task
{
    public:
        Task(std::string id, std::string desc, int dur, std::vector<std::string> prer);
        ~Task();
        void setLevel(int);
        void setEStart(int);
        void setLStart(int);
        void setPrerTask(std::vector<Task*>);
        int getEStart();
        int getLStart();
        int getLevel();
        std::vector<Task*> getPrerTask();
        std::string getId();
        std::string getDescription();
        int getDuration();
        std::vector<std::string> getPrerequisites();
        void print();
        bool operator<(const Task& t) const;

    private:
        std::string id_;
        std::string desc_;
        int dur_;
        std::vector<std::string> prer_;
        std::vector<Task*> prerTask;
        int level;
        int earliest_start;
        int latest_start;
};

#endif /* !TASK_HPP_ */
