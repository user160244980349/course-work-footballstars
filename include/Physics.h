#ifndef FOOTBALLSTARS_PHYSICS_H
#define FOOTBALLSTARS_PHYSICS_H

#include "main.h"
#include "Model.h"
#include "Collider.h"

/// Класс отвечающий за поведение динамических объектов.
class Physics {
private:
    /**
    * Структура, хранящая в себе базовые аттрибуты тела.
    * При наследовании наполняется большим количеством
    * аттрибутов.
    */
    struct {
        Model* objectPtr;   ///< Указатель на тело, которому принадлежит.
        Collider* collider; ///< Указатель на коллайдер тела, которому принадлежит.
    } ThisAttributes;

    /**
    * Структура, хранящая в себе физические аттрибуты тела.
    * При наследовании наполняется большим количеством
    * аттрибутов.
    */
    struct {
        Rect oldPos;            ///< Предыдущие положение и размеры тела.
        double previousSpeedX;  ///< Предыдущея скорость тела по горизонтали.
        double previousSpeedY;  ///< Предыдущея скорость тела по вертикали.
        double moduleX;         ///< Переменная, определяющая направление скорости тела по горизонтали.
        double moduleY;         ///< Переменная, определяющая направление скорости тела по вертикали.
        double maxSpeed;        ///< Максимальная скорость тела.
        double bouncy;          ///< Коэфициент упругости тела.
    } PhysicalAttributes;

    /**
    * Структура, хранящая в себе указатели на окружающие тела
    * на сцене, для просчета взаимодействий с ними.
    */
    struct {
        Collider** otherColliders;  ///< Указатель на массив коллайдеров других физических тел.
        Collider** otherTriggers;   ///< Указатель на массив триггеров.
        int collidresNum;           ///< Количество физических тел.
        int triggersNum;            ///< Количество триггеров.
    } Env;

    /**
    * Структура, хранящая в себе
    * вектора скоростей и ускорений.
    */
    struct {
        Vector s;               ///< Вектор скорости.
        Vector a;               ///< Вектор ускорения.
        Vector g;               ///< Вектор ускорения свободного падения.
        Vector additionalS;     ///< Вектор для регистрации превышения максимальной скорости.
        Vector additionalA;     ///< Вектор для регистрации превышения максимального ускорения.
    } Vectors;

    /**
    * Структура, хранящая в себе булевые переменные
    * и массивы булевых переменных для регистрации столкновений.
    */
    struct {
        bool* onTriggerEnter;   ///< Массив, заполненный булевыми переменными, отвечающими за вхождение в триггер.
        bool collision;         ///< Булевая переменная, отвечающая за столкновение.
        bool* collisions;       ///< Массив, заполненный булевыми переменными, отвечающими за контакт коллайдеров в триггер.
        bool bounce;            ///< Булевая переменная, показывает был ли совершен рикошет.
        bool sleep;
    } Triggers;

public:
    /**
    * \param objectPtr − указатель на тело, которому принадлежит.
    * \param collider − координаты и размеры коллайдера.
    * \param s − Вектор начальной скорости.
    * \param a − Вектор начального ускорения.
    * \param g − Вектор ускорения свободного падения.
    * \param bouncy − Упругость тела.
    * \param otherColliders − Массив других коллайдеров.
    * \param collidresNum − Количество других коллайдеров.
    * \param otherTriggers − Массив триггеров.
    * \param triggersNum − Количество триггеров.
    */
    Physics (Model* objectPtr,
            Collider* collider,
            Vector s,
            Vector a,
            Vector g,
            double bouncy,
            Collider**
            otherColliders,
            int collidresNum,
            Collider** otherTriggers,
            int triggersNum);

    ~Physics ();

    /**
    * Метод, для приложения сил к телу.
    * \param s − скорость.
    * \param a − ускорение.
    */
    void ApplyForce (Vector s, Vector a);

    /// Просчет физики.
    void Update ();

    void Sleep();
    void Awake();

    /// Просчет столкновений.
    void Collide ();

    /**
    * Метод, проверяющий находится ли тело в триггере.
    * \param trigger − триггер для проверки.
    */
    bool OnTriggerStay (Collider* trigger);

    /**
    * Метод, проверяющий входило ли тело в триггер.
    * \param trigger − триггер для проверки.
    */
    bool OnTriggerEnter (Collider* trigger);

    /// Метод, который используется в контроллерах, для управления телом.
    virtual void Action (Physics* ballPhysics, Collider* ballCollider) {};
};

#endif // FOOTBALLSTARS_PHYSICS_H
