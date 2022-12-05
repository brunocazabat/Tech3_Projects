/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** AI
*/

#ifndef AI_HPP_
#define AI_HPP_

#include "../../interfaces/ITComponents.hpp"

class AI: public ITComponents<std::string> {
    public:
        AI(std::string type);
        ~AI();
        Elem elem() const override {return (IElem::AI);};
        void use();

    protected:
        int _count;
        std::pair<int, int> _playerPos;
        std::pair<int, int> _entityPos;
    private:
};

#endif /* !AI_HPP_ */