/******************************************************************************/
/*!
\file	TextRenderer.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "TextRenderer.h"
#include "GL\glew.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::ifstream;
using std::getline;
using std::string;

TextRenderer::TextRenderer(void)
{

}

TextRenderer::TextRenderer(TextShader *shader, Mtx44 projection)
{
    this->shader = shader;
    LoadProjection(projection);
}

void TextRenderer::readFile(const char *file_path)
{
    ifstream datafile(file_path);

    string data;
    string width;
    string offsetwidth;

    int search = 0;
    int afterbasewitdh = 0;
    int in = 0;

    for (int i = 0; i < 256; ++i)
    {
        totalwidth[i] = 0.f;
    }

    do
    {
        search++;
        getline(datafile, data, ',');
        getline(datafile, width, '\n');

        if (search >= 9)
        {
            if (afterbasewitdh < 256)
            {
                totalwidth[in] = std::stof(width.c_str()) / 100.f;
            }

            else
            {
                totalwidth[in - 256] += std::stof(width.c_str()) / 100.f;
            }

            ++in;
            ++afterbasewitdh;
        }


    }while(search !=  520);

    datafile.close();
}

void TextRenderer::prepareTextDisplaying(TexturedModel model)
{
    unsigned int vaoID = model.getRawModel().getVaoID();
    unsigned int textureID = model.getTexturedModel().getTextureID();

    glBindVertexArray(vaoID);

    glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	glEnableVertexAttribArray(2); // 3rd attribute buffer : normal
    glEnableVertexAttribArray(3); // 4th attribute buffer : texture

    // end transformation
    if(textureID > 0)
	{
        shader->load_ColorTextureEnable(1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
        shader->load_TextureColor(0);   // this means using the first texture
	}
	else
	{
		shader->load_TextureColor(0);   // this means using the first texture
	}
}

void TextRenderer::unbindText(void)
{
    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}
float sp = 0;
void TextRenderer::renderText(std::vector<TextData> text)
{
    std::vector<TextData>::iterator it = text.begin();
    // loading one by one in map .. efficiently
    while(it != text.end())
    {
        prepareTextDisplaying(it->getTextMesh());
        unsigned int indexSize = it->getTextMesh().getRawModel().getIndexSize();

        glDisable(GL_DEPTH_TEST);

        view.PushMatrix();
        view.LoadIdentity();
        model.PushMatrix();
        model.LoadIdentity();

        // transformation for text is here
        createTransformationMatrixForText(it->getPosition(), it->getSize());

        shader->load_TextEnabled(true);
        shader->load_TextColor(it->getColor());
        
        for(unsigned i = 0; i < it->getText().length(); ++i)
        {
            Mtx44 characterSpacing;

            if (i > 0)
                sp += totalwidth[it->getText()[i-1]];

            characterSpacing.SetToTranslation(sp, 0, 0); //1.0f is the spacing of each character, you may change this value

            shader->load_MVP(projection.Top() * view.Top() * model.Top() * characterSpacing);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)((unsigned)it->getText()[i] * 6 * sizeof(GLuint)));
        }

        sp = 0;
        model.PopMatrix();
        view.PopMatrix();
        projection.PopMatrix();


        unbindText();
        ++it;
    }

    shader->load_TextEnabled(false);
    glEnable(GL_DEPTH_TEST);
}

void TextRenderer::createTransformationMatrixForText(Vector2 translation, float size)
{
    model.Translate(translation.x, translation.y, 0);
    model.Scale(size, size, size);
}

void TextRenderer::LoadProjection(Mtx44 projection)
{
    this->projection.PushMatrix();
	this->projection.LoadMatrix(projection);
}

void TextRenderer::createViewMatrix(Camera &camera)
{
    //Set view matrix using camera settings
    view.LoadIdentity();
    view.LookAt(
        camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
        camera.getTarget().x, camera.getTarget().y, camera.getTarget().z,
        camera.getUp().x, camera.getUp().y, camera.getUp().z
        );
}

TextRenderer::~TextRenderer(void)
{

}