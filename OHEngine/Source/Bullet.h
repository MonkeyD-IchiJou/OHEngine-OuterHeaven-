/******************************************************************************/
/*!
\file	Bullet.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef VECTOR_3_H
#define VECTOR_3_H

#include "Vector3.h"

class CBulletInfo
{
protected:
    bool m_bStatus;
    Vector3 position;
    Vector3 direction;
    float speed;
    float lifetime;

public:
    CBulletInfo(void);
    virtual ~CBulletInfo(void);
    
    void Init(const Vector3 position, const Vector3 direction, const float speed, const float lifetime);

    void SetStatus(const bool bStatus);
    bool getStatus(void);

    void SetPosition(const Vector3 position);
    Vector3 getPosition(void);

    void SetDirection(const Vector3 direction);
    Vector3 getDirection(void);

    void SetSpeed(const float speed);
    float getSpeed(void);

    void SetLifetime(const float lifetime);
    float getLifetime(void);

    void Update(const double dt);
};

#endif