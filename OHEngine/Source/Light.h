/******************************************************************************/
/*!
\file	Light.h
\author Chuk Yih Jou
\brief
class to provide all variables for light object
*/
/******************************************************************************/

#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"

/******************************************************************************/
/*!
		Class Light:
\brief	provide Light object variables to set up
*/
/******************************************************************************/

enum LIGHT_TYPE
{
    LIGHT_POINT = 0,
    LIGHT_DIRECTIONAL,
    LIGHT_SPOT,
};

class Light
{
private:
    LIGHT_TYPE type;
	Vector3 position;
	Color color;
	Vector3 spotDirection;
	float power;
	float kC, kL, kQ;
	float cosCutoff;
	float cosInner;
	float exponent;

public:

    Light(void);
    ~Light(void);

    LIGHT_TYPE getType(void);
    void setType(LIGHT_TYPE type);

    Vector3 getPosition(void);
    void setPosition(Vector3 position);

    Color getColor(void);
    void setColor(Color color);

    Vector3 getSpotDirection(void);
    void setSpotDirection(Vector3 spotDirection);

    float getPower(void);
    void setPower(float power);

    float getkC(void);
    void setkC(float kC);

    float getkL(void);
    void setkL(float kL);

    float getkQ(void);
    void setkQ(float kQ);

    float getcosCutoff(void);
    void setcosCutoff(float cosCutoff);

    float getcosInner(void);
    void setcosInner(float cosInner);

    float getExponent(void);
    void setExponent(float exponent);

};

#endif