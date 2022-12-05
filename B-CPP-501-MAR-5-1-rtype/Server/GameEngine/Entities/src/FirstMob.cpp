/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** FirstMob
*/

#include "../include/FirstMob.hpp"

FirstMob::FirstMob():_count(rand() % 30)
{
    _canFire = false;
    _components.push_back(std::make_shared<Life>(200));
    _components.push_back(std::make_shared<Position>(std::pair<int, int>(1920, 500)));
    _components.push_back(std::make_shared<Speed>(std::pair<int, int>(-10, 0)));
    _components.push_back(std::make_shared<Sprite>(SPRITES_PATH + "r-typesheet7.gif;33;0;33;33;6"));
}

FirstMob::~FirstMob()
{
}

void FirstMob::setPos(int x, int y)
{
    std::static_pointer_cast<Position>(getComponent(IElem::Position))->update(std::pair<int, int>(x, y));
}

void FirstMob::randVertSpeed()
{
    _count++;
    if (_count >= 30) {
        _count = 0;
        _canFire = true;
    }
    if (_count % 6 > 3)
        std::static_pointer_cast<Speed>(getComponent(IElem::Speed))->updateY(5);
    else
        std::static_pointer_cast<Speed>(getComponent(IElem::Speed))->updateY(-5);
}

void FirstMob::update()
{
    randVertSpeed();
    (*std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))) += 1;
    std::static_pointer_cast<Position>(getComponent(IElem::Position))->updateBySpeed(std::static_pointer_cast<Speed>(getComponent(IElem::Speed))->get());
}

bool FirstMob::hit(int nb)
{
    (*std::static_pointer_cast<Life>(getComponent(IElem::Life))) -= nb;
    if (std::static_pointer_cast<Life>(getComponent(IElem::Life))->get() <= 0) {
        return (false);
    }
    return (true);
}

int FirstMob::getDamage()
{
    return (5);
}

std::pair<int, int> FirstMob::getPos()
{
    return (std::static_pointer_cast<Position>(getComponent(IElem::Position))->get());
}

std::string FirstMob::getSprite()
{
    return (std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->get());
}

Rect FirstMob::getSpriteRect()
{
    std::pair<int, int> pos = std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->getRectPos();
    std::pair<int, int> size = std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->getRectSize();

    return (Rect(pos.first, pos.second, size.first, size.second));
}

bool FirstMob::isOnFire()
{
    return (_canFire);
}

std::shared_ptr<IDEntities> FirstMob::fire()
{
    _canFire = false;
    return (std::make_shared<BasicProjectile>(getPos(), 50));
}

void FirstMob::display()
{

}