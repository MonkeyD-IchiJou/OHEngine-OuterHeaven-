/******************************************************************************/
/*!
\file	EntityRenderer.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "MyGL.h"
#include "LineRenderer.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::ifstream;
using std::getline;
using std::string;


LineRenderer::LineRenderer(void)
{
}

LineRenderer::LineRenderer(LineShader *shader, Mtx44 projection)
{
    this->shader = shader;
    LoadProjection(projection);
}

LineRenderer::~LineRenderer(void)
{
}

void LineRenderer::render(Entity entity)
{
   
    TexturedModel tm = entity.getMesh();

    prepareTexturedModel(tm);
    unsigned int indexSize = tm.getRawModel().getIndexSize();

    model.LoadIdentity();
    model.PushMatrix();

    prepareInstance(entity);

    glDisable(GL_DEPTH_TEST);
    GL::DrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
    glEnable(GL_DEPTH_TEST);

    model.PopMatrix();


    unbindTexturedModel();
    
}

void LineRenderer::prepareTexturedModel(TexturedModel model)
{
    unsigned int vaoID = model.getRawModel().getVaoID();

    GL::BindVertexArray(vaoID);

    GL::EnableVertexAttribArray(0); // 1st attribute buffer : vertices
	GL::EnableVertexAttribArray(1); // 2nd attribute buffer : colors
}

void LineRenderer::unbindTexturedModel(void)
{
    GL::DisableVertexAttribArray(0);
	GL::DisableVertexAttribArray(1);

    GL::BindVertexArray(0);
}

void LineRenderer::prepareInstance(Entity &entity)
{
    // transformation is done down here
    createTransformationMatrix(entity.getPosition(), entity.getAngle(), entity.getRVector(), entity.getScaleX(), entity.getScaleY(), entity.getScaleZ());

   
    view.LoadIdentity();
    shader->load_MVP(projection.Top() *  view.Top() * model.Top());
    // end transformation
}

void LineRenderer::LoadProjection(Mtx44 projection)
{
    this->projection.PushMatrix();
	this->projection.LoadMatrix(projection);
}

void LineRenderer::createViewMatrix(Camera &camera)
{
    //Set view matrix using camera settings
    view.LoadIdentity();
    view.LookAt(
        camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
        camera.getTarget().x, camera.getTarget().y, camera.getTarget().z,
        camera.getUp().x, camera.getUp().y, camera.getUp().z
        );
}

void LineRenderer::createTransformationMatrixSlerp(Vector3 translation, float w, Vector3 v, float s)
{
}

void LineRenderer::createTransformationMatrix(Vector3 translation, float w, Vector3 v, float sx, float sy, float sz)
{
    model.Translate(translation.x, translation.y, translation.z);
    model.QuaternionRotate(w, v);
    //model.QuaternionRotate(-5, Vector3(1, 0, 0));
    model.Scale(sx, sy, sz);
}