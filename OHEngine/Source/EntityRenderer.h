/******************************************************************************/
/*!
\file	EntityRenderer.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef EntityRenderer_H
#define EntityRenderer_H

#include <map>
#include <vector>
#include "Entity.h"
#include "StaticShader.h"
#include "MatrixStack.h"
#include "Camera.h"

using std::map;
using std::vector;

class EntityRenderer
{
private:
    StaticShaders *shader;

    MS model, view, projection;
    
    void prepareTexturedModel(TexturedModel model);
    void unbindTexturedModel(void);
    void prepareInstance(Entity &entity);

    void createTransformationMatrix(Vector3 translation, float w, Vector3 v, float sx, float sy, float sz);
    void createTransformationMatrixSlerp(Vector3 translation, float w, Vector3 v, float s);

public:
    EntityRenderer(void);
    EntityRenderer(StaticShaders *shader, Mtx44 projection);
    ~EntityRenderer(void);

    void render(map<TexturedModel, vector<Entity>> entities);

    void LoadProjection(Mtx44 projection);
    
    void createViewMatrix(Camera &camera);
    void renderLight(Light *light);
};

#endif