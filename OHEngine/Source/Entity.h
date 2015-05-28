/******************************************************************************/
/*!
\file	Entity.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef ENTITY_H
#define ENTITY_H

#include "Vector3.h"
#include "TexturedModel.h"
#include "Material.h"

class Entity
{
protected:
    TexturedModel mesh;      // it is supposed to be static .. let me think of a better way to store this
    Material material;
    Vector3 position;
    float w;
    Vector3 v;
    float rotx, roty, rotz, scaleX, scaleY, scaleZ; // TRS transformation variables
    bool enableLight;

    // temp testing
    bool animation;
    int m_currentFrame;

public:
    Entity(void);
    Entity(TexturedModel mesh, Vector3 position, float w, Vector3 v, float scaleX, float scaleY, float scaleZ);
    ~Entity(void);
    
    void increasePosition(Vector3 d);
    void increaseRotation(float rotx, float roty, float rotz);
    void increaseRotation(float w, Vector3 v);
    void increaseScale(float scale);

    TexturedModel getMesh(void);
    void setMesh(TexturedModel mesh);

    Vector3 getPosition(void);
    void setPosition(Vector3 position);
    void setPositionX(float x);
    void setPositionY(float y);
    void setPositionZ(float z);

    float getRotx(void);
    void setRotx(float rotx);

    float getRoty(void);
    void setRoty(float roty);

    float getRotz(void);
    void setRotz(float rotz);

    float getScaleX(void);
    void setScaleX(float scaleX);             

    float getScaleY(void);
    void setScaleY(float scaleY);  

    float getScaleZ(void);
    void setScaleZ(float scaleZ);  

    Material getMaterial(void);
    void setMaterial(Material material);

    float getAngle(void);
    void setAngle(float w);

    Vector3 getRVector(void);
    void setRVector(Vector3 v);

    bool getLight(void);
    void setLightEnable(bool enableLight);

    bool getAnimation(void);
    void setAnimation(bool animation);

    int getCurrentFrame(void);
    void setCurrentFrame(int m_currentFrame);

    bool setup;
    bool lineRender;
    bool renderFog;
};
#endif 