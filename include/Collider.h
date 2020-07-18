#ifndef FOOTBALLSTARS_COLLIDER_H
#define FOOTBALLSTARS_COLLIDER_H

#include "Model.h"
#include "Vector.h"

class Collider : public Base {
private:
    /**
    * Структура, хранящая в себе базовые аттрибуты тела.
    * При наследовании наполняется большим количеством
    * аттрибутов.
    */
    struct {
        Model* objectPtr;   ///< Указатель на тело, которому принадлежит.
    } ThisAttributes;
    /**
    * Структура, хранящая в себе векторы, которые
    * в определенной ситуации изменяют параметры тела.
    */
    struct {
        Vector offset;  ///< Вектор, компенсирующий разницу между размерами и координатами тела и коллайдера
    } Vectors;
public:
    /**
    * \param objectPtr − указатель на тело, которому принадлежит.
    * \param pos − координаты и размеры коллайдера.
    */
    Collider (Model* objectPtr, Rect pos);

    ~Collider ();

    ///Обновление параметров коллайдера.
    void Update ();
};

#endif // FOOTBALLSTARS_COLLIDER_H
