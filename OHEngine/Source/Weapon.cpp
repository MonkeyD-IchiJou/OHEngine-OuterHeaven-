#include "Weapon.h"

Weapon::Weapon(void)
{
    magazineAni = 0;
    silderAni = 0;
}

Weapon::~Weapon(void)
{

}

Weapon::Weapon(TexturedModel mesh, Vector3 position, float w, Vector3 v, float scaleX, float scaleY, float scaleZ) : Entity(mesh, position, w, v, scaleX, scaleY, scaleZ)
{
    magazineAni = 0;
    silderAni = 0;
}

float Weapon::getWX(void)
{
    return wx;
}

void Weapon::setWX(float wx)
{
    this->wx = wx;
}

Vector3 Weapon::getVX(void)
{
    return vx;
}


void Weapon::setVX(Vector3 vx)
{
    this->vx = vx;
}


float Weapon::getWY(void)
{
    return wy;
}


void Weapon::setWY(float wy)
{
    this->wy = wy;
}


Vector3 Weapon::getVY(void)
{
    return vy;
}


void Weapon::setVY(Vector3 vy)
{
    this->vy = vy;
}


float Weapon::getWZ(void)
{
    return wz;
}


void Weapon::setWZ(float wz)
{
    this->wz = wz;
}


Vector3 Weapon::getVZ(void)
{
    return vz;
}


void Weapon::setVZ(Vector3 vz)
{
    this->vz = vz;
}

Vector2 Weapon::getShearXY(void)
{
    return ShearXY;
}


void Weapon::setShearXY(Vector2 ShearXY)
{
    this->ShearXY = ShearXY;
}

void Weapon::SetSliderandMagazine(TexturedModel mesh2, TexturedModel mesh3)
{
    this->mesh2 = mesh2;
    this->mesh3 = mesh3;
}

TexturedModel Weapon::getSliderMesh(void)
{
    return mesh2;
}

TexturedModel Weapon::getMagazineMesh(void)
{
    return mesh3;
}