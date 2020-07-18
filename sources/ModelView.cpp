#include "../include/ModelView.h"
#include "../include/Utilities.h"

ModelView::ModelView (SDL_Renderer* renderer, Model* object, Rect pos, bool rotate, const char* path, SDL_RendererFlip flip) : Base (pos) {
        this -> SDLenv.renderer = renderer;
        this -> ThisAttributes.objectPtr = object;
        this -> PhysicalAttributes.rotate = rotate;
        this -> SDLenv.flip = flip;
        this -> ForDraw.angle = 0;

        this -> Vectors.offset.x = pos.x;
        this -> Vectors.offset.y = pos.y;
        pos.x = ThisAttributes.objectPtr -> GetPos ().x + Vectors.offset.x;
        pos.y = ThisAttributes.objectPtr -> GetPos ().y + Vectors.offset.y;

        this -> Vectors.rotate.x = pos.w / 2 + Vectors.offset.x;
        this -> Vectors.rotate.y = pos.h / 2 + Vectors.offset.y;

        LoadTexture (path, renderer, &(SDLenv.image));
};
ModelView::~ModelView () {
    SDL_DestroyTexture (SDLenv.image);
};
void ModelView::DrawImage () {

    Rect newPos;        // Новое положение вида на основе положения модели.
    newPos = GetPos ();

    SDL_Rect newPosForDraw;     // SDL эквивалент Rect для использования SDL_RenderCopyEx().
    newPosForDraw.x = newPos.x;
    newPosForDraw.y = newPos.y;
    newPosForDraw.w = newPos.w;
    newPosForDraw.h = newPos.h;

    SDL_Point newRotate;        // SDL эквивалент rotate для использования SDL_RenderCopyEx().
    newRotate.x = Vectors.rotate.x;
    newRotate.y = Vectors.rotate.y;

    if (PhysicalAttributes.rotate)
        ForDraw.angle = M_PI * GetPos ().x;
    SDL_RenderCopyEx (SDLenv.renderer, SDLenv.image, NULL, &newPosForDraw, ForDraw.angle, &newRotate, SDLenv.flip);
};
void ModelView::Update () {

    Rect newPos;    // Новое положение вида на основе положения модели.

    newPos.x = ThisAttributes.objectPtr -> GetPos ().x + Vectors.offset.x;
    newPos.y = ThisAttributes.objectPtr -> GetPos ().y + Vectors.offset.y;
    newPos.w = GetPos ().w;
    newPos.h = GetPos ().h;

    SetPos (newPos);
};