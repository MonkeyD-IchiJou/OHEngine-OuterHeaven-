/******************************************************************************/
/*!
\file	Player.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "InputsController.h"
#include "terrain.h"

class Player : public Entity
{
private:
    static float RUN_SPEED;
    static float TURN_SPEED;
    static float GRAVITY;
    static float JUMP_POWER;
    static float TERRAIN_HEIGHT;

    bool isInAir;
    float currentSpeed, currentTurnSpeed, upwardSpeed;

    InputsController controller;

    void checkInputs(void);
    void jump(void);

public:
    Player(void);
    Player(TexturedModel mesh, Vector3 position, float w, Vector3 v, float scaleX, float scaleY, float scaleZ);
    ~Player(void);

    void move(const double dt, Terrain &terrain);

    InputsController &getInput(void);

    Vector3 facingDirection;
};

#endif