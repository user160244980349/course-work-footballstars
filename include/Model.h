#ifndef FOOTBALLSTARS_MODEL_H
#define FOOTBALLSTARS_MODEL_H

#include "Rect.h"
#include "Base.h"

/// Модель или объект игрового процесса.
class Model : public Base {
private:
    /**
    * Структура, хранящая в себе базовые аттрибуты тела.
    * При наследовании наполняется большим количеством
    * аттрибутов.
    */
    struct {

    } ThisAttributes;

public:
    /**
    * Конструктор класса.
    * \param pos − координаты и размеры тела.
    */
    Model (Rect pos);

    ~Model ();

};

#endif // FOOTBALLSTARS_MODEL_H
