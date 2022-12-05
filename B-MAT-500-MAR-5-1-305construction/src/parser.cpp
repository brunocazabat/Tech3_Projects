/*
** EPITECH PROJECT, 2020
** B-MAT-500-MAR-5-1-305construction-bruno.cazabat
** File description:
** parser
*/

#include "parser.hpp"

Parser::Parser(std::string filename)
{
    ifs_ = openFile(filename);
    totalDuration = 0;
    run();
}

Parser::~Parser()
{
    ifs_.close();
}

void Parser::run()
{
    std::string line;
    while (getline(ifs_, line))
    {
        parseLine(line);
    }
    levelDetermination();
    assignPrerequisites();
    eDater();
    lDater();
}

void Parser::officialPrint()
{
    std::vector<Task> ttt;
    for (size_t i = 0; i < taskList.size(); i++)
    {
        ttt.push_back(*taskList[i]);
    }
    std::sort(ttt.begin(), ttt.end());
    std::cout << "Total duration of construction: " << totalDuration << " weeks\n" << std::endl;
    for (size_t i = 0; i < ttt.size(); i++)
    {

        std::cout << ttt[i].getId() << " must begin ";
        if (ttt[i].getEStart() == ttt[i].getLStart())
            std::cout << "at t=" << ttt[i].getEStart() << std::endl;
        else
            std::cout << "between t=" << ttt[i].getEStart() << " and t=" << ttt[i].getLStart() << std::endl;
    }
    std::cout << std::endl;
    graphPrint(ttt);
}

void Parser::graphPrint(std::vector<Task> task)
{
    for (size_t i = 0; i < task.size(); i++)
    {
        std::cout << task[i].getId() << "\t(" << task[i].getLStart() - task[i].getEStart() << ")\t";
        for (int e = 0; e < task[i].getEStart(); e++)
        {
            std::cout << ' ' << std::flush;
        }
        for (int d = 0; d < task[i].getDuration(); d++)
        {
            std::cout << '=' << std::flush;
        }
        std::cout << std::endl;
    }
}

void Parser::printTasks()
{
    for (size_t i = 0; i < taskList.size(); i++)
    {
        taskList[i]->print();
    }

    std::cout << "Total duration of construction: " << totalDuration << " weeks" << std::endl;
}

int getMaxEStart(Task *task)
{
    int max = 0;
    int calcul = 0;
    for (size_t i = 0; i < task->getPrerTask().size(); i++)
    {
        calcul = task->getPrerTask()[i]->getEStart() + task->getPrerTask()[i]->getDuration();
        if (max < calcul)
            max = calcul;
    }
    return max;
}

int getMaxLevel(std::vector<Task *> tl)
{
    int maxLevel = 0;
    for (size_t i = 0; i < tl.size(); i++)
    {
        if (maxLevel < tl[i]->getLevel())
            maxLevel = tl[i]->getLevel();
    }
    return maxLevel;
}

void Parser::eDater()
{
    for (int lv = 2; lv <= getMaxLevel(taskList); lv++)
    {
        for (size_t i = 0; i < taskList.size(); i++)
        {
            if (taskList[i]->getLevel() == lv)
                taskList[i]->setEStart(getMaxEStart(taskList[i]));
            if (totalDuration < taskList[i]->getEStart() + taskList[i]->getDuration())
                totalDuration = taskList[i]->getEStart() + taskList[i]->getDuration();
        }
    }
}

void Parser::lDater()
{
    int calcul;
    for (size_t i = 0; i < taskList.size(); i++)
    {
        if (taskList[i]->getLevel() == getMaxLevel(taskList))
            taskList[i]->setLStart(totalDuration - taskList[i]->getDuration());
    }
    for (int lv = getMaxLevel(taskList); lv > 0; lv--)
    {
        for (size_t i = 0; i < taskList.size(); i++)
        {
            if (taskList[i]->getLevel() == lv)
                for (size_t j = 0; j < taskList[i]->getPrerTask().size(); j++)
                {
                    calcul = taskList[i]->getLStart() - taskList[i]->getPrerTask()[j]->getDuration();
                    if (calcul < taskList[i]->getPrerTask()[j]->getLStart() || taskList[i]->getPrerTask()[j]->getLStart() < 0)
                        taskList[i]->getPrerTask()[j]->setLStart(calcul);
                }
        }
    }
    for (size_t i = 0; i < taskList.size(); i++)
    {
        if (taskList[i]->getLStart() < 0)
            taskList[i]->setLStart(totalDuration - taskList[i]->getDuration());
    }
}

