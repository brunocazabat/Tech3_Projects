/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Rect
*/

#ifndef RECT_HPP_
#define RECT_HPP_

class Rect {
    public:
        Rect(int posx_f, int posy_f, int sizex_f, int sizey_f):posx(posx_f), posy(posy_f), sizex(sizex_f), sizey(sizey_f){};
        ~Rect(){};
        int posx;
        int posy;
        int sizex;
        int sizey;

    protected:
    private:
};

#endif /* !RECT_HPP_ */