#include "TerrainRenderer.h"
#include "MyGL.h"

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
        GL::DrawElements(GL_TRIANGLES, terrains[i].getRawModel().getIndexSize(), GL_UNSIGNED_INT, 0);
        model.PopMatrix();

        unbindTexturedModel();
    }
}

void TerrainRenderer::prepareTerrain(Terrain terrain)
{
    unsigned int vaoID = terrain.getRawModel().getVaoID();
    unsigned int textureID[2];
    
    
       textureID[0] = terrain.getTexturedModel().getTextureID();
       textureID[1] = terrain.getTexturedModel().getTextureID2();
    
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
		GL::BindTexture(GL_TEXTURE_2D, textureID[0]);
        shader->load_TextureColor(0);   // this means using the first texture

        shader->load_ColorTextureEnable2(1);
		GL::ActiveTexture(GL_TEXTURE1);
		GL::BindTexture(GL_TEXTURE_2D, textureID[1]);
        shader->load_TextureColor2(1);   // this means using the first texture
    }
	
	else
	{
		shader->load_TextureColor(0);   // this means using the first texture
	}
}

void TerrainRenderer::unbindTexturedModel(void)
{
    GL::DisableVertexAttribArray(0);
	GL::DisableVertexAttribArray(1);
    GL::DisableVertexAttribArray(2);
    GL::DisableVertexAttribArray(3);

    GL::BindTexture(GL_TEXTURE_2D, 0);

    GL::BindVertexArray(0);
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