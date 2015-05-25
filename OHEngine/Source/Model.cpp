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
#include <sstream>

Model::Model(void)
{
    loader = new MeshLoader();
}

void Model::InitModel(void)
{
    // init camera
    camera.Init(Vector3(390.f, 20.f, 390.f), Vector3(150.f, 0.f, 150.f), Vector3(0, 1, 0));

    MeshInit();
    
    LightInit();

    PlayerInit();

    EntityInit();

    SpriteAnimationInit();

    TerrainInit();

    TextEntityInit();

    // init the array of bullets
    arrBullets = new CBulletInfo[10];
}

void Model::MeshInit(void)
{
    Mesh_RawModel *mesh = new Mesh_RawModel();
    Mesh_TexturedModel *texmesh = new Mesh_TexturedModel();

    // 8th mesh init
    mesh =  MeshBuilder::GenerateSpriteAnimation(4, 7);   // load all vbos into vao
    texmesh = loader->loadTexture("Image//man2.tga");                              // load texture
    meshStorage["CAT"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // 8th mesh init
    mesh =  MeshBuilder::GenerateSpriteAnimation(1, 10);   // load all vbos into vao
    texmesh = loader->loadTexture("Image//issacleg.tga");                              // load texture
    meshStorage["FLAME"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;


    // 8th mesh init
    mesh =  MeshBuilder::GenerateSpriteAnimation(7, 7);   // load all vbos into vao
    texmesh = loader->loadTexture("Image//fire.tga");                              // load texture
    meshStorage["FIRE"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // first mesh init
    mesh =  MeshBuilder::GenerateSkyPlane("yo", Color (1,1,1), 128, 300.0f, 2000.0f, 1.0f, 1.0f);//MeshBuilder::GenerateQuad();    // load all vbos into vao
    texmesh = loader->loadTexture("Image//nightsky.tga");                              // load texture                                 
    meshStorage["SKYPLANE"] = TexturedModel(*mesh, *texmesh);  // store rawmesh and texmesh into TexturedModel class

    delete mesh;
    delete texmesh;

    // second mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//Boxman.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//boxman.tga");                              // load texture
    meshStorage["MICROBOT"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // second mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//spaceship.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//ARC170_TXT_VERSION_4_D.tga");                              // load texture
    meshStorage["SPACESHIP"] = TexturedModel(*mesh, *texmesh); 

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

    // 5th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//PyramidHead.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//phblade2_d.tga");                              // load texture
    meshStorage["STREETLAMP"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;
    
    // 6th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//WoodHouse.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//MADEIRA2.tga");                              // load texture
    meshStorage["HOUSE"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;
    

    // 6th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//centipede.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//phblade2_d.tga");                              // load texture
    meshStorage["CENTIPEDE"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // 7th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//rabbit.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//robbierabbit_bloody_d.tga");                              // load texture
    meshStorage["RABBIT"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;


    // 7th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//jeff.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//char_prisonermonster_d.tga");                              // load texture
    meshStorage["JEFF"] = TexturedModel(*mesh, *texmesh); 

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
        light[i].setPower(5.f);
        light[i].setkC(1.0f);
        light[i].setkL(0.01f);
        light[i].setkQ(0.001f);
        light[i].setcosCutoff(cos(Math::DegreeToRadian(45.f)));
        light[i].setcosInner(cos(Math::DegreeToRadian(30.f)));
        light[i].setExponent(3.f);
        light[i].setSpotDirection(Vector3(0.f, 1.f, 0.f));
    }

    light[0].setType(LIGHT_DIRECTIONAL);
    light[0].setPower(0.5f);

    light[1].setColor(Color(1.f, 0, 0));
    light[1].setPosition(Vector3(500.f, 50.f, 250.f));

    light[2].setColor(Color(1.f, 1.f, 0));
    light[2].setPosition(Vector3(260.f, 20.f, 350.f));

    light[3].setColor(Color(1.f, 0, 1.f));
    light[3].setPosition(Vector3(200.f, 20.f, 500.f));

    light[4].setColor(Color(0, 0, 1.f));
    light[4].setPosition(Vector3(300.f, 20.f, -350.f));

    light[5].setColor(Color(1.f, 1.f, 0));
    light[5].setPosition(Vector3(400.f, 20.f, 10.f));

    light[6].setType(LIGHT_SPOT);
    light[6].setPower(1.5f);
    light[6].setColor(Color(1.f, 1.f, 1.f));
    light[6].setPosition(Vector3(350.f, 10.f, 350.f));

    light[7].setColor(Color(1.f, 1.f, 1.f));
    light[7].setPower(1.3f);
    light[7].setPosition(Vector3(400.f, 10.f, 400.f));
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

    tempEntity = Entity(meshStorage["HOUSE"], Vector3(420.f, 10.f, 430.f),  180.f, Vector3(0.f, 1.f, 0), 5.0f, 5.0f, 5.0f);      // final stage
    m.setkSpecular(Component(0.01f, 0.01f, 0.01f));
    m.setkAmbient(Component(0.1f, 0.1f, 0.1f));
    m.setkShininess(1.f);
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

    tempEntity = Entity(meshStorage["STREETLAMP"], Vector3(260.f, 0.f, 330.f),  0.f, Vector3(0.f, 1.f, 0), 3.0f, 3.0f, 3.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(1.0f, 1.0f, 1.0f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(10.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["400E1"] = tempEntity;

    tempEntity = Entity(meshStorage["STREETLAMP"], Vector3(310.f, 10.f, 420.f),  120.f, Vector3(0.f, 1.f, 0), 5.0f, 5.0f, 5.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(1.0f, 1.0f, 1.0f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(10.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["700E1"] = tempEntity;

    tempEntity = Entity(meshStorage["HOUSE"], Vector3(300.f, 0.f, 300.f),  0.f, Vector3(0.f, 1.f, 0), 5.0f, 5.0f, 5.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.01f, 0.01f, 0.01f));
    m.setkAmbient(Component(0.1f, 0.1f, 0.1f));
    m.setkShininess(1.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["500E1"] = tempEntity;


    tempEntity = Entity(meshStorage["CENTIPEDE"], Vector3(350.f, 0.f, 350.f),  -45.f, Vector3(0.f, 1.f, 0), 3.0f, 3.0f, 3.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(1.0f, 1.0f, 1.0f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(10.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["600E1"] = tempEntity;


    tempEntity = Entity(meshStorage["RABBIT"], Vector3(320.f, 2.f, 350.f),  -45.f, Vector3(0.f, 1.f, 0), 2.0f, 2.0f, 2.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["800E1"] = tempEntity;

    tempEntity = Entity(meshStorage["SPACESHIP"], Vector3(320.f, 50.f, 350.f),  -45.f, Vector3(0.f, 1.f, 0), 2.0f, 2.0f, 2.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["900E1"] = tempEntity;


    tempEntity = Entity(meshStorage["JEFF"], Vector3(330.f, 40.f, 350.f),  -45.f, Vector3(0.f, 1.f, 0), 2.0f, 2.0f, 2.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["010E1"] = tempEntity;
}

void Model::SpriteAnimationInit(void)
{
    Entity tempEntity;

    animation2 = SpriteAnimation(meshStorage["FIRE"], Vector3(420.f, 20.f, 390.f),  0, Vector3(0.f, 0, 0), 30.0f, 30.0f, 30.0f, 7, 7);
    animation2.setAnimation(true);
    animation2.setLightEnable(false);

    animation2.m_anim = new Animation();
    animation2.m_anim->Set(0, 47, 0, 3.f);



    animation = SpriteAnimation(meshStorage["CAT"], Vector3(500.f, 50.f, 250.f),  0, Vector3(0.f, 0, 0), 4.f, 4.f, 4.f, 4, 7);
    animation.setAnimation(true);
    animation.setLightEnable(false);

    animation.m_anim = new Animation();
    animation.m_anim->Set(0, 26, 0, 1.f);

    
    animation3 = SpriteAnimation(meshStorage["FLAME"], Vector3(380.f, 15.f, 390.f),  0, Vector3(0.f, 0, 0), 4.f, 4.f, 4.f, 1, 10);
    animation3.setAnimation(true);
    animation3.setLightEnable(false);

    animation3.m_anim = new Animation();
    animation3.m_anim->Set(0, 9, 0, 1.f);
}


void Model::PlayerInit(void)
{
    Entity tempEntity;
    Material m;     // just a temporary variable for setting up material

    float height = terrain["100T1"].getHeightOfTerrain(camera.getTarget().x, camera.getTarget().z) + 3.f;
    player1 = Player(meshStorage["SPACESHIP"], Vector3(390.f, height, 390.f),  0, Vector3(0.f, 0, 0), 0.5f, 0.5f, 0.5f);
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.1f, 0.1f, 0.1f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.f);
    player1.setMaterial(m);
    player1.setLightEnable(true);
}

void Model::TerrainInit(void)
{
    terrain["100T1"] = Terrain(0, 0, *loader, loader->loadMultiTexture("Image//blood.tga"), loader->loadMultiTexture("Image//grass.tga"), "Image//mm.raw");
    terrain["100T1"].setLightEnable(true);
}

void Model::TextEntityInit(void)
{
    text["100X1"] = TextData(textMeshStorage["JOKERFONT"], "FPS: ", Color(1.f, 0.f, 0.f), 3.f, Vector2(10.f, 50.f)); 
}

void Model::Update(const double dt)
{ 
    updateGL(dt);

    if(camera.getCameraType() == TPS_TYPE)
    {
        camera.UpdateTPS(dt, player1);      // update the camera
        player1.move(dt, terrain["100T1"]);
        
        //camera.setTarget(Vector3(player1.getPosition().x, 3.f, player1.getPosition().z));
        camera.setTarget(player1.getPosition());
        //light[7].setPosition(camera.getTarget());
        
    }

    else
    {
        camera.UpdateFPS(dt, terrain["100T1"]);      // update the camera
        light[7].setPosition(camera.getPosition());
    }

    entity["100E1"].setPosition(Vector3(camera.getPosition().x, camera.getPosition().y + 1000.f, camera.getPosition().z));

    std::ostringstream spos;
	spos.precision(5);
	spos << "FPS: " << 1.0/dt;
    text["100X1"].setString(spos.str());


    for(int i = 0 ; i < 10; i++)
    {
        arrBullets[i].Update(dt);
    }

    entity["300E1"].setPosition(arrBullets[0].getPosition());

    // animation update here
    animation.Update(dt);
    animation2.Update(dt);
    animation3.Update(dt);

    Vector3 dir = camera.getPosition() - animation.getPosition();
    Vector3 dir2 = camera.getPosition() - animation2.getPosition();
    Vector3 dir3 = camera.getPosition() - animation3.getPosition();


    animation2.setAngle(Math::RadianToDegree(atan2(dir2.x, dir2.z)));
    animation2.setRVector(Vector3(0, 1, 0));

    animation.setAngle(Math::RadianToDegree(atan2(dir.x, dir.z)));
    animation.setRVector(Vector3(0, 1, 0));

    
    animation3.setAngle(Math::RadianToDegree(atan2(dir3.x, dir3.z)));
    animation3.setRVector(Vector3(0, 1, 0));
}
//static float lights = 0;
void Model::updateGL(double dt)
{
    if(controller.getKeysInputs('1'))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    
    if(controller.getKeysInputs('2'))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if(controller.getKeysInputs('3'))
    {
        camera.setCameraType(TPS_TYPE);
        camera.setPosition(player1.getPosition() + 5.f);
    }
    if(controller.getKeysInputs('4'))
    {
        camera.setCameraType(FPS_TYPE);
        
    }

    if(controller.getKeysInputs('5'))
    {
        float lights = light[0].getPower();
        lights+=0.1f * static_cast<float>(dt);
        light[0].setPower(lights);
    }

    if(controller.getKeysInputs('6'))
    {
        float lights = light[0].getPower();
        lights-=0.1f * static_cast<float>(dt);
        light[0].setPower(lights);
        
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