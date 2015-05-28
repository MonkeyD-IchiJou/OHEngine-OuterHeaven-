/******************************************************************************/
/*!
\file	EntityRenderer.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "MyGL.h"
#include "WeaponRenderer.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::ifstream;
using std::getline;
using std::string;


WeaponRenderer::WeaponRenderer(void)
{
}

WeaponRenderer::WeaponRenderer(StaticShaders *shader, Mtx44 projection)
{
    this->shader = shader;
    LoadProjection(projection);
}

WeaponRenderer::~WeaponRenderer(void)
{
}

void WeaponRenderer::render(Weapon weapon)
{
    glClear(GL_DEPTH_BUFFER_BIT);

    model.LoadIdentity();
    model.PushMatrix();



    createTransformationMatrix(weapon.getPosition(), weapon.getAngle(), weapon.getRVector(), weapon.getScaleX(), weapon.getScaleY(), weapon.getScaleZ(), weapon.getWX(), weapon.getVX());
    prepareInstance(weapon);
    renderSpecific(weapon.getMesh());

    model.PushMatrix();
    model.Translate(0, 0, weapon.silderAni);
    prepareInstance(weapon);
    renderSpecific(weapon.getSliderMesh());
    model.PopMatrix();

    model.PushMatrix();
    model.Translate(0, weapon.magazineAni, 0);
    prepareInstance(weapon);
    renderSpecific(weapon.getMagazineMesh());

    model.PopMatrix();
    model.PopMatrix();
    
}

void WeaponRenderer::renderSpecific(TexturedModel mesh)
{
    prepareTexturedModel(mesh);
    unsigned int indexSize = mesh.getRawModel().getIndexSize();
    GL::DrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
    unbindTexturedModel();
}

void WeaponRenderer::prepareTexturedModel(TexturedModel model)
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

void WeaponRenderer::unbindTexturedModel(void)
{
    GL::DisableVertexAttribArray(0);
	GL::DisableVertexAttribArray(1);
    GL::DisableVertexAttribArray(2);
    GL::DisableVertexAttribArray(3);

    GL::BindTexture(GL_TEXTURE_2D, 0);

    GL::BindVertexArray(0);
}

void WeaponRenderer::prepareInstance(Weapon &weapon)
{
    // transformation is done down here
    //createTransformationMatrix(weapon.getPosition(), weapon.getAngle(), weapon.getRVector(), weapon.getScaleX(), weapon.getScaleY(), weapon.getScaleZ(), weapon.getWX(), weapon.getVX());

   
    view.LoadIdentity();
    shader->load_MVP(projection.Top() *  view.Top() * model.Top());
    // end transformation

    Mtx44 modelView;  // temp variable
    modelView = view.Top() * model.Top();       // week 6
    shader->load_ModelView(modelView);          // load mv into shader

    if(weapon.getLight())
	{
        shader->load_LightEnabled(weapon.getLight());     // tell shader to enable light

        shader->load_ModelView_Inverse_Transpose(modelView.GetInverse().GetTranspose());

		//load material
        shader->load_Material(weapon.getMaterial());
	}
	else
	{	
		shader->load_LightEnabled(weapon.getLight());     // tell shader to disable light
	}
}

void WeaponRenderer::renderLight(Light *light)
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

void WeaponRenderer::LoadProjection(Mtx44 projection)
{
    this->projection.PushMatrix();
	this->projection.LoadMatrix(projection);
}

void WeaponRenderer::createViewMatrix(Camera &camera)
{
    //Set view matrix using camera settings
    view.LoadIdentity();
    view.LookAt(
        camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
        camera.getTarget().x, camera.getTarget().y, camera.getTarget().z,
        camera.getUp().x, camera.getUp().y, camera.getUp().z
        );
}

void WeaponRenderer::createTransformationMatrixSlerp(Vector3 translation, float w, Vector3 v, float s)
{
}

void WeaponRenderer::createTransformationMatrix(Vector3 translation, float w, Vector3 v, float sx, float sy, float sz, float wx, Vector3 vx)
{
    model.Translate(translation.x, translation.y, translation.z);
    model.QuaternionRotate(w, v);
    model.QuaternionRotate(wx, vx);
    model.Scale(sx, sy, sz);
}