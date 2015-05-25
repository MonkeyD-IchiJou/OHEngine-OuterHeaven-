
/******************************************************************************/
/*!
\file	MastererRenderer.cpp
\author Chuk Yih Jou
\brief
Optimised render class to render mesh, main rendering loop is here
*/
/******************************************************************************/

#include "MasterRenderer.h"
#include "MyApplication.h"
#include "MyGL.h"

double MasterRenderer::FOV = 90.0;
double MasterRenderer::ASPECT = 1680.0 / 1050.0;
double MasterRenderer::NEAR_PLANE = 0.1;
double MasterRenderer::FAR_PLANE = 10000.0;
double MasterRenderer::LEFT = 0.0, 
    MasterRenderer::RIGHT = 80.0, 
    MasterRenderer::BOTTOM = 0.0, 
    MasterRenderer::TOP = 60.0, 
    MasterRenderer::NEAR_VAL = -10.0, 
    MasterRenderer::FAR_VAL = 10.0;

MasterRenderer::MasterRenderer(void)
{
    
}

void MasterRenderer::Init(void)
{
    shader = new StaticShaders();
    renderer = new EntityRenderer(shader, createPerspectiveMatrix());

    terrainShader = new TerrainShader();
    terrainRenderer = new TerrainRenderer(terrainShader, createPerspectiveMatrix()); 

    textShader = new TextShader();
    textRenderer = new TextRenderer(textShader, createOrthoMatrix());
    textRenderer->readFile("FontData.csv");

    prepare();
}

void MasterRenderer::cleanUp(void)
{
    shader->CleanUp();
    delete shader;
    delete renderer;

    terrainShader->CleanUp();
    delete terrainShader;
    delete terrainRenderer;

    textShader->CleanUp();
    delete textShader;
    delete textRenderer;

    entities.clear();                          
    terrains.clear();
    texts.clear();
}

MasterRenderer::~MasterRenderer(void)
{
    
}

void MasterRenderer::prepare(void)
{
    // Set background color to dark blue
    GL::ClearColor(0.0f, 0.f, 0.4f, 0.f);

    //Enable back face culling
    GL::Enable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
	GL::DepthFunc(GL_LESS); 

	//Enable back face culling
	GL::Enable(GL_CULL_FACE);

	//Default to fill mode
	GL::PolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GL::Enable(GL_BLEND);

	GL::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MasterRenderer::ready(void)
{
	GL::Clear(GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::processEntity(Entity &entity)
{
    // master plan
    // mission is to group all similar textured mesh in the same group
    // the fastest way
    map<TexturedModel, vector<Entity>>::iterator it = entities.find(entity.getMesh());

    if (it == entities.end())
    {
        // if reach the end.. meaning no similar mesh .. push into a new vector
        vector<Entity> newbatch;
        newbatch.push_back(entity);
        entities[entity.getMesh()] = newbatch;
    }

    else
    {
        // else.. push it into existed vector
        it->second.push_back(entity);
    }
}

void MasterRenderer::processText(TextData &text)
{
    texts.push_back(text);
}

void MasterRenderer::processTerrain(Terrain &terrain)
{
    terrains.push_back(terrain);
}

void MasterRenderer::prepareLight(Light *light)
{
    shader->Start();
    shader->load_Light(light);
    shader->Stop();

    terrainShader->Start();
    terrainShader->load_Light(light);
    terrainShader->Stop();
}

Mtx44 MasterRenderer::createPerspectiveMatrix(void)
{
    Mtx44 projection;
    projection.SetToPerspective(FOV, ASPECT, NEAR_PLANE, FAR_PLANE);
    return projection;
}

Mtx44 MasterRenderer::createOrthoMatrix(void)
{
    Mtx44 projection;
    projection.SetToOrtho(LEFT, RIGHT, BOTTOM, TOP, NEAR_VAL, FAR_VAL);
    return projection;
}

void MasterRenderer::render(Light *light, Camera &camera)
{
    ready();


    // terrain will render first baby
    terrainShader->Start();
    terrainRenderer->LoadProjection(createPerspectiveMatrix());
    terrainRenderer->createViewMatrix(camera);
    terrainRenderer->renderLight(light);
    terrainRenderer->render(terrains);
    terrainShader->Stop();

    shader->Start();
    renderer->LoadProjection(createPerspectiveMatrix());
    renderer->createViewMatrix(camera);         // take note of this one
    renderer->renderLight(light);
    renderer->render(entities);
    shader->Stop();

    

    textShader->Start();
    textRenderer->LoadProjection(createOrthoMatrix());
    textRenderer->createViewMatrix(camera);
    textRenderer->renderText(texts);
    textShader->Stop();

    entities.clear();                           // rmb to clear entities map every single frame
    terrains.clear();
    texts.clear();
}