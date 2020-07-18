//
// Created by user on 29.05.2019.
//

#ifndef FOOTBALLSTARS_CONTROLKEYS_H
#define FOOTBALLSTARS_CONTROLKEYS_H

#include "main.h"

/**
* Структура, описывающая клавиши управления.
* Она отправляется в контроллер персонажа в качестве параметра
* и, при необходимости, может быть с легкостью отредактирована.
*/

struct ControlKeys{
    SDL_Keycode left;   ///< Переменная, хранящая клавишу для движения влево.
    SDL_Keycode right;  ///< Переменная, хранящая клавишу для движения вправо.
    SDL_Keycode jump;   ///< Переменная, хранящая клавишу для прыжка.
    SDL_Keycode shoot;  ///< Переменная, хранящая клавишу для удара.
};

#endif // FOOTBALLSTARS_CONTROLKEYS_H
