/******************************************************************************/
/*!
\file	Entity.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "Entity.h"

Entity::Entity(void)
{
    enableLight = true;
}

Entity::Entity(TexturedModel mesh, Vector3 position, float w, Vector3 v, float scaleX, float scaleY, float scaleZ)
{
    this->mesh = mesh;
    this->position = position;
    this->w = w;
    this->v = v;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->scaleZ = scaleZ;
}

Entity::~Entity(void)
{
}

void Entity::increasePosition(Vector3 d)
{
    position += d;
}

void Entity::increaseRotation(float rotx, float roty, float rotz)
{
    this->rotx += rotx;
    this->roty += roty;
    this->rotz += rotz;
}

void Entity::increaseRotation(float w, Vector3 v)
{
    this->w += w;
    this->v = v;
}

TexturedModel Entity::getMesh(void)
{
    return mesh;
}

void Entity::setMesh(TexturedModel mesh)
{
    this->mesh = mesh;
}

Vector3 Entity::getPosition(void)
{
    return position;
}

void Entity::setPosition(Vector3 position)
{
    this->position = position;
}

float Entity::getRotx(void)
{
    return rotx;
}

void Entity::setRotx(float rotx)
{
    this->rotx = rotx;
}

float Entity::getRoty(void)
{
    return roty;
}

void Entity::setRoty(float roty)
{
    this->roty = roty;
}

float Entity::getRotz(void)
{
    return rotz;
}

void Entity::setRotz(float rotz)
{
    this->rotz = rotz;
}

float Entity::getScaleX(void)
{
    return scaleX;
}

void Entity::setScaleX(float scaleX)
{
    this->scaleX = scaleX;
}

float Entity::getScaleY(void)
{
    return scaleY;
}

void Entity::setScaleY(float scaleY)
{
    this->scaleY = scaleY;
}

float Entity::getScaleZ(void)
{
    return scaleZ;
}

void Entity::setScaleZ(float scaleZ)
{
    this->scaleZ = scaleZ;
}

Material Entity::getMaterial(void)
{
    return material;
}

void Entity::setMaterial(Material material)
{
    this->material = material;
}

bool Entity::getLight(void)
{
    return enableLight;
}

void Entity::setLightEnable(bool enableLight)
{
    this->enableLight = enableLight;
}

float Entity::getAngle(void)
{
    return w;
}

void Entity::setAngle(float w)
{
    this->w = w;
}

Vector3 Entity::getRVector(void)
{
    return v;
}

void Entity::setRVector(Vector3 v)
{
    this->v = v;
}