/******************************************************************************/
/*!
\file	2DRenderer.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef TWOD_RENDERER_H
#define TWOD_RENDERER_H

#include <vector>
#include "TextShader.h"
#include "MatrixStack.h"
#include "Camera.h"
#include "Entity.h"

class TwoDRenderer
{
private:
    TextShader *shader;

    MS model, view, projection;
    
    void prepareTwoDisplaying(TexturedModel model);
    void unbindText(void);
    void createTransformationMatrixForText(Vector3 translation, float size, float w, Vector3 v);

public:
    TwoDRenderer(void);
    TwoDRenderer(TextShader *shader, Mtx44 projection);
    ~TwoDRenderer(void);

    void renderTwoD(std::vector<Entity> twoD);


    void LoadProjection(Mtx44 projection);
    void createViewMatrix(Camera &camera);
};

#endif