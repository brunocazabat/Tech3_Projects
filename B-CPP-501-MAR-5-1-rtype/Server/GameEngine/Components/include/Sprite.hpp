/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "../../interfaces/ITComponents.hpp"

class Sprite: public ITComponents<std::string> {
    public:
        // path = path;posx;posy;sizex;sizey;max_anim
        Sprite(std::string path);
        ~Sprite();
        Elem elem() const override {return (IElem::Sprite);};
        std::pair<int, int> getRectPos() const;
        std::pair<int, int> getRectSize() const;
        void setRectPos(int x, int y);
        void setRectSize(int x, int y);
        void operator+=(int nb);
        void operator-=(int nb);

    protected:
    private:
        // _value;
        std::pair<int, int> _rectSize;
        std::pair<int, int> _rectPos;
        int _maxAnim;
};

#endif /* !SPRITE_HPP_ */