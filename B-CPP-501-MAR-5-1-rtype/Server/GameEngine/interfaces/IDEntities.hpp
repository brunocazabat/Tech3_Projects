/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** IDEntities
*/

#ifndef IDENTITIES_HPP_
#define IDENTITIES_HPP_

#ifdef __linux__
    #define PATH ""
#elif defined _WIN32 || defined _WIN64
    #define PATH "../../../"
#else
    #error "unknown platform"
#endif

#define SPRITES_PATH PATH + std::string("Sprites/")

#include "../Components/include/AI.hpp"
#include "../Components/include/ComponentError.hpp"
#include "../Components/include/Damage.hpp"
#include "../Components/include/Life.hpp"
#include "../Components/include/Position.hpp"
#include "../Components/include/Rect.hpp"
#include "../Components/include/Speed.hpp"
#include "../Components/include/Sprite.hpp"

class IDEntities {
    public:
        typedef IComponents::Elem IElem;
        virtual ~IDEntities() = default;
        virtual std::string getName() {return (_name);};
        virtual void setName(std::string name) {_name = name;};
        virtual void update() = 0;
        virtual void display() = 0;
        virtual bool hit(int nb) = 0;
        virtual std::pair<int, int> getPos() = 0;
        virtual std::string getSprite() = 0;
        virtual Rect getSpriteRect() = 0;
        virtual bool findComponent(IElem type) {
            for (size_t i = 0; i < _components.size(); i++) {
                if (_components.at(i)->elem() == type) {return (true);}
            }return (false);};
        virtual std::shared_ptr<IComponents> getComponent(IElem type) {
            for (size_t i = 0; i < _components.size(); i++) {
                if (_components.at(i)->elem() == type) {return (_components.at(i));}
            }throw ComponentError("No matching component for this type:" + std::to_string(type) + "\n");};

    protected:
        std::vector<std::shared_ptr<IComponents>> _components;
        std::string _name;
};

#endif /* !IDENTITIES_HPP_ */