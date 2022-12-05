/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

void hahohore(const std::vector<double> &matrixX)
{
    std::cout << std::endl;
    for (auto &i : matrixX) {
        std::cout << std::fixed << std::setprecision(1) << i << std::endl;
    }
}

void scoubite(const std::vector<double> &matrixX, int n, int j, int i)
{
    std::cout << std::fixed << std::setprecision(1) << matrixX[j * n + i] << std::endl;
}

void maisputinsimon(const std::vector<std::vector<double>> &matrixA)
{
    for (unsigned int i = 0; i != matrixA.size(); i++) {
        for (unsigned int j = 0; j != matrixA[i].size(); j++) {
            std::cout << matrixA[i][j];
            if (j != matrixA[i].size() - 1)
                std::cout << '\t';
        }
        std::cout << std::endl;
    }
}