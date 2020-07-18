#ifndef FOOTBALLSTARS_MODELVIEW_H
#define FOOTBALLSTARS_MODELVIEW_H

#include "main.h"
#include "Base.h"
#include "Model.h"
#include "Vector.h"

/// Класс вида объекта.
class ModelView : public Base {
private:
    /// Структура, описывающая переменные для работы с SDL.
    struct {
        SDL_Renderer* renderer; ///< Указатель на рендерер.
        SDL_Texture* image;     ///< Указатель на текстуру.
        SDL_RendererFlip flip;  ///< Отзеркаливание текстуры.
    } SDLenv;

    /**
    * Структура, хранящая в себе базовые аттрибуты тела.
    * При наследовании наполняется большим количеством
    * аттрибутов.
    */
    struct {
        Model* objectPtr; ///< Указатель на объект, которому принадлежит.
    } ThisAttributes;

    /**
    * Структура, хранящая в себе аттрибуты таймера,
    * для просчета физики.
    */
    struct {
        bool rotate;    ///< Определяет имеет ли вращение модель.
    } PhysicalAttributes;

    /// Структура, хранящая остальные параметры для рисования.
    struct {
        double angle;   ///< Вращение модели. Рассчитывается из скорости.
    } ForDraw;

    /**
    * Структура, хранящая в себе векторы, которые
    * в определенной ситуации изменяют параметры тела.
    */
    struct {
        Vector offset;  ///< Вектор, компенсирующий разницу между размерами и координатами тела и коллайдера
        Vector rotate;  ///< Вектор, определяющий ось вращения тела.
    } Vectors;

public:
    /**
    * \param renderer − Указатель на рендерер.
    * \param object − Модель, которой принадлежит вид.
    * \param collider − Коллайдер модели, которой принадлежит вид.
    * \param pos − Координаты смещения вида и его размеры.
    * \param rotate − Вращение вида.
    * \param path − Путь до текстуры.
    * \param flip − Отзеркаливание текстуры.
    */
    ModelView (SDL_Renderer* renderer, Model* object, Rect pos, bool rotate, const char* path, SDL_RendererFlip flip);

    ~ModelView ();

    /// Метод отрисовки вида на экране.
    void DrawImage ();

    /// Метод обновления параметров вида.
    void Update ();
};

#endif // FOOTBALLSTARS_MODELVIEW_H
