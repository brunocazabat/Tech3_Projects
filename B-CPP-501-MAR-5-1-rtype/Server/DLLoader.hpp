/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <iostream>
#include <dlfcn.h>

template<typename T>
class DLLoader {
    public:
        DLLoader() {};
        T *getInstance(std::string lib, void **handler)
        {
            void *handle = dlopen(lib.c_str(), RTLD_LAZY);
            if (!handle) {
                std::cerr << "Erreur ouverture de la lib : " << lib << std::endl << dlerror() << std::endl;
                exit(84);
            }
            T *(*func)();
            *(void **) (&func) = dlsym(handle, "entryPoint");
            if (func == NULL) {
                std::cerr << "Erreur lecture de la lib : " << lib << std::endl << dlerror() << std::endl;
                exit(84);
            }
            (*handler) = handle;
            return (func());
        };
    protected:
    private:
};

#endif /* !DLLOADER_HPP_ */