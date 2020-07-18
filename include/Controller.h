#ifndef FOOTBALLSTARS_CONTROLLER_H
#define FOOTBALLSTARS_CONTROLLER_H

#include "main.h"
#include "Physics.h"
#include "Collider.h"
#include "ControlVectors.h"
#include "ControlKeys.h"

/// Класс, осуществляющий управление телом.
class Controller : public Physics {
private:
    /// Структура, описывающая переменные для работы с SDL.
    struct {
        SDL_Event* event; ///< Событие.
    } SDLenv;

    /**
    * Структура, хранящая в себе указатели на окружающие тела
    * на сцене, для просчета взаимодействий с ними.
    */
    struct {
        Physics* ballPhysics;   ///< Указатель на физический объект мяч для взаимодействия игрока с ним.
        Collider* ballCollider; ///< Указатель на коллайдер мяча, для взаимодействия игрока с ним.
    } Env;

    /**
    * Структура, хранящая в себе указатели на окружающие тела
    * на сцене, для просчета взаимодействий с ними.
    */
    struct {
        ControlVectors vectors; ///< Вектора, с помощью каторых осуществляется управление.
        ControlKeys keys;       ///< Клавиши, с помощью каторых осуществляется управление.
    } Control;

public:
    /**
    * \param objectPtr − Указатель на объект, которому принадлежит контроллер.
    * \param event − Событие.
    * \param collider − Указатель на коллайдер, которому принадлежит контроллер.
    * \param s − Вектор начальной скорости.
    * \param a − Вектор начального ускорения.
    * \param g − Вектор ускорения свободного падения.
    * \param bouncy − Упругость тела.
    * \param otherColliders − Массив коллайдеров окружающих тел.
    * \param collidresNum − Количество коллайдеров окружающих тел.
    * \param otherTriggers − Массив триггеров.
    * \param triggersNum − Количество триггеров.
    * \param keys − Клавиши управления.
    * \param vectors − Вектора управления.
    */
    Controller (Model* objectPtr,
            SDL_Event* event,
            Collider* collider,
            Vector s,
            Vector a,
            Vector g,
            double bouncy,
            Collider** otherColliders,
            int collidresNum,
            Collider** otherTriggers,
            int triggersNum,
            ControlKeys keys,
            ControlVectors vectors);

    ~Controller ();

    /**
    * Метод, определяющий поведение тела на основе событий.
    * \param ballPhysics − Физическое тело мяч.
    * \paramball Collider − Коллайдер мяча.
    */
    void Action (Physics* ballPhysics, Collider* ballCollider);

};

#endif // FOOTBALLSTARS_CONTROLLER_H
