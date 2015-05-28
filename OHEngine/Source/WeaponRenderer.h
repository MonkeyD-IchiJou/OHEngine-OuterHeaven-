/******************************************************************************/
/*!
\file	WeaponRenderer.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef WeaponRenderer_H
#define WeaponRenderer_H

#include "Weapon.h"
#include "StaticShader.h"
#include "MatrixStack.h"
#include "Camera.h"


class WeaponRenderer
{
private:
    StaticShaders *shader;

    MS model, view, projection;
    
    void prepareTexturedModel(TexturedModel model);
    void unbindTexturedModel(void);
    void prepareInstance(Weapon &weapon);

    void createTransformationMatrix(Vector3 translation, float w, Vector3 v, float sx, float sy, float sz, float wx, Vector3 vx);
    void createTransformationMatrixSlerp(Vector3 translation, float w, Vector3 v, float s);

    void renderSpecific(TexturedModel mesh);

public:
    WeaponRenderer(void);
    WeaponRenderer(StaticShaders *shader, Mtx44 projection);
    ~WeaponRenderer(void);

    void render(Weapon weapon);

    void LoadProjection(Mtx44 projection);
    
    void createViewMatrix(Camera &camera);
    void renderLight(Light *light);
};

#endif