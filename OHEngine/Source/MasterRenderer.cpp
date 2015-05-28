
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
double MasterRenderer::NEAR_PLANE = 0.10;
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
    renderer = new EntityRenderer(shader, createPerspectiveMatrix(FOV, ASPECT, NEAR_PLANE, FAR_PLANE));

    terrainShader = new TerrainShader();
    terrainRenderer = new TerrainRenderer(terrainShader, createPerspectiveMatrix(FOV, ASPECT, NEAR_PLANE, FAR_PLANE)); 

    textShader = new TextShader();
    textRenderer = new TextRenderer(textShader, createOrthoMatrix());
    textRenderer->readFile("FontData.csv");

    twodrenderer = new TwoDRenderer(textShader, createOrthoMatrix());

    weaponRenderer = new WeaponRenderer(shader, createPerspectiveMatrix(FOV, ASPECT, NEAR_PLANE, FAR_PLANE));

    lineShader = new LineShader();
    lineRenderer = new LineRenderer(lineShader, createPerspectiveMatrix(FOV, ASPECT, NEAR_PLANE, FAR_PLANE));

    prepare();
    prepareFog();
    
}

void MasterRenderer::cleanUp(void)
{
    shader->CleanUp();
    delete shader;
    delete renderer;
    delete weaponRenderer;


    lineShader->CleanUp();
    delete lineShader;
    delete lineRenderer;


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
    GL::ClearColor(0.5f, 0.5f, 0.5f, 0.f);

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

void MasterRenderer::prepareFog(void)
{
    terrainShader->Start();
    terrainShader->load_FogColor(Color(0.5f, 0.5f, 0.5f));
    terrainShader->load_FogStart(1.f);
    terrainShader->load_FogEnd(500);
    terrainShader->load_FogDensity(0.0095f);
    terrainShader->load_FogType(2);
    terrainShader->load_FogEnabled(true);
    terrainShader->Stop();


    shader->Start();
    shader->load_FogColor(Color(0.5f, 0.5f, 0.5f));
    shader->load_FogStart(1.f);
    shader->load_FogEnd(500);
    shader->load_FogDensity(0.0095f);
    shader->load_FogType(2);
    shader->load_FogEnabled(true);
    shader->Stop();
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

void MasterRenderer::processWeapon(Weapon &weapon)
{
    this->weapon = weapon;
}

void MasterRenderer::processLine(Entity &Line)
{
    this->Line = Line;
}

void MasterRenderer::processTwoD(Entity &twoD)
{
    this->twoD.push_back(twoD);
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

Mtx44 MasterRenderer::createPerspectiveMatrix(double fovy, double aspect, double zNear, double zFar)
{
    Mtx44 projection;
    projection.SetToPerspective( fovy,  aspect,  zNear,  zFar);
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
    terrainRenderer->LoadProjection(createPerspectiveMatrix(FOV, ASPECT, NEAR_PLANE, FAR_PLANE));
    terrainRenderer->createViewMatrix(camera);
    terrainRenderer->renderLight(light);
    terrainRenderer->render(terrains);
    terrainShader->Stop();

    shader->Start();
    renderer->LoadProjection(createPerspectiveMatrix(FOV, ASPECT, NEAR_PLANE, FAR_PLANE));
    renderer->createViewMatrix(camera);         // take note of this one
    renderer->renderLight(light);
    renderer->render(entities);

    // 47.5 for ak .. 60 for bazooka
    
    weaponRenderer->LoadProjection(createPerspectiveMatrix(40, ASPECT, 0.01, FAR_PLANE));
    weaponRenderer->createViewMatrix(camera);         // take note of this one
    weaponRenderer->renderLight(light);
    weaponRenderer->render(weapon);

    shader->Stop();

    

    textShader->Start();
    textRenderer->LoadProjection(createOrthoMatrix());
    textRenderer->createViewMatrix(camera);
    textRenderer->renderText(texts);

    twodrenderer->LoadProjection(createOrthoMatrix());
    twodrenderer->createViewMatrix(camera);
    twodrenderer->renderTwoD(twoD);

    textShader->Stop();

    
    lineShader->Start();
    lineRenderer->LoadProjection(createPerspectiveMatrix(40, ASPECT, 0.01, FAR_PLANE));
    lineRenderer->createViewMatrix(camera);         // take note of this one
    lineRenderer->render(Line);
    lineShader->Stop();

    entities.clear();                           // rmb to clear entities map every single frame
    terrains.clear();
    texts.clear();
    twoD.clear();
}