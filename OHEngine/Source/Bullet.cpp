/******************************************************************************/
/*!
\file	Bullet.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "Bullet.h"

CBulletInfo::CBulletInfo(void) : m_bStatus(false)
{
}

CBulletInfo::~CBulletInfo(void)
{

}

void CBulletInfo::Init(const Vector3 position, const Vector3 direction, const float speed, const float lifetime)
{
    SetPosition(position);
    SetDirection(direction);
    SetSpeed(speed);
    SetLifetime(lifetime);
    SetStatus(true);
}

void CBulletInfo::SetStatus(const bool bStatus)
{
    this->m_bStatus = bStatus;
}

bool CBulletInfo::getStatus(void)
{
    return m_bStatus;
}

void CBulletInfo::SetPosition(const Vector3 position)
{
    this->position = position;
}

Vector3 CBulletInfo::getPosition(void)
{
    return position;
}

void CBulletInfo::SetDirection(const Vector3 direction)
{
    this->direction = direction;
}

Vector3 CBulletInfo::getDirection(void)
{
    return direction;
}

void CBulletInfo::SetSpeed(const float speed)
{
    this->speed = speed;
}

float CBulletInfo::getSpeed(void)
{
    return speed;
}

void CBulletInfo::SetLifetime(const float lifetime)
{
    this->lifetime = lifetime;
}

float CBulletInfo::getLifetime(void)
{
    return lifetime;
}

void CBulletInfo::Update(const double dt)
{
    // check if the bullet is active
    if(getStatus() == true)
    {
        // Update the position of the bullet
        SetPosition(getPosition() + getDirection() * getSpeed() * static_cast<float>(dt));

        // Update the lifetime
        SetLifetime(getLifetime() - static_cast<float>(dt));

        // check if the lifetime is gone
        if(getLifetime() < 0)
        {
            SetStatus( false);
        }
    }
}