#ifndef FOOTBALLSTARS_CONTROLVECTOR_H
#define FOOTBALLSTARS_CONTROLVECTOR_H

#include "Vector.h"

/**
* Структура, которая описывает поведение
* персонажа во время игры. Также как и управление
* передается в качестве параметра. В ней задается
* сила удара по мячу, скорость передвижения персонажа.
*/

struct ControlVectors {
    Vector nul;     ///< Переменная, хранящая нулевой вектор.
    Vector left;    ///< Переменная, хранящая вектор движения влево.
    Vector right;   ///< Переменная, хранящая вектор движения вправо.
    Vector jump;    ///< Переменная, хранящая вектор прыжка.
    Vector shoot;   ///< Переменная, хранящая вектор удара.
};

#endif // FOOTBALLSTARS_CONTROLVECTOR_H
