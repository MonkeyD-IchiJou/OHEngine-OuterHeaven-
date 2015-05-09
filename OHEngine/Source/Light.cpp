/******************************************************************************/
/*!
\file	Light.cpp
\author Chuk Yih Jou
\brief
class to provide all variables for light object
*/
/******************************************************************************/

#include "Light.h"

Light::Light(void)
{

}

Light::~Light(void)
{

}

LIGHT_TYPE Light::getType(void)
{
    return type;
}

void Light::setType(LIGHT_TYPE type)
{
    this->type = type;
}

Vector3 Light::getPosition(void)
{
    return position;
}

void Light::setPosition(Vector3 position)
{
    this->position = position;
}

Color Light::getColor(void)
{
    return color;
}

void Light::setColor(Color color)
{
    this->color = color;
}

Vector3 Light::getSpotDirection(void)
{
    return spotDirection;
}

void Light::setSpotDirection(Vector3 spotDirection)
{
    this->spotDirection = spotDirection;
}

float Light::getPower(void)
{
    return power;
}

void Light::setPower(float power)
{
    this->power = power;
}

float Light::getkC(void)
{
    return kC;
}

void Light::setkC(float kC)
{
    this->kC = kC;
}

float Light::getkL(void)
{
    return kL;
}

void Light::setkL(float kL)
{
    this->kL = kL;
}

float Light::getkQ(void)
{
    return kQ;
}

void Light::setkQ(float kQ)
{
    this->kQ = kQ;
}

float Light::getcosCutoff(void)
{
    return cosCutoff;
}

void Light::setcosCutoff(float cosCutoff)
{
    this->cosCutoff = cosCutoff;
}

float Light::getcosInner(void)
{
    return cosInner;
}

void Light::setcosInner(float cosInner)
{
    this->cosInner = cosInner;
}

float Light::getExponent(void)
{
    return exponent;
}

void Light::setExponent(float exponent)
{
    this->exponent = exponent;
}