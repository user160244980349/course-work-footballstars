#ifndef FOOTBALLSTARS_SCOREBOARD_H
#define FOOTBALLSTARS_SCOREBOARD_H

#include "main.h"

/// Класс табло счета.
class Scoreboard {
private:
    /// Структура, хранящая счет игроков.
    struct {
        int player1Score;   ///< Счет игрока слева.
        int player2Score;   ///< Счет игрока справа.
        char buf[1];
    } scores;

    /// Структура, описывающая переменные для работы с SDL.
    struct {
        SDL_Renderer* renderer; ///< Указатель на рендерер.
        TTF_Font* font;         ///< Указатель на шрифт.
        SDL_Color color;        ///< Цвет текста.
        SDL_Surface* surf1;     ///< Поверхность счета игрока слева.
        SDL_Texture* tex1;      ///< текстура счета игрока слева.
        SDL_Surface* surf2;     ///< Поверхность счета игрока справа.
        SDL_Texture* tex2;      ///< текстура счета игрока справа.
    } SDLenv;

    /// Структура, описывающая области экрана и текстур для вывода.
    struct {
        SDL_Rect rect1;     ///< Области текстуры счета игрока слева для вывода.
        SDL_Rect rect2;     ///< Области экрана счета игрока слева для вывода.
        SDL_Rect rect3;     ///< Области текстуры счета игрока справа для вывода.
        SDL_Rect rect4;     ///< Области экрана счета игрока справа для вывода.
    } rects;

public:
    /**
    * \param renderer − Указатель на рендерер.
    */
    Scoreboard (SDL_Renderer* renderer, const char* path);

    /// Метод вывода счета на экран.
    void DrawScores ();

    ///Метод увеличения счета игрока слева.
    void IncP1Score ();

    ///Метод увеличения счета игрока справа.
    void IncP2Score ();
    ~Scoreboard ();
};

#endif // FOOTBALLSTARS_SCOREBOARD_H
