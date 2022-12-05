/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "../include/radiator.hpp"

static void vecResult(const std::vector<std::vector<double>> &matrixA, std::vector<double> &matrixX, const std::vector<double> &matrixY, const int &nPow, const int &iterMax)
{
    double sum = 0;

    for (int i = 0; i < iterMax; i++) {
        for (int j = 0; j < nPow; j++) {
            sum = 0;
            for (int k = 0; k < nPow; k++) {
                if (k != j)
                    sum += matrixA[j][k] * matrixX[k];
                matrixX[j] = (matrixY[j] - sum) / matrixA[j][j];
            }
        }
    }
}

static void trotimax(std::vector<std::vector<double>> &matrixA, const int &n, const int &nPow)
{
    double h = 0.5;
    double hPow = 1 / (h * h);

    for (int i = 0; i < n; i++) {
        matrixA[i][i] = 1;
    }
    for (int j = 1; j < n - 1; j++) {
        matrixA[j * n][j * n] = 1;
        for (int i = 1; i < n - 1; i++) {
            matrixA[j * n + i][(j - 1) * n + i] = hPow;
            matrixA[j * n + i][j * n + i - 1] = hPow;
            matrixA[j * n + i][j * n + i] = -4 * hPow;
            matrixA[j * n + i][j * n + i + 1] = hPow;
            matrixA[j * n + i][(j + 1) * n + i] = hPow;
        }
        matrixA[(j + 1) * n - 1][(j + 1) * n - 1] = 1;
        for (int i = 1; i <= n; i++) {
            matrixA[nPow - i][nPow - i] = 1;
        }
    }
}

void comehereyoulilshit(int n, int nPow, int jr, int ir, int i, int j, const std::string &options)
{
    std::vector<double> matrixY(nPow, 0);
    std::vector<std::vector<double>> matrixA(nPow, std::vector<double>(nPow, 0));
    std::vector<double> matrixX(nPow, 0);

    trotimax(matrixA, n, nPow);
    matrixY[jr * n + ir] = -300;
    vecResult(matrixA, matrixX, matrixY, nPow, 100);
    if (options == "A") {
        maisputinsimon(matrixA);
        hahohore(matrixX);
    }
    if (options == "B") {
        scoubite(matrixX, n, j, i);
    }
}