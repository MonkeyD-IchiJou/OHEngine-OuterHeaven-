/******************************************************************************/
/*!
\file	TextRenderer.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "2DRenderer.h"
#include "Utility.h"
#include "MyGL.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::ifstream;
using std::getline;
using std::string;

TwoDRenderer::TwoDRenderer(void)
{

}

TwoDRenderer::TwoDRenderer(TextShader *shader, Mtx44 projection)
{
    this->shader = shader;
    LoadProjection(projection);
}

void TwoDRenderer::prepareTwoDisplaying(TexturedModel model)
{
    unsigned int vaoID = model.getRawModel().getVaoID();
    unsigned int textureID = model.getTexturedModel().getTextureID();

    GL::BindVertexArray(vaoID);

    GL::EnableVertexAttribArray(0); // 1st attribute buffer : vertices
	GL::EnableVertexAttribArray(1); // 2nd attribute buffer : colors
	GL::EnableVertexAttribArray(2); // 3rd attribute buffer : normal
    GL::EnableVertexAttribArray(3); // 4th attribute buffer : texture

    // end transformation
    if(textureID > 0)
	{
        shader->load_ColorTextureEnable(1);
		GL::ActiveTexture(GL_TEXTURE0);
		GL::BindTexture(GL_TEXTURE_2D, textureID);
        shader->load_TextureColor(0);   // this means using the first texture
	}
	else
	{
		shader->load_TextureColor(0);   // this means using the first texture
	}
}

void TwoDRenderer::unbindText(void)
{
    GL::DisableVertexAttribArray(0);
	GL::DisableVertexAttribArray(1);
    GL::DisableVertexAttribArray(2);
    GL::DisableVertexAttribArray(3);

    GL::BindTexture(GL_TEXTURE_2D, 0);

    GL::BindVertexArray(0);
}

void TwoDRenderer::renderTwoD(std::vector<Entity> twoD)
{
    std::vector<Entity>::iterator it = twoD.begin();
    // loading one by one in map .. efficiently
    while(it != twoD.end())
    {
        prepareTwoDisplaying(it->getMesh());
        unsigned int indexSize = it->getMesh().getRawModel().getIndexSize();

        view.PushMatrix();
        view.LoadIdentity();
        model.PushMatrix();
        model.LoadIdentity();

        // transformation for text is here
        createTransformationMatrixForText(it->getPosition(), it->getScaleX(), it->getAngle(), it->getRVector());

        shader->load_MVP(projection.Top() * view.Top() *  model.Top());

        GL::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        model.PopMatrix();
        view.PopMatrix();
        //projection.PopMatrix();

        unbindText();
        ++it;
    }
}

void TwoDRenderer::createTransformationMatrixForText(Vector3 translation, float size, float w, Vector3 v)
{
    model.Translate(translation.x, translation.y, translation.z);
    model.QuaternionRotate(w, v);
    model.Scale(size, size, size);
}

void TwoDRenderer::LoadProjection(Mtx44 projection)
{
    //this->projection.PopMatrix();
    this->projection.PushMatrix();
	this->projection.LoadMatrix(projection);
}

void TwoDRenderer::createViewMatrix(Camera &camera)
{
    //Set view matrix using camera settings
    view.LoadIdentity();
    view.LookAt(
        camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
        camera.getTarget().x, camera.getTarget().y, camera.getTarget().z,
        camera.getUp().x, camera.getUp().y, camera.getUp().z
        );
}

TwoDRenderer::~TwoDRenderer(void)
{

}