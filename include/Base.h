#ifndef FOOTBALLSTARS_BASE_H
#define FOOTBALLSTARS_BASE_H

#include "Rect.h"

///Класс, являющийся основой практически всего.
class Base {
private:
    /**
    * Структура, хранящая в себе базовые аттрибуты тела.
    * При наследовании наполняется большим количеством
    * аттрибутов.
    */
    struct {
        Rect pos; ///< Переменная, хранящая координаты и размеры тела.
    } ThisAttributes;
public:
    /**
    * \param pos − координаты и размеры тела.
    */
    Base (Rect pos);

    ~Base ();

    /**
    * Метод, который устанавливает координаты и размеры тела.
    * \param pos − координаты и размеры тела.
    */
    void SetPos (Rect pos);

    /**
    * Метод, который возвращает координаты и размеры тела.
    * \param pos − координаты и размеры тела.
    * \return координаты и размеры тела.
    */
    Rect GetPos ();

    ///Обновление параметров объекта.
    virtual void Update () {};

};

#endif // FOOTBALLSTARS_BASE_H
