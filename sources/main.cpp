#include "../include/main.h"
#include "../include/Utilities.h"

/**
* Вход в программу.
* \param argc − Количество внешних параметров.
* \param argv − Массив внешних параметров.
*/
int main(int argc, char* argv[]) {

    if (SDL_Init (SDL_INIT_EVERYTHING)) {
         std::cout << "error loading SDL2!" << std::endl;
         return 1;
    }

    if (TTF_Init()) {
         std::cout << "error loading SDL2_TTF!" << std::endl;
         return 1;
    }

    if (!IMG_Init (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP)) {
        std::cout << "error loading SDL2_IMG!" << std::endl;
        return 1;
    }

    char name[] = "Footballstars";     // Название программы.
    SDL_Window* window;         // Указатель на окно.
    SDL_Renderer* renderer;     // Указатель на рендерер.
    SDL_Surface* icon = IMG_Load("Rresources/ball.png");

    window = SDL_CreateWindow (name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWWIDTH, WINDOWHIGHT, !SDL_WINDOW_RESIZABLE);
    SDL_SetWindowIcon (window, icon);

    renderer = SDL_CreateRenderer (window, 1, 0);

    MainFunction (renderer);
    
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    SDL_FreeSurface (icon);
    TTF_Quit ();
    IMG_Quit ();
    SDL_Quit ();

    return 0;
}