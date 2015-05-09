/******************************************************************************/
/*!
\file	Player.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "Player.h"
#include "Quaternion.h"

float Player::RUN_SPEED = 20.f;
float Player::TURN_SPEED = 160.f;
float Player::GRAVITY = -50.f;
float Player::JUMP_POWER = 30.f;
float Player::TERRAIN_HEIGHT = 3.f;

Player::Player(void)
{

}

Player::Player(TexturedModel mesh, Vector3 position, float w, Vector3 v, float scaleX, float scaleY, float scaleZ)
{
    this->mesh = mesh;
    this->position = position;
    this->w = w;
    this->v = v;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->scaleZ = scaleZ;

    currentSpeed = 0;
    currentTurnSpeed = 0;
    upwardSpeed = 0;
    isInAir = false;

    facingDirection.Set(0, 0, 1);
}

Player::~Player(void)
{

}

void Player::move(const double dt, Terrain &terrain)
{
    checkInputs();
    increaseRotation(currentTurnSpeed * static_cast<float>(dt), Vector3(0, 1, 0));
    float distance = currentSpeed * static_cast<float>(dt);
    float dx = distance * sin(Math::DegreeToRadian(w));
    float dz = distance * cos(Math::DegreeToRadian(w));
    increasePosition(Vector3(dx, 0, dz));

    Quaternion q(currentTurnSpeed * static_cast<float>(dt), Vector3(0, 1, 0));
    facingDirection = q * facingDirection;

    upwardSpeed += GRAVITY * static_cast<float>(dt);
    increasePosition(Vector3(0, upwardSpeed * static_cast<float>(dt), 0));
    float terrainHeight = terrain.getHeightOfTerrain(getPosition().x, getPosition().z) + 3.f;
    if(getPosition().y < terrainHeight)
    {
        upwardSpeed = 0;
        isInAir = false;
        setPosition(Vector3(getPosition().x, terrainHeight, getPosition().z));
    }
}

void Player::jump(void)
{
    if(!isInAir)
    {
        this->upwardSpeed = JUMP_POWER;
        isInAir = true;
    }
}

void Player::checkInputs(void)
{
    if(controller.getKeysInputs('w'))
    {
        this->currentSpeed = RUN_SPEED;
    }

    else if(controller.getKeysInputs('s'))
    {
        this->currentSpeed = -RUN_SPEED;
    }

    else
    {
        this->currentSpeed = 0;
    }

    if (controller.getKeysInputs('d'))
    {
        this->currentTurnSpeed = -TURN_SPEED;
    }

    else if(controller.getKeysInputs('a'))
    {
        this->currentTurnSpeed = TURN_SPEED;
    }

    else
    {
        this->currentTurnSpeed = 0;
    }

    if (controller.getKeysInputs(' '))
    {
        jump();
    }
}

InputsController &Player::getInput(void)
{
    return controller;
}