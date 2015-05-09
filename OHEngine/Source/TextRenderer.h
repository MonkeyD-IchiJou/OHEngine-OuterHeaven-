/******************************************************************************/
/*!
\file	TextRenderer.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>
#include <vector>
#include "TextShader.h"
#include "MatrixStack.h"
#include "Camera.h"
#include "TextData.h"

class TextRenderer
{
private:
    TextShader *shader;

    MS model, view, projection;

    float totalwidth[256]; 

    void prepareTextDisplaying(TexturedModel model);
    void unbindText(void);
    void createTransformationMatrixForText(Vector2 translation, float size);

public:
    TextRenderer(void);
    TextRenderer(TextShader *shader, Mtx44 projection);
    ~TextRenderer(void);

    void renderText(std::vector<TextData> text);

    void readFile(const char * file_path);

    void LoadProjection(Mtx44 projection);
    void createViewMatrix(Camera &camera);
};

#endif