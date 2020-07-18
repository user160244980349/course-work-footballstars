#ifndef FOOTBALLSTARS_UTILITIES_H
#define FOOTBALLSTARS_UTILITIES_H

#include "main.h"
#include "Vector.h"
#include "Rect.h"
#include "Model.h"
#include "Collider.h"
#include "ModelView.h"
#include "ControlKeys.h"
#include "ControlVectors.h"
#include "Physics.h"
#include "Controller.h"
#include "Scoreboard.h"

/**
* Функция хэлпер -- позволяет упростить загрузку текстур
* до 1й команды.
*/
void LoadTexture (const char* path, SDL_Renderer* renderer, SDL_Texture** texture);

/**
* Главная функция.
* \param renderer − Указатель на рендерер.
*/
void MainFunction (SDL_Renderer* renderer);

#endif // FOOTBALLSTARS_UTILITIES_H