bool isAdded(std::vector<Task *> taskAdded, std::vector<std::string> prerequisites)
{
    std::vector<std::string> p2 = prerequisites;

    for (size_t i = 0; i < prerequisites.size(); i++)
    {
        for (size_t j = 0; j < taskAdded.size(); j++)
        {
            if (prerequisites[i] == taskAdded[j]->getId())
            {
                if (std::find(p2.begin(), p2.end(), prerequisites[i]) != p2.end())
                    p2.erase(std::find(p2.begin(), p2.end(), prerequisites[i]));
            }
            if (p2.size() == 0)
            {
                return true;
            }
        }
    }
    return false;
}

void Parser::levelDetermination()
{
    std::vector<Task *> taskAdded;
    std::vector<Task *> taskAdded2;

    for (size_t i = 0; taskList.size() > i; i++)
    {
        if (taskList[i]->getPrerequisites().size() == 0)
        {
            taskList[i]->setLevel(1);
            taskAdded.push_back(taskList[i]);
        }
    }
    
    for (int lv = 2; taskList.size() > taskAdded2.size(); lv++)
    {
        if (taskAdded.size() == taskAdded2.size()) {
            std::cout << "file error: invalid prerequisite" << std::endl;
            std::cout << "tasks parsed: " << taskAdded2.size() << "/" << taskList.size() << std::endl;
            std::cout << "could not determine level: " << lv << std::endl;
            exit (84);
        }
        taskAdded2 = taskAdded;
        for (size_t i = 0; i < taskList.size(); i++) // parcours taskList
        {
            if (taskList[i]->getLevel() == 0) // si level == 0 alors...
            {
                for (size_t j = 0; j < taskList[i]->getPrerequisites().size(); j++) // parcours prerequisites de l'element
                {
                    if (isAdded(taskAdded2, taskList[i]->getPrerequisites()) == true) // si prerequisite a déjà été ajoutée alors...
                    {
                        taskList[i]->setLevel(lv);          // set le level de cette task
                        taskAdded.push_back(taskList[i]);       // add cette task à la liste de tasks déjà ajoutée
                        break;
                    }
                }
            }
        }
    }
    for (size_t i = 0; i < taskList.size(); i++) // parcours taskList
    {
        if (taskList[i]->getLevel() == 0) // si level == 0 alors pas normal
        {
            std::cout << "file error: invalid prerequisite at line: " << i+1 << std::endl;   // donc error
            taskList[i]->print();
            // exit (84);
        }
    }
}

void Parser::assignPrerequisites()
{
    std::vector<Task *> prerList;

    for (size_t i = 0; i < taskList.size(); i++)
    {
        for (size_t j = 0; j < taskList[i]->getPrerequisites().size(); j++)
        {
            for (size_t k = 0; k < taskList.size(); k++)
                if (taskList[k]->getId() == taskList[i]->getPrerequisites()[j])
                    prerList.push_back(taskList[k]);
            }
        taskList[i]->setPrerTask(prerList);
        prerList.clear();
    }
}

std::vector<std::string> split(const std::string &src, char delim)
{
    using namespace std;
    vector<string> v;
    auto p = begin(src);
    for (auto q = find(p, end(src), delim); q != end(src); q = find(++p, end(src), delim))
    {
        v.emplace_back(p, q);
        p = q;
    }
    if (p != end(src))
        v.emplace_back(p, end(src));
    return v;
}

bool isNumber(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
        if (std::isdigit(str[i]) == false)
            return false;
    return true;
}

void Parser::parseLine(std::string line)
{
    std::vector<std::string> cell = split(line, ';');
    std::string id;
    std::string desc;
    int duration;
    std::vector<std::string> prer = {};
    int x = 0;

    if (cell.size() < 3) {
        std::cout << "file error at: " << line << std::endl;
        std::cout << "each line must contain at least 3 columns : id;description;duration;prerequisites(optional)" << std::endl;
        exit(84);
    }

    if (!isNumber(cell[2]))
    {
        std::cout << "file error at: " << line << std::endl;
        std::cout << "third argument must be a number";
        exit (84);
    }

    for (size_t i = 0; i < cell.size(); i++)
    {
        switch (x)
        {
        case 0:
            id = cell[i];
            break;
        case 1:
            desc = cell[i];
            break;
        case 2:
            duration = std::stoi(cell[i]);
            break;
        default:
            prer.push_back(cell[i]);
            break;
        }
        x++;
    }
    Task *task = new Task(id, desc, duration, prer);
    taskList.push_back(task);
}

std::ifstream Parser::openFile(std::string filename)
{
    std::ifstream is(filename);
    if (!is.is_open())
    {
        std::cout << "invalid file name, use -h for help" << std::endl;
        exit(84);
    }
    return is;
}
