/******************************************************************************/
/*!
\file	Weapon.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.h"
#include "InputsController.h"
#include "Vector2.h"

class Weapon : public Entity
{
private:
    float wx;
    Vector3 vx;

    float wy;
    Vector3 vy;

    float wz;
    Vector3 vz;

    Vector2 ShearXY;

    TexturedModel mesh2, mesh3;

    
public:
    Weapon(void);
    Weapon(TexturedModel mesh, Vector3 position, float w, Vector3 v, float scaleX, float scaleY, float scaleZ);
    ~Weapon(void);

    float getWX(void);
    void setWX(float wx);

    Vector3 getVX(void);
    void setVX(Vector3 vx);

    float getWY(void);
    void setWY(float wy);

    Vector3 getVY(void);
    void setVY(Vector3 vy);

    float getWZ(void);
    void setWZ(float wz);

    Vector3 getVZ(void);
    void setVZ(Vector3 vz);

    Vector2 getShearXY(void);
    void setShearXY(Vector2 ShearXY);

    bool renderWeapon;

    void SetSliderandMagazine(TexturedModel mesh2, TexturedModel mesh3);

    TexturedModel getSliderMesh(void);
    TexturedModel getMagazineMesh(void);


    float magazineAni;
    float silderAni;
};

#endif