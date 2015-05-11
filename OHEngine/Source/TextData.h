/******************************************************************************/
/*!
\file	TextData.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef TEXT_DATA_H
#define TEXT_DATA_H

#include "TexturedModel.h"
#include "vertex.h"
#include "Vector2.h"

class TextData
{
private:
    TexturedModel textMesh;
    std::string text;
    Color color;
    float size;
    Vector2 position;

public:
    TextData(void);
    TextData(TexturedModel textMesh, std::string text, Color color, float size, Vector2 position);
    ~TextData(void);

    TexturedModel getTextMesh(void);
    void setTextMesh(TexturedModel textMesh);

    std::string getText(void);
    void setText(char key);
    void popText();

    Color getColor(void);
    void setColor(Color color);

    float getSize(void);
    void setSize(float size);

    Vector2 getPosition(void);
    void setPosition(Vector2 position);

};

#endif