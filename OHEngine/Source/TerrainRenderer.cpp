#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(void)
{

}

TerrainRenderer::TerrainRenderer(TerrainShader *shader, Mtx44 projection)
{
    this->shader = shader;
    LoadProjection(projection);
}

TerrainRenderer::~TerrainRenderer(void)
{

}

void TerrainRenderer::render(std::vector<Terrain> terrains)
{
    
    for (unsigned int i = 0; i < terrains.size(); i++)
    {
        prepareTerrain(terrains[i]);

        model.LoadIdentity();
        model.PushMatrix();
        loadModelMatrix(terrains[i]);
        glDrawElements(GL_TRIANGLES, terrains[i].getRawModel().getIndexSize(), GL_UNSIGNED_INT, 0);
        model.PopMatrix();

        unbindTexturedModel();
    }
}

void TerrainRenderer::prepareTerrain(Terrain terrain)
{
    unsigned int vaoID = terrain.getRawModel().getVaoID();
    unsigned int textureID = terrain.getTexturedModel().getTextureID();

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

void TerrainRenderer::unbindTexturedModel(void)
{
    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain &terrain)
{
    // transformation is done down here
    model.Translate(terrain.getX(), 0.f, terrain.getZ());
    model.Scale(1.f, 1.f, 1.f);

    shader->load_MVP(projection.Top() * view.Top() * model.Top());
    // end transformation

    if(terrain.getLight())
	{
        shader->load_LightEnabled(terrain.getLight());     // tell shader to enable light

		Mtx44 modelView;  // temp variable
        
		modelView = view.Top() * model.Top();
        shader->load_ModelView(modelView);          // load mv into shader

        shader->load_ModelView_Inverse_Transpose(modelView);

		//load material
        shader->load_Material(terrain.getMaterial());
	}
	else
	{	
		shader->load_LightEnabled(terrain.getLight());     // tell shader to disable light
	}
}

void TerrainRenderer::createViewMatrix(Camera &camera)
{
    //Set view matrix using camera settings
    view.LoadIdentity();
    view.LookAt(
        camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
        camera.getTarget().x, camera.getTarget().y, camera.getTarget().z,
        camera.getUp().x, camera.getUp().y, camera.getUp().z
        );
}

void TerrainRenderer::renderLight(Light *light)
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

void TerrainRenderer::LoadProjection(Mtx44 projection)
{
    this->projection.PushMatrix();
	this->projection.LoadMatrix(projection);
}