/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "include/include.hpp"

void        make::bruh::compile(std::map<std::string, std::vector<std::string>> const &mapper, std::map<std::string, std::string> mapper2, std::string file)
{
    _mapper = mapper;
    _mapper2 = mapper2;

    if (file == "")
        drawer4();
    else
        drawer3(file);
}



void        make::bruh::matrixcreate(unsigned long x, unsigned long y)
{
    std::vector<int>            vec;

    for (unsigned long i = 0; i < x; i++)
        vec.push_back(0);
    for (unsigned long i = 0; i < y; i++)
        this->matrix.push_back(vec);
}

void        make::bruh::drawer1(std::string file, std::string aff)
{
    std::string                     cle;
    std::vector<std::string>        dep;

    for (auto mapper : _mapper)
    {
        std::string                 newAff;
        cle = mapper.first;
        dep = mapper.second;

        if (std::find(dep.begin(), dep.end(), file) != dep.end())
        {
            if (std::find(RightTab.begin(), RightTab.end(), cle) != RightTab.end()) {
                newAff = aff;
                newAff += file ;
                newAff += " -> ";
                drawer1(cle, newAff);
            }
            else
            {
                newAff = aff;
                newAff += file;
                newAff += " -> ";
                newAff += cle;
                this->arbre.push_back(newAff);
            }
        }
    }
}

void        make::bruh::drawer2(std::string file, std::string aff)
{
    std::string                     cle;
    std::vector<std::string>        dep;

    for (auto mapper : _mapper)
    {
        std::string                 newAff;
        cle = mapper.first;
        dep = mapper.second;

        if (std::find(dep.begin(), dep.end(), file) != dep.end())
        {
            if (std::find(RightTab.begin(), RightTab.end(), cle) != RightTab.end()) {
                newAff = aff;
                newAff += _mapper2[cle];
                newAff += "\n";
                drawer2(cle, newAff);
            }
            else
            {
                newAff = aff;
                newAff += _mapper2[cle];
                this->arbre.push_back(newAff);
            }
        }
    }
}

void        make::bruh::drawer3(std::string resolver)
{
    std::string cle;
    std::vector<std::string> dependencies;
    std::vector<std::string> files;
    bool found;

    for (auto const &line : _mapper) {
        found = false;
        cle = line.first;
        dependencies = line.second;

        for (unsigned int i = 0; i < files.size(); i++) {
            if (files[i] == cle)
                found = true;
        }
        if (!found)
            files.push_back(cle);
        for (auto fileName : dependencies)
        {
            if (std::find(this->RightTab.begin(), this->RightTab.end(), fileName) == this->RightTab.end())
            {
                if (fileName != "")
                    this->RightTab.push_back(fileName);
            }
            if (!fileName.empty()) {
                found = false;
                for (unsigned int i = 0; i < files.size(); i++) {
                    if (files[i] == fileName)
                        found = true;
                }
                if (!found)
                    files.push_back(fileName);
            }
        }
    }

    if (std::find(files.begin(), files.end(), resolver) == files.end())
        exit(84);
        
    std::sort(files.begin(), files.end(), [](const std::string &one, const std::string &two) -> bool {
        return (one < two);
    });
    std::sort(this->RightTab.begin(), this->RightTab.end(), [](const std::string &one, const std::string &two) -> bool {
        return (one < two);
    });
    this->drawer2(resolver, "");
    for (auto toPrint : this->arbre)
        std::cout << toPrint << std::endl;
    if (this->arbre.empty())
        std::cout << std::endl;
}

void        make::bruh::drawer4()
{
    std::string cle;
    std::vector<std::string> dependencies;
    std::vector<std::string> files;
    bool found;

    for (auto const &line : _mapper) {
        found = false;
        cle = line.first;
        dependencies = line.second;
        if (std::find(this->LeftTab.begin(), this->LeftTab.end(), cle) == this->LeftTab.end())
            this->LeftTab.push_back(cle);

        for (unsigned int i = 0; i < files.size(); i++) {
            if (files[i] == cle)
                found = true;
        }
        if (!found)
            files.push_back(cle);
        for (auto fileName : dependencies)
        {
            if (std::find(this->RightTab.begin(), this->RightTab.end(), fileName) == this->RightTab.end())
            {
                if (fileName != "")
                    this->RightTab.push_back(fileName);
            }
            if (!fileName.empty()) {
                found = false;
                for (unsigned int i = 0; i < files.size(); i++) {
                    if (files[i] == fileName)
                        found = true;
                }
                if (!found)
                    files.push_back(fileName);
            }
        }
    }

    std::sort(files.begin(), files.end(), [](const std::string &one, const std::string &two) -> bool { return (one < two); });

    std::sort(this->RightTab.begin(), this->RightTab.end(), [](const std::string &one, const std::string &two) -> bool { return (one < two); });

    this->matrixcreate(files.size(), files.size());
    int     i = 0;
    int     j = 0;

    for (auto const &fileName : files)
    {
        j = 0;
        if (_mapper.find(fileName) != _mapper.end())
        {
            for (auto const &fileName2 : files)
            {
                dependencies = _mapper[fileName];
                if (std::find(dependencies.begin(), dependencies.end(), fileName2) != dependencies.end()) {
                    this->matrix[i][j] = 1;
                }
                j++;
            }
        }
        i++;
    }

    this->matrixchecker();
    this->filess = files;
    this->loopchecker();

    for (unsigned int i = 0; i < files.size(); i++)
    {
        std::cout << '[';
        for (unsigned int j = 0; j < files.size(); j++)
            std::cout << this->matrix[i][j];
        std::cout << ']' << std::endl;
    }
    std::cout << std::endl;

    for (auto fileName : RightTab)
        this->drawer1(fileName, "");
    for (auto toPrint : this->arbre)
        std::cout << toPrint << std::endl;
}

void                make::bruh::matrixchecker()
{
    for (unsigned int i = 0; i < this->matrix.size(); i++)
    {
        for (unsigned int j = 0; j < this->matrix[i].size(); j++)
        {
            if (i == j && this->matrix[i][j] == 1)
            {
                std::cerr << "inclusion de sois-meme." << std::endl;
                exit(84);
            }
        }
    }
}

void                make::bruh::loopchecker()
{
    for (auto fileName : this->filess)
    {
        if (std::find(LeftTab.begin(), LeftTab.end(), fileName) != LeftTab.end())
        {
            for (auto Files : this->_mapper[fileName])
            {
                if (std::find(LeftTab.begin(), LeftTab.end(), Files) != LeftTab.end())
                {
                    for (auto Filess : this->_mapper[Files])
                    {
                        if (Filess == fileName)
                        {
                            std::cerr << Filess << " depend de " << fileName << "et inversement." << std::endl;
                            exit(84);
                        }
                    }
                }
            }
        }
    }
}