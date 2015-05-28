/******************************************************************************/
/*!
\file	WeaponRenderer.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef LineRenderer_H
#define LineRenderer_H

#include "Entity.h"
#include "LineShader.h"
#include "MatrixStack.h"
#include "Camera.h"


class LineRenderer
{
private:
    LineShader *shader;

    MS model, view, projection;
    
    void prepareTexturedModel(TexturedModel model);
    void unbindTexturedModel(void);
    void prepareInstance(Entity &entity);

    void createTransformationMatrix(Vector3 translation, float w, Vector3 v, float sx, float sy, float sz);
    void createTransformationMatrixSlerp(Vector3 translation, float w, Vector3 v, float s);

public:
    LineRenderer(void);
    LineRenderer(LineShader *shader, Mtx44 projection);
    ~LineRenderer(void);

    void render(Entity entity);

    void LoadProjection(Mtx44 projection);
    
    void createViewMatrix(Camera &camera);
};

#endif