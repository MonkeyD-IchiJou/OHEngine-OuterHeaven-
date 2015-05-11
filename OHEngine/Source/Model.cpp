/******************************************************************************/
/*!
\file	Model.cpp
\author Chuk Yih Jou
\brief
All rendering datas is here
*/
/******************************************************************************/

#include "Model.h"
#include "MeshBuilder.h"
#include "MyMath.h"
#include <iostream>

Model::Model(void)
{
    loader = new MeshLoader();
}

void Model::InitModel(void)
{
    // init camera
    camera.Init(Vector3(150.f, 20.f, 160.f), Vector3(150.f, 0.f, 150.f), Vector3(0, 1, 0));

    MeshInit();
    
    LightInit();

    PlayerInit();

    EntityInit();

    TerrainInit();

    TextEntityInit();

    // init the array of bullets
    arrBullets = new CBulletInfo[10];
}

void Model::MeshInit(void)
{
    Mesh_RawModel *mesh = new Mesh_RawModel();
    Mesh_TexturedModel *texmesh = new Mesh_TexturedModel();

    // first mesh init
    mesh =  MeshBuilder::GenerateSkyPlane("yo", Color (1,1,1), 128, 300.0f, 2000.0f, 1.0f, 1.0f);//MeshBuilder::GenerateQuad();    // load all vbos into vao
    texmesh = loader->loadTexture("Image//top.tga");                              // load texture                                 
    meshStorage["SKYPLANE"] = TexturedModel(*mesh, *texmesh);  // store rawmesh and texmesh into TexturedModel class

    delete mesh;
    delete texmesh;

    // second mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//MicroRobot.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//sea.tga");                              // load texture
    meshStorage["MICROBOT"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // 3rd mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//bed.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//bed.tga");                              // load texture
    meshStorage["BED"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // 4th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//column1.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//back.tga");                              // load texture
    meshStorage["COLUMN1"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // text init
    mesh = MeshBuilder::GenerateText(16, 16);
    texmesh = loader->loadTexture("Image//MineCraftText.tga");
    textMeshStorage["JOKERFONT"] = TexturedModel(*mesh, *texmesh); 
    
    delete mesh;
    delete texmesh;
}

void Model::LightInit(void)
{
    // light init default
    for (int i = 0; i < StaticShaders::MAX_LIGHT; i++)
    {
        light[i].setType(LIGHT_POINT);
        light[i].setPosition(Vector3(0.f, 20.f, 0));
        light[i].setColor(Color(1, 1, 1));
        light[i].setPower(10.f);
        light[i].setkC(1.f);
        light[i].setkL(0.01f);
        light[i].setkQ(0.001f);
        light[i].setcosCutoff(cos(Math::DegreeToRadian(45.f)));
        light[i].setcosInner(cos(Math::DegreeToRadian(30.f)));
        light[i].setExponent(3.f);
        light[i].setSpotDirection(Vector3(0.f, 1.f, 0.f));
    }

    light[0].setType(LIGHT_DIRECTIONAL);
    light[0].setPower(0.9f);

    light[1].setColor(Color(1.f, 0, 0));
    light[1].setPosition(Vector3(500.f, 20.f, 0));

    light[2].setColor(Color(1.f, 1.f, 0));
    light[2].setPosition(Vector3(100.f, 20.f, 100.f));

    light[3].setColor(Color(1.f, 0, 1.f));
    light[3].setPosition(Vector3(200.f, 20.f, 500.f));

    light[4].setColor(Color(0, 0, 1.f));
    light[4].setPosition(Vector3(300.f, 20.f, 0));

    light[5].setColor(Color(1.f, 1.f, 0));
    light[5].setPosition(Vector3(400.f, 20.f, 10.f));

    light[6].setType(LIGHT_SPOT);
    light[6].setPower(1.5f);
    light[6].setColor(Color(1.f, 1.f, 1.f));
    light[6].setPosition(Vector3(10.f, 20.f, 400.f));

    light[7].setColor(Color(0, 1.f, 0));
    light[7].setPosition(Vector3(10.f, 20.f, 200.f));
}

void Model::EntityInit(void)
{
    Entity tempEntity;
    Material m;     // just a temporary variable for setting up material

    // init entity
    tempEntity = Entity(meshStorage["SKYPLANE"], Vector3(0, 1000.f, 0), 0.f, Vector3(0.f, 0, 0), 1.f, 1.f, 1.f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(1.0f, 1.0f, 1.0f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(10.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(false);
    entity["100E1"] = tempEntity;

    tempEntity = Entity(meshStorage["BED"], Vector3(400.f, 0.f, 500.f),  90.f, Vector3(0.f, 1.f, 0), 15.0f, 15.0f, 15.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(1.0f, 1.0f, 1.0f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(10.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["200E1"] = tempEntity;

    tempEntity = Entity(meshStorage["COLUMN1"], Vector3(0.f, 0.f, 0.f),  90.f, Vector3(0.f, 1.f, 0), 5.0f, 5.0f, 5.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(1.0f, 1.0f, 1.0f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(10.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["300E1"] = tempEntity;
}

void Model::PlayerInit(void)
{
    Entity tempEntity;
    Material m;     // just a temporary variable for setting up material

    float height = terrain["100T1"].getHeightOfTerrain(camera.getTarget().x, camera.getTarget().z) + 3.f;
    player1 = Player(meshStorage["MICROBOT"], Vector3(camera.getTarget().x, height, camera.getTarget().z),  0, Vector3(0.f, 0, 0), 0.5f, 0.5f, 0.5f);
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.1f, 0.1f, 0.1f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.f);
    player1.setMaterial(m);
    player1.setLightEnable(true);
}

void Model::TerrainInit(void)
{
    terrain["100T1"] = Terrain(0, 0, *loader, *loader->loadTexture("Image//moss1.tga"), "Image//heightmap.raw");

    terrain["200T1"] = Terrain(1, 0, *loader, *loader->loadTexture("Image//moss1.tga"), "Image//heightmap.raw");

    terrain["300T1"] = Terrain(0, 1, *loader, *loader->loadTexture("Image//moss1.tga"), "Image//heightmap.raw");

    terrain["400T1"] = Terrain(1, 1, *loader, *loader->loadTexture("Image//moss1.tga"), "Image//heightmap.raw");
}

void Model::TextEntityInit(void)
{
    std::string a;
    char c = 2;
    a.push_back(c);
    text["100X1"] = TextData(textMeshStorage["JOKERFONT"], words, Color(0.f, 0.f, 0.f), 5.f, Vector2(10.f, 10.f)); 
}

void Model::Update(const double dt)
{ 
    updateGL();

    player1.move(dt, terrain["100T1"]);
    camera.Update(dt, player1);      // update the camera
   
    camera.setTarget(player1.getPosition());
    entity["100E1"].setPosition(Vector3(camera.getPosition().x, camera.getPosition().y + 1000.f, camera.getPosition().z));

    for(int i = 0 ; i < 10; i++)
    {
        arrBullets[i].Update(dt);
    }

    text["100X1"];
    entity["300E1"].setPosition(arrBullets[0].getPosition());
}

void Model::updateGL(void)
{
    if(controller.getKeysInputs('1'))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    
    if(controller.getKeysInputs('2'))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Model::UpdatePlayerStatus(const unsigned char key)
{
    player1.getInput().UpdateMyKeysStatus(key);
}

void Model::UpdateWeaponStatus(const unsigned char key)
{
    if(key == WA_FIRE)
    {
        arrBullets[0].Init(camera.getTarget(), player1.facingDirection, 10.f, 50.f);
    }
}

void Model::UpdateCameraStatus(const unsigned char key)
{
    camera.getInputs().UpdateMyKeysStatus(key);
}

void Model::UpdateMouseCameraStatus(const unsigned char key)
{
    camera.getInputs().UpdateMyMouseKeyStatus(key);
}

void Model::UpdateGLStatus(const unsigned char key)
{
    controller.UpdateMyKeysStatus(key);
}

void Model::UpdateWordsStatus(const unsigned char key)
{
    if (key == 8 && text["100X1"].getText().size() > 0)       // if never pressed 8
    {
        text["100X1"].popText();
    }

    if (key != 8)
    {
        text["100X1"].setText(key);
    }
}

Model::~Model(void)
{
    meshStorage.clear();        
    textMeshStorage.clear();        

    entity.clear();               
    text.clear();               
    terrain.clear();             
}