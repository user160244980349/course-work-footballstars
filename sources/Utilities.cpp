#include "../include/Utilities.h"

void LoadTexture (const char* path, SDL_Renderer* renderer, SDL_Texture** texture) {
    SDL_Surface* image = IMG_Load(path);
    if (image == NULL) {
        std::cout << "error loading texture!" << std::endl;
        return;
    }
    *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface (image);
}
void MainFunction (SDL_Renderer* renderer) {

    SDL_Event trueEvent;
    SDL_Event* event = &trueEvent; // Событие.

    Vector g = {0, 0.1};            // Вектор ускорения свободного падения.
    Vector nul = {0 ,0};            // Нулевой вектор.
    Vector left = {-3, -1.5};       // Вектор движения влево.
    Vector right = {3, -1.5};       // Вектор движения вправо.
    Vector jump = {0, -5};          // Вектор прыжка.
    Vector shootLeft = {-10, -5};   // Вектор удара влево.
    Vector shootRight = {10, -5};   // Вектор удара вправо.

    Rect temp;  // Переменная для инициализации моделей, коллайдеров, моделей, видов и контроллеров.

    temp.w = 30;
    temp.h = 30;
    temp.x = WINDOWWIDTH / 2;
    temp.y = 200;
    Model* ball = new Model (temp); // Модель мяча.
    temp.w = 30;
    temp.h = 30;
    temp.x = 0;
    temp.y = 0;
    Collider* ballCollider = new Collider (ball, temp); // Коллайдер мяча.
    temp.w = 30;
    temp.h = 30;
    temp.x = 0;
    temp.y = 0;
    ModelView* ballView = new ModelView (renderer, ball, temp, true, "resources/ball.png", SDL_FLIP_NONE); // Вид мяча.

    temp.w = WINDOWWIDTH + 100;
    temp.h = 50;
    temp.x = -50;
    temp.y = WINDOWHIGHT -50;
    Model* ground = new Model (temp); // Модель земли.
    temp.w = WINDOWWIDTH + 100;
    temp.h = 50;
    temp.x = 0;
    temp.y = 0;
    Collider* groundCollider = new Collider (ground, temp); // Коллайдер земли.
    temp.w = WINDOWWIDTH + 100;
    temp.h = 50;
    temp.x = 0;
    temp.y = 0;
    ModelView* groundView = new ModelView (renderer, ground, temp, false, "resources/grass.png", SDL_FLIP_NONE); // Вид земли.

    temp.w = 50;
    temp.h = WINDOWHIGHT + 100;
    temp.x = WINDOWWIDTH;
    temp.y = -50;
    Model* rightWall = new Model (temp);    // Модель правой стены.
    temp.w = 50;
    temp.h = WINDOWHIGHT + 100;
    temp.x = 0;
    temp.y = 0;
    Collider* rightWallCollider = new Collider (rightWall, temp); // Коллайдер правой стены.

    temp.w = 50;
    temp.h = WINDOWHIGHT + 100;
    temp.x = -50;
    temp.y = -50;
    Model* leftWall = new Model (temp);     // Модель левой стены.
    temp.w = 50;
    temp.h = WINDOWHIGHT + 100;
    temp.x = 0;
    temp.y = 0;
    Collider* leftWallCollider = new Collider (leftWall, temp);     // Коллайдер левой стены.

    temp.w = WINDOWWIDTH + 100;
    temp.h = 50;
    temp.x = -50;
    temp.y = -50;
    Model* roof = new Model (temp);     // Модель потолка.
    temp.w = WINDOWWIDTH + 100;
    temp.h = 50;
    temp.x = 0;
    temp.y = 0;
    Collider* roofCollider = new Collider (roof, temp);     // Коллайдер потолка.

    temp.w = WINDOWWIDTH;
    temp.h = WINDOWHIGHT;
    temp.x = 0;
    temp.y = 0;
    Model* background = new Model (temp);   // Модель заднего фона.
    temp.w = WINDOWWIDTH;
    temp.h = WINDOWHIGHT;
    temp.x = 0;
    temp.y = 0;
    ModelView* backgroundView = new ModelView (renderer, background, temp, false, "resources/sky.png", SDL_FLIP_NONE); // Вид заднего фона.

    temp.w = 100;
    temp.h = 200;
    temp.x = WINDOWWIDTH - 150;
    temp.y = WINDOWHIGHT - 250;
    Model* rightGoals = new Model (temp);   // Модель правых ворот.
    temp.w = 100;
    temp.h = 200;
    temp.x = 0;
    temp.y = 0;
    ModelView* rightGoalsView = new ModelView (renderer, rightGoals, temp, false, "resources/footballgoals.png", SDL_FLIP_NONE); // Вид правых ворот.
    temp.w = 150;
    temp.h = 10;
    temp.x = WINDOWWIDTH - 150;
    temp.y = WINDOWHIGHT - 250;
    Model* rightGoalsColliderModelTop = new Model (temp);   // Модель верхнего коллайдера правых ворот.
    temp.w = 150;
    temp.h = 10;
    temp.x = 0;
    temp.y = 0;
    Collider* rightGoalsColliderTop = new Collider (rightGoalsColliderModelTop, temp); // Верхний коллайдер правых ворот.
    temp.w = 10;
    temp.h = 250;
    temp.x = WINDOWWIDTH - 80;
    temp.y = WINDOWHIGHT - 250;
    Model* rightGoalsColliderModelSide = new Model (temp);  // Модель нижнего коллайдера правых ворот.
    temp.w = 10;
    temp.h = 250;
    temp.x = 0;
    temp.y = 0;
    Collider* rightGoalsColliderSide = new Collider (rightGoalsColliderModelSide, temp); // Нижний коллайдер правых ворот.

    temp.w = 100;
    temp.h = 200;
    temp.x = 50;
    temp.y = WINDOWHIGHT - 250;
    Model* leftGoals = new Model (temp);    // Модель левых ворот.
    temp.w = 100;
    temp.h = 200;
    temp.x = 0;
    temp.y = 0;
    ModelView* leftGoalsView = new ModelView (renderer, leftGoals, temp, false, "resources/footballgoals.png", SDL_FLIP_HORIZONTAL); // Вид левых ворот.
    temp.w = 10;
    temp.h = 188;
    temp.x = 60;
    temp.y = WINDOWHIGHT - 250;
    Model* leftGoalsColliderModelSide = new Model (temp);    // Модель верхнего коллайдера левых ворот.
    temp.w = 10;
    temp.h = 188;
    temp.x = 0;
    temp.y = 0;
    Collider* leftGoalsColliderSide = new Collider (leftGoalsColliderModelSide, temp); // Верхний коллайдер левых ворот.
    temp.w = 150;
    temp.h = 10;
    temp.x = 0;
    temp.y = WINDOWHIGHT - 250;
    Model* leftGoalsColliderModelTop = new Model (temp);   // Модель нижнего коллайдера левых ворот.
    temp.w = 150;
    temp.h = 10;
    temp.x = 0;
    temp.y = 0;
    Collider* leftGoalsColliderTop = new Collider (leftGoalsColliderModelTop, temp);  // Нижний коллайдер левых ворот.

    temp.w = 50;
    temp.h = 100;
    temp.x = 150;
    temp.y = WINDOWHIGHT - 250;
    Model* player1 = new Model (temp);  // Модель левого игрока.
    temp.w = 50;
    temp.h = 100;
    temp.x = 0;
    temp.y = 0;
    Collider* player1Collider = new Collider (player1, temp);   // Коллайдер левого игрока.
    temp.w = 70;
    temp.h = 100;
    temp.x = 0;
    temp.y = 0;

    // Массив видов левого игрока.
    ModelView* player1View[] = {    new ModelView (renderer, player1, temp, false, "resources/aguero.png", SDL_FLIP_NONE),
                                    new ModelView (renderer, player1, temp, false, "resources/bale.png", SDL_FLIP_HORIZONTAL),
                                    new ModelView (renderer, player1, temp, false, "resources/delpiero.png", SDL_FLIP_NONE),
                                    new ModelView (renderer, player1, temp, false, "resources/james.png", SDL_FLIP_NONE),
                                    new ModelView (renderer, player1, temp, false, "resources/sterling.png", SDL_FLIP_NONE) };

    temp.w = 50;
    temp.h = 100;
    temp.x = WINDOWWIDTH - 220;
    temp.y = WINDOWHIGHT - 250;
    Model* player2 = new Model (temp);  // Модель правого игрока.
    temp.w = 50;
    temp.h = 100;
    temp.x = 0;
    temp.y = 0;
    Collider* player2Collider = new Collider (player2, temp);   // Коллайдер правого игрока.
    temp.w = 70;
    temp.h = 100;
    temp.x = 0;
    temp.y = 0;

    // Массив видов правого игрока.
    ModelView* player2View[] = {    new ModelView (renderer, player2, temp, false, "resources/aguero.png", SDL_FLIP_HORIZONTAL),
                                    new ModelView (renderer, player2, temp, false, "resources/bale.png", SDL_FLIP_NONE),
                                    new ModelView (renderer, player2, temp, false, "resources/delpiero.png", SDL_FLIP_HORIZONTAL),
                                    new ModelView (renderer, player2, temp, false, "resources/james.png", SDL_FLIP_HORIZONTAL),
                                    new ModelView (renderer, player2, temp, false, "resources/sterling.png", SDL_FLIP_HORIZONTAL) };

    temp.w = 60;
    temp.h = 190;
    temp.x = 85;
    temp.y = WINDOWHIGHT - 240;
    Model* leftGoalsTrigger = new Model (temp);     // Модель триггера левых ворот.
    temp.w = 60;
    temp.h = 190;
    temp.x = 0;
    temp.y = 0;
    Collider* leftGoalsTriggerCollider = new Collider (leftGoalsTrigger, temp);     // Коллайдер триггера левых ворот.

    temp.w = 60;
    temp.h = 190;
    temp.x = WINDOWWIDTH - 145;
    temp.y = WINDOWHIGHT - 240;
    Model* rightGoalsTrigger = new Model (temp);    // Модель триггера правых ворот.
    temp.w = 60;
    temp.h = 190;
    temp.x = 0;
    temp.y = 0;
    Collider* rightGoalsTriggerCollider = new Collider (rightGoalsTrigger, temp);   // Коллайдер триггера правых ворот.

    Base* models[] = {ball, roof, ground, leftWall, rightWall, rightGoals};     // Массив модалей.
    Collider* colliders[] = {groundCollider, rightWallCollider, leftWallCollider, roofCollider, rightGoalsColliderTop, rightGoalsColliderSide, leftGoalsColliderTop, leftGoalsColliderSide}; // Массив коллайдеров.
    Collider* triggers[] = {leftGoalsTriggerCollider, rightGoalsTriggerCollider, player1Collider, player2Collider, ballCollider};   // Массив триггеров.
    ModelView* views[] = {ballView, groundView, backgroundView, rightGoalsView, leftGoalsView}; // Массив видов.

    ControlKeys player1Control = {SDLK_a, SDLK_d, SDLK_w, SDLK_SPACE};          // Клавиши управления игрока слева.
    ControlKeys player2Control = {SDLK_KP_4, SDLK_KP_6, SDLK_KP_8, SDLK_KP_0};  // Клавиши управления игрока справа.

    ControlVectors player1Vectors = {nul, left, right, jump, shootRight};   // Вектора управления игрока слева.
    ControlVectors player2Vectors = {nul, left, right, jump, shootLeft};    // Вектора управления игрока справа.


    Physics* player1Controller = new Controller (player1, event, player1Collider, nul, nul, g, 0.5, colliders, 8, NULL, 0, player1Control, player1Vectors);   // Контроллер игрока слева.
    Physics* player2Controller = new Controller (player2, event, player2Collider, nul, nul, g, 0.5, colliders, 8, NULL, 0, player2Control, player2Vectors);   // Контроллер игрока справа.
    Physics* ballPhysics = new Physics (ball, ballCollider, nul, nul, g, 0.9, colliders, 8, triggers, 5);   // Физическое тело мяч.

    Physics* physics[] = {player1Controller, player2Controller, ballPhysics}; // Массив контроллеров.

    Scoreboard* scores = new Scoreboard(renderer, "resources/fonts/Ubuntu-B.ttf");  // Табло счета.

    int modelCounter1 = 0;  // Номер вида игрока слера.
    int modelCounter2 = 1;  // Номер вида игрока справа.

    // Таймеры перерисовки кадров.
    struct {
        double currentTime;
        double lastTime;
    } PhysicsUpdate;

    struct {
        double currentTime;
        double lastTime;
    } frameUpdate;

    PhysicsUpdate.currentTime = 0;
    PhysicsUpdate.lastTime = 0;
    PhysicsUpdate.currentTime = 0;
    PhysicsUpdate.lastTime = 0;

    for (int i = 0; i < 3; i++)
        physics[i]->Awake();

    bool running = true;
    while (running) {

        PhysicsUpdate.currentTime = SDL_GetTicks();
        if (PhysicsUpdate.currentTime - PhysicsUpdate.lastTime > 5) {
            PhysicsUpdate.lastTime = PhysicsUpdate.currentTime;

            for (int i = 0; i < 8; i++)
                colliders[i]->Update();

            for (int i = 0; i < 5; i++)
                triggers[i]->Update();

            for (int i = 0; i < 3; i++)
                physics[i]->Update();

            if (ballPhysics->OnTriggerEnter(leftGoalsTriggerCollider))
                scores->IncP2Score();

            if (ballPhysics->OnTriggerEnter(rightGoalsTriggerCollider))
                scores->IncP1Score();
        }

        frameUpdate.currentTime = SDL_GetTicks();
        if (frameUpdate.currentTime - frameUpdate.lastTime > 15) {
            frameUpdate.lastTime = frameUpdate.currentTime;

            SDL_RenderClear(renderer);

            for (int i = 0; i < 5; i++)
                views[i]->Update();

            player1View[modelCounter1]->Update();
            player2View[modelCounter2]->Update();

            backgroundView->DrawImage();
            groundView->DrawImage();

            player1View[modelCounter1]->DrawImage();
            player2View[modelCounter2]->DrawImage();

            ballView->DrawImage();
            leftGoalsView->DrawImage();
            rightGoalsView->DrawImage();

            scores->DrawScores();

            SDL_RenderPresent(renderer);
        }

        while (SDL_PollEvent(event)) {

            for (int i = 0; i < 2; i++)
                physics[i]->Action(ballPhysics, ballCollider);

            if (event->key.state == SDL_PRESSED && event->key.repeat == 0) {
                if (event->key.keysym.sym == SDLK_1) {
                    modelCounter1++;
                    if (modelCounter1 > 4)
                        modelCounter1 = 0;
                }
                if (event->key.keysym.sym == SDLK_2) {
                    modelCounter2++;
                    if (modelCounter2 > 4)
                        modelCounter2 = 0;
                }
            }

            if (event->type == SDL_QUIT) {
                running = false;
                return;
            }
        }
    }

    delete ball;
    delete ballCollider;
    delete ballView;
    delete ground;
    delete groundCollider;
    delete groundView;
    delete rightWall;
    delete rightWallCollider;
    delete leftWall;
    delete leftWallCollider;
    delete roof;
    delete roofCollider;
    delete background;
    delete backgroundView;
    delete rightGoals;
    delete rightGoalsView;
    delete rightGoalsColliderModelTop;
    delete rightGoalsColliderTop;
    delete rightGoalsColliderModelSide;
    delete rightGoalsColliderSide;
    delete leftGoals;
    delete leftGoalsView;
    delete leftGoalsColliderModelTop;
    delete leftGoalsColliderTop;
    delete leftGoalsColliderModelSide;
    delete leftGoalsColliderSide;

    delete player1;
    delete player1Collider;
    for (int i = 0; i < 5; i++)
        delete player1View[i];

    delete player2;
    delete player2Collider;
    for (int i = 0; i < 5; i++)
        delete player2View[i];

    delete leftGoalsTrigger;
    delete leftGoalsTriggerCollider;
    delete rightGoalsTrigger;
    delete rightGoalsTriggerCollider;
    delete ballPhysics;
    delete player1Controller;
    delete player2Controller;
    delete scores;
}
