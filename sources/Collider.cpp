#include "../include/Collider.h"

Collider::Collider (Model* objectPtr, Rect pos) : Base (pos) {
        ThisAttributes.objectPtr = objectPtr;

        Vectors.offset.x = pos.x;
        Vectors.offset.y = pos.y;
        pos.x = ThisAttributes.objectPtr -> GetPos ().x + Vectors.offset.x;
        pos.y = ThisAttributes.objectPtr -> GetPos ().y + Vectors.offset.y;
};
Collider::~Collider () {

};
void Collider::Update () {

    Rect newPos; // Новое положение тела, после просчета физики.

    newPos.x = ThisAttributes.objectPtr -> GetPos ().x + Vectors.offset.x;
    newPos.y = ThisAttributes.objectPtr -> GetPos ().y + Vectors.offset.y;
    newPos.w = GetPos ().w;
    newPos.h = GetPos ().h;

    SetPos (newPos);
};