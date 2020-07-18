#include "../include/Controller.h"

Controller::Controller (Model* objectPtr, SDL_Event* event, Collider* collider, Vector s, Vector a, Vector g, double bouncy, Collider** otherColliders, int collidresNum, Collider** otherTriggers, int triggersNum,
        ControlKeys keys, ControlVectors vectors) : Physics (objectPtr, collider, s, a, g, bouncy, otherColliders, collidresNum, otherTriggers, triggersNum) {

this -> SDLenv.event = event;
this -> Control.vectors = vectors;
this -> Control.keys = keys;

};
void Controller::Action (Physics* ballPhysics, Collider* ballCollider) {

    Vector result = {0, 0}; // Результирующий вектор.

    if(SDLenv.event -> key.state == SDL_PRESSED && SDLenv.event -> key.repeat == 0) {
        if (SDLenv.event -> key.keysym.sym == Control.keys.left) {
            result.x += Control.vectors.left.x;
            result.y += Control.vectors.left.y;
        }

        if (SDLenv.event -> key.keysym.sym == Control.keys.right) {
            result.x += Control.vectors.right.x;
            result.y += Control.vectors.right.y;
        }

        if (SDLenv.event -> key.keysym.sym == Control.keys.jump) {
            result.x += Control.vectors.jump.x;
            result.y += Control.vectors.jump.y;
        }

        if (SDLenv.event -> key.keysym.sym == Control.keys.shoot && OnTriggerStay (ballCollider)) {
            if (ballPhysics)
                ballPhysics -> ApplyForce (Control.vectors.shoot, Control.vectors.nul);
        }
        ApplyForce (result, Control.vectors.nul);
    }
};
Controller::~Controller () {

};