#include "../include/Physics.h"

Physics::Physics (Model* objectPtr,
                Collider* collider,
                Vector s,
                Vector a,
                Vector g,
                double bouncy,
                Collider** otherColliders,
                int collidresNum,
                Collider** otherTriggers,
                int triggersNum) {

    this -> ThisAttributes.objectPtr = objectPtr;
    this -> ThisAttributes.collider = collider;
    this -> Env.otherColliders = otherColliders;
    this -> Env.otherTriggers = otherTriggers;
    this -> Env.collidresNum = collidresNum;
    this -> Env.triggersNum = triggersNum;
    this -> PhysicalAttributes.maxSpeed = 20;
    this -> PhysicalAttributes.bouncy = bouncy;
    this -> Vectors.s = s;
    this -> Vectors.a = a;
    this -> Vectors.g = g;
    this -> Triggers.collision = false;
    this -> Triggers.bounce = false;
    this -> Triggers.sleep = true;

    Vectors.additionalS.x = 0;
    Vectors.additionalS.y = 0;
    Vectors.additionalA.x = 0;
    Vectors.additionalA.y = 0;

    this -> Triggers.collisions = new bool[collidresNum];
    for (int i = 0; i < collidresNum; i++)
    this -> Triggers.collisions[i] = false;

    this -> Triggers.onTriggerEnter = new bool[triggersNum];
    for (int i = 0; i < triggersNum; i++)
    this -> Triggers.onTriggerEnter[i] = false;
};
void Physics::ApplyForce (Vector s, Vector a) {

    Vectors.additionalS.x += s.x;
    Vectors.additionalS.y += s.y;
    Vectors.additionalA.x += a.x;
    Vectors.additionalA.y += a.y;
};
void Physics::Update () {

    if (Triggers.sleep)
        return;

    Vectors.s.x += Vectors.g.x + Vectors.additionalS.x + Vectors.additionalA.x;
    Vectors.s.y += Vectors.g.y + Vectors.additionalS.y + Vectors.additionalA.y;

    Rect newPos;
    newPos.x = ThisAttributes.objectPtr -> GetPos ().x + Vectors.s.x;
    newPos.y = ThisAttributes.objectPtr -> GetPos ().y + Vectors.s.y;
    newPos.w = ThisAttributes.objectPtr -> GetPos ().w;
    newPos.h = ThisAttributes.objectPtr -> GetPos ().h;

    if (Vectors.s.x > PhysicalAttributes.maxSpeed)
        Vectors.s.x = PhysicalAttributes.maxSpeed;
    if (Vectors.s.x < -PhysicalAttributes.maxSpeed)
        Vectors.s.x = -PhysicalAttributes.maxSpeed;
    if (Vectors.s.y > PhysicalAttributes.maxSpeed)
        Vectors.s.y = PhysicalAttributes.maxSpeed;
    if (Vectors.s.y < -PhysicalAttributes.maxSpeed)
        Vectors.s.y = -PhysicalAttributes.maxSpeed;

    ThisAttributes.objectPtr -> SetPos (newPos);

    Collide ();

    if (Triggers.collision) {
        Triggers.bounce = true;
        ThisAttributes.objectPtr -> SetPos (PhysicalAttributes.oldPos);
    } else {
        PhysicalAttributes.oldPos.x = ThisAttributes.objectPtr -> GetPos ().x - Vectors.s.x;
        PhysicalAttributes.oldPos.y = ThisAttributes.objectPtr -> GetPos ().y - Vectors.s.y;
        PhysicalAttributes.oldPos.w = ThisAttributes.objectPtr -> GetPos ().w;
        PhysicalAttributes.oldPos.h = ThisAttributes.objectPtr -> GetPos ().h;
    }

    if (!Triggers.collision && Triggers.bounce) {

        Vectors.s.x *= PhysicalAttributes.bouncy;
        Vectors.s.y *= PhysicalAttributes.bouncy;
        Triggers.bounce = false;
    }

    Vectors.additionalS.x = 0;
    Vectors.additionalS.y = 0;
};
void Physics::Sleep() {
    Triggers.sleep = true;
};
void Physics::Awake() {
    Triggers.sleep = false;
};
void Physics::Collide () {

    double x1 = ThisAttributes.objectPtr -> GetPos().x;                                             // Левая граница тела.
    double x2 = ThisAttributes.objectPtr -> GetPos().x + ThisAttributes.objectPtr -> GetPos().w;    // Правая граница тела.
    double y1 = ThisAttributes.objectPtr -> GetPos().y;                                             // Верхняя граница тела.
    double y2 = ThisAttributes.objectPtr -> GetPos().y + ThisAttributes.objectPtr -> GetPos().h;    // Нижняя граница тела.
    int collisionCounter = 0;                                                                       // Колличество столкновений.
    double step = 1;                                                                                // Величина шага проверки на столкновение.

    for (int collidersCount = 0; collidersCount < Env.collidresNum; collidersCount++) {

        if (Env.otherColliders[collidersCount] == this -> ThisAttributes.collider)
            continue;

        double left = Env.otherColliders[collidersCount] -> GetPos ().x;                                                        // Левая граница другого тела.
        double right = Env.otherColliders[collidersCount] -> GetPos ().x + Env.otherColliders[collidersCount] -> GetPos ().w;   // Левая граница другого тела.
        double top = Env.otherColliders[collidersCount] -> GetPos ().y;                                                         // Левая граница другого тела.
        double bottom = Env.otherColliders[collidersCount] -> GetPos ().y + Env.otherColliders[collidersCount] -> GetPos ().h;  // Левая граница другого тела.

        for (double x = ThisAttributes.objectPtr -> GetPos ().x; x < ThisAttributes.objectPtr -> GetPos ().x + ThisAttributes.objectPtr -> GetPos ().w; x += step) {

            if (Triggers.collisions[collidersCount])
                break;

            for (double y = ThisAttributes.objectPtr -> GetPos ().y; y < ThisAttributes.objectPtr -> GetPos ().y + ThisAttributes.objectPtr -> GetPos ().h; y += step) {

                if (Triggers.collisions[collidersCount])
                    break;

                if (x > left && x < right && y > top && y < bottom) {

                    Triggers.collision = true;
                    Triggers.collisions[collidersCount] = true;
                    collisionCounter++;

                    if ((abs(y2 - top) >= abs(x2 - left) &&
                         abs(y1 - bottom) > abs(x2 - left)) ||
                        (abs(y1 - bottom) >= abs(x1 - right) &&
                         abs(y2 - top) > abs(x1 - right))) {

                        PhysicalAttributes.moduleX = -1;
                    } else
                        PhysicalAttributes.moduleX = 1;

                    if ((abs(y2 - top) < abs(x2 - left) &&
                         abs(y2 - top) <= abs(x1 - right)) ||
                        (abs(y1 - bottom) < abs(x1 - right) &&
                         abs(y1 - bottom) <= abs(x2 - left))) {

                        PhysicalAttributes.moduleY = -1;
                    } else
                        PhysicalAttributes.moduleY = 1;

                    Vectors.s.x = PhysicalAttributes.previousSpeedX * PhysicalAttributes.moduleX;
                    Vectors.s.y = PhysicalAttributes.previousSpeedY * PhysicalAttributes.moduleY;
                }
            }
        }
        if (collisionCounter == 0) {
            Triggers.collision = false;
            Triggers.collisions[collidersCount] = false;
        }
    }
    if (!Triggers.collision) {
        PhysicalAttributes.previousSpeedX = Vectors.s.x;
        PhysicalAttributes.previousSpeedY = Vectors.s.y;
    }
};
bool Physics::OnTriggerStay (Collider* trigger) {
    double x1 = ThisAttributes.collider -> GetPos().x;
    double x2 = ThisAttributes.collider -> GetPos().x + ThisAttributes.collider -> GetPos().w;
    double y1 = ThisAttributes.collider -> GetPos().y;
    double y2 = ThisAttributes.collider -> GetPos().y + ThisAttributes.collider -> GetPos().h;

    double left = trigger -> GetPos ().x;
    double right = trigger -> GetPos ().x + trigger -> GetPos ().w;
    double top = trigger -> GetPos ().y;
    double bottom = trigger -> GetPos ().y + trigger -> GetPos ().h;

    if (x2 > left && x1 < right && y2 > top && y1 < bottom) {
        return true;
    } else
        return false;
};
bool Physics::OnTriggerEnter (Collider* trigger) {

    for (int i = 0; i < Env.triggersNum; i++) {

        if (trigger != Env.otherTriggers[i])
            continue;

        if (OnTriggerStay (trigger)) {
            if (!Triggers.onTriggerEnter[i]) {
                Triggers.onTriggerEnter[i] = true;
                return true;
            } else
                return false;
        }
        Triggers.onTriggerEnter[i] = false;
        return false;
    }
    return false;
};
Physics::~Physics () {
    delete this -> Triggers.onTriggerEnter;
    delete this -> Triggers.collisions;
};