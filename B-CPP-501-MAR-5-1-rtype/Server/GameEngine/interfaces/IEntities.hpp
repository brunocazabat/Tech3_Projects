/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** IEntities
*/

#ifndef IENTITIES_HPP_
#define IENTITIES_HPP_

#include "IDEntities.hpp"

class IEntities : public IDEntities {
    public:
        virtual ~IEntities() = default;
        virtual bool isOnFire() = 0;
        virtual std::shared_ptr<IDEntities> fire() = 0;
    protected:
        bool _canFire;
};

#endif /* !IENTITIES_HPP_ */