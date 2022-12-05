/*
** EPITECH PROJECT, 2021
** ouioui
** File description:
** oui
*/

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>

void    print_usage(char **av);

namespace bruh {
    class reedpipe {
        public:
            std::map<std::string, float> var;
            std::vector<float> res;
            std::vector<float> ordinate;
            std::vector<int> abscissa = { 0, 5, 10, 15, 20 };
            std::vector<float> vect = { 0, 0, 0, 0, 0 };

            void compute();
            bool checkSyntaxDouble(char *av);
            bool checkSyntaxInt(char *av);

            reedpipe();
            ~reedpipe();
        private:
        protected:
    };
}