#include "../include/Scoreboard.h"

Scoreboard::Scoreboard (SDL_Renderer* renderer, const char* path) {
    this -> SDLenv.font = TTF_OpenFont(path, 64);
    this -> SDLenv.renderer = renderer;
    SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF};
    this -> SDLenv.color = color;
    this -> scores.player1Score = 0;
    this -> scores.player2Score = 0;
};
Scoreboard::~Scoreboard () {
    if (SDLenv.surf1)
        SDL_FreeSurface(SDLenv.surf1);
    if (SDLenv.surf2)
        SDL_FreeSurface(SDLenv.surf2);
    if (SDLenv.tex1)
        SDL_DestroyTexture (SDLenv.tex1);
    if (SDLenv.tex2)
        SDL_DestroyTexture (SDLenv.tex2);
};

void Scoreboard::DrawScores () {

    sprintf(scores.buf, "%d", scores.player1Score);
    SDLenv.surf1 = TTF_RenderUTF8_Solid(SDLenv.font, scores.buf, SDLenv.color);
    SDLenv.tex1 = SDL_CreateTextureFromSurface(SDLenv.renderer, SDLenv.surf1);
    rects.rect1.x = 0;
    rects.rect1.y = 0;
    rects.rect2.x = 0;
    rects.rect2.y = 0;
    rects.rect2.w = rects.rect1.w = SDLenv.surf1 -> w;
    rects.rect2.h = rects.rect1.h = SDLenv.surf1 -> h;
    SDL_RenderCopy(SDLenv.renderer, SDLenv.tex1, &rects.rect1, &rects.rect2);
    SDL_FreeSurface(SDLenv.surf1);
    SDL_DestroyTexture (SDLenv.tex1);

    sprintf(scores.buf, "%d", scores.player2Score);
    SDLenv.surf2 = TTF_RenderUTF8_Solid(SDLenv.font, scores.buf, SDLenv.color);
    SDLenv.tex2 = SDL_CreateTextureFromSurface(SDLenv.renderer, SDLenv.surf2);
    rects.rect3.x = 0;
    rects.rect3.y = 0;
    rects.rect4.x = WINDOWWIDTH - SDLenv.surf2 -> w;
    rects.rect4.y = 0;
    rects.rect4.w = rects.rect3.w = SDLenv.surf2 -> w;
    rects.rect4.h = rects.rect3.h = SDLenv.surf2 -> h;
    SDL_RenderCopy(SDLenv.renderer, SDLenv.tex2, &rects.rect3, &rects.rect4);
    SDL_FreeSurface(SDLenv.surf2);
    SDL_DestroyTexture (SDLenv.tex2);
};
void Scoreboard::IncP1Score () {
    scores.player1Score++;
};
void Scoreboard::IncP2Score () {
    scores.player2Score++;
};