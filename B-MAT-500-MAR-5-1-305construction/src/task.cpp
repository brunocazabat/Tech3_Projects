/*
** EPITECH PROJECT, 2020
** B-MAT-500-MAR-5-1-305construction-bruno.cazabat
** File description:
** task
*/

#include "task.hpp"

Task::Task(std::string id, std::string desc, int dur, std::vector<std::string> prer)
{
    id_ = id;
    desc_ = desc;
    dur_ = dur;
    prer_ = prer;
    level = 0;
    earliest_start = 0;
    latest_start = -1;
}

Task::~Task()
{
}

void Task::setLevel(int lvl)
{
    level = lvl;
}

int Task::getLevel()
{
    return level;
}

void Task::setPrerTask(std::vector<Task *> pt)
{
    prerTask = pt;
}

std::vector<Task *> Task::getPrerTask()
{
    return prerTask;
}

void Task::setEStart(int i)
{
    earliest_start = i;
}

void Task::setLStart(int i)
{
    latest_start = i;
}

int Task::getEStart()
{
    return earliest_start;
}

int Task::getLStart()
{
    return latest_start;
}

std::string Task::getId()
{
    return id_;
}

std::string Task::getDescription()
{
    return desc_;
}

int Task::getDuration()
{
    return dur_;
}

std::vector<std::string> Task::getPrerequisites()
{
    return prer_;
}

void Task::print()
{
    std::cout << "[TASK ID: " << this->getId() << "]---------------------------------------" << std::endl;
    std::cout << "description:\t\t" << this->getDescription() << std::endl;
    std::cout << "duration:\t\t" << this->getDuration() << std::endl;
    std::cout << "prerequisites:\t\t";

    for (size_t j = 0; j < this->getPrerequisites().size(); j++)
    {
        std::cout << this->getPrerequisites()[j] << " ";
    }
    std::cout << "\nlevel:\t\t\t" << this->getLevel() << std::endl;
    std::cout << "earliest start:\t\t" << this->getEStart() << std::endl;
    std::cout << "latest start:\t\t" << this->getLStart();

    std::cout << std::endl
              << std::endl;
}

bool Task::operator<(const Task &t) const
{
    if (earliest_start != t.earliest_start)
        return (earliest_start < t.earliest_start);
    if (dur_ != t.dur_)
        return (dur_ < t.dur_);
    return (id_ < t.id_);
}