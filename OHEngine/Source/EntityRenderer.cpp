/******************************************************************************/
/*!
\file	EntityRenderer.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "MyGL.h"
#include "EntityRenderer.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::ifstream;
using std::getline;
using std::string;


EntityRenderer::EntityRenderer(void)
{
}

EntityRenderer::EntityRenderer(StaticShaders *shader, Mtx44 projection)
{
    this->shader = shader;
    LoadProjection(projection);
}

EntityRenderer::~EntityRenderer(void)
{
}

void EntityRenderer::render(map<TexturedModel, vector<Entity>> entities)
{
    map<TexturedModel, vector<Entity>>::iterator it = entities.begin();

    // loading one by one in map .. efficiently
    while(it != entities.end())
    {
        prepareTexturedModel(it->first);
        unsigned int indexSize = it->first.getRawModel().getIndexSize();

        for(unsigned int i = 0; i < it->second.size(); i++)
        {
            model.LoadIdentity();
            model.PushMatrix();
            prepareInstance(it->second[i]);
            GL::DrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
            model.PopMatrix();
        }

        unbindTexturedModel();
        ++it;
    }
}

void EntityRenderer::prepareTexturedModel(TexturedModel model)
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

void EntityRenderer::unbindTexturedModel(void)
{
    GL::DisableVertexAttribArray(0);
	GL::DisableVertexAttribArray(1);
    GL::DisableVertexAttribArray(2);
    GL::DisableVertexAttribArray(3);

    GL::BindTexture(GL_TEXTURE_2D, 0);

    GL::BindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity &entity)
{
    // transformation is done down here
    createTransformationMatrix(entity.getPosition(), entity.getAngle(), entity.getRVector(), entity.getScaleX(), entity.getScaleY(), entity.getScaleZ());

    shader->load_MVP(projection.Top() * view.Top() * model.Top());
    // end transformation

    if(entity.getLight())
	{
        shader->load_LightEnabled(entity.getLight());     // tell shader to enable light

		Mtx44 modelView;  // temp variable
        
		modelView = view.Top() * model.Top();
        shader->load_ModelView(modelView);          // load mv into shader

        shader->load_ModelView_Inverse_Transpose(modelView);

		//load material
        shader->load_Material(entity.getMaterial());
	}
	else
	{	
		shader->load_LightEnabled(entity.getLight());     // tell shader to disable light
	}
}

void EntityRenderer::renderLight(Light *light)
{
    for(int i= 0; i < 8; i++)
    {
        if (light[i].getType() == LIGHT_DIRECTIONAL)
        {
            Vector3 lightDir(light[i].getPosition().x, light[i].getPosition().y, light[i].getPosition().z);
            Vector3 lightDirection_cameraspace = view.Top() * lightDir;
            shader->load_LightDirection(lightDirection_cameraspace, i);
        }

        else if (light[i].getType() == LIGHT_SPOT)
        {
            Position p(light[i].getPosition().x, light[i].getPosition().y, light[i].getPosition().z);
            Position lightPosition_cameraspace = view.Top() * p;
            shader->load_LightDirection(lightPosition_cameraspace, i);

            Vector3 spotDirection_cameraspace = view.Top() * light[i].getSpotDirection();
            shader->load_LightSpotDirection(spotDirection_cameraspace, i);
        }

        else
        {
            Position p(light[i].getPosition().x, light[i].getPosition().y, light[i].getPosition().z);
            Position lightPosition_cameraspace = view.Top() * p;
            shader->load_LightDirection(lightPosition_cameraspace, i);
        }
    }
}

void EntityRenderer::LoadProjection(Mtx44 projection)
{
    this->projection.PushMatrix();
	this->projection.LoadMatrix(projection);
}

void EntityRenderer::createViewMatrix(Camera &camera)
{
    //Set view matrix using camera settings
    view.LoadIdentity();
    view.LookAt(
        camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
        camera.getTarget().x, camera.getTarget().y, camera.getTarget().z,
        camera.getUp().x, camera.getUp().y, camera.getUp().z
        );
}

void EntityRenderer::createTransformationMatrixSlerp(Vector3 translation, float w, Vector3 v, float s)
{
}

void EntityRenderer::createTransformationMatrix(Vector3 translation, float w, Vector3 v, float sx, float sy, float sz)
{
    model.Translate(translation.x, translation.y, translation.z);
    model.QuaternionRotate(w, v);
    model.Scale(sx, sy, sz);
}