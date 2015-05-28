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
#include "MyApplication.h"

Model::Model(void)
{
    loader = new MeshLoader();
}

void Model::InitModel(void)
{
    reloadTime = false;
    switchWeaponLiao = false;
    countBullet = 15;
    m_gravity.Set(0, -9.8f, 0); //init gravity as 9.8ms-2 downwards
    velociyforGrenade.Set(0, 0, 0);
    throwG = false;

    // init camera
    camera.Init(Vector3(0, 20.f, 0), Vector3(10.f, 0.f, 10.f), Vector3(0, 1, 0));

    MeshInit();
    
    LightInit();

    PlayerInit();

    WeaponInit();

    EntityInit();

    SpriteAnimationInit();

    TerrainInit();

    TextEntityInit();

    UIInit();

    // init the array of bullets
    arrBullets = new CBulletInfo[10];

    collision = false;
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

    // 7th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//grenade.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//T3_Grenade_DIFF.tga");                              // load texture
    meshStorage["BAZOOKA"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

     // 7th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//gunbaby.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//pist_223.tga");                              // load texture
    meshStorage["GUN"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;


     // 7th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//gunslider.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//pist_223.tga");                              // load texture
    meshStorage["GUNSLIDER"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

     // 7th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//magazine.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//pist_223.tga");                              // load texture
    meshStorage["GUNMAGAZINE"] = TexturedModel(*mesh, *texmesh); 

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

    // first mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//swordA.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//arming_sword_2.tga");  
    meshStorage["SWORD"] = TexturedModel(*mesh, *texmesh);  // store rawmesh and texmesh into TexturedModel class

    delete mesh;
    delete texmesh;

    // first mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//swordhandle.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//arming_sword_2_scabbard.tga");  
    meshStorage["SWORDHANDLE"] = TexturedModel(*mesh, *texmesh);  // store rawmesh and texmesh into TexturedModel class

    delete mesh;
    delete texmesh;

    // second mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//Boxman.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//boxman.tga");                              // load texture
    meshStorage["BOXMAN"] = TexturedModel(*mesh, *texmesh); 

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


    // 7th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//grass.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//grass_ao.tga");                              // load texture
    meshStorage["GRASS"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // 7th mesh init
    mesh =  MeshBuilder::GenerateOBJ("OBJ//bazookaBullet.obj");   // load all vbos into vao
    texmesh = loader->loadTexture("Image//bazookatex1.tga");                              // load texture
    meshStorage["BAZOOKABULLET"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;



    // 7th mesh init
    mesh =  MeshBuilder::GenerateCube();   // load all vbos into vao
    texmesh = loader->loadTexture("Image//bowrecurve_D.tga");                              // load texture
    meshStorage["CUBE"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // 7th mesh init
    mesh =  MeshBuilder::GenerateQuad(1);   // load all vbos into vao
    texmesh = loader->loadTexture("Image//bulletui.tga");                              // load texture
    meshStorage["BULLETUI"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // 7th mesh init
    mesh =  MeshBuilder::GenerateQuad(1);   // load all vbos into vao
    texmesh = loader->loadTexture("Image//grass.tga");                              // load texture
    meshStorage["MINIMAP"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;


    // 7th mesh init
    mesh =  MeshBuilder::GenerateQuad(1);   // load all vbos into vao
    texmesh = loader->loadTexture("Image//blood.tga");                              // load texture
    meshStorage["CURSOR"] = TexturedModel(*mesh, *texmesh); 

    delete mesh;
    delete texmesh;

    // 7th mesh init
    mesh =  MeshBuilder::GenerateLine();   // load all vbos into vao
    meshStorage["LINE"] = TexturedModel(*mesh, NULL); 

    delete mesh;

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

    //// init entity
    //tempEntity = Entity(meshStorage["SKYPLANE"], Vector3(0.f, 1000.f, 0), 0.f, Vector3(0.f, 0, 0), 1.f, 1.f, 1.f);      // final stage
    //m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    //m.setkSpecular(Component(1.0f, 1.0f, 1.0f));
    //m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    //m.setkShininess(10.f);
    //tempEntity.setMaterial(m);
    //tempEntity.setLightEnable(false);
    //entity["100E1"] = tempEntity;

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

    tempEntity = Entity(meshStorage["SPACESHIP"], Vector3(320.f, 50.f, 350.f),  0, Vector3(0.f, 1.f, 0), 2.0f, 2.0f, 2.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["900E1"] = tempEntity;


    tempEntity = Entity(meshStorage["JEFF"], Vector3(330.f, 40.f, 350.f),  0, Vector3(0.f, 1.f, 0), 2.0f, 2.0f, 2.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["010E1"] = tempEntity;


    tempEntity = Entity(meshStorage["SWORDHANDLE"], Vector3(340.f, 48.f, 350.f),  0, Vector3(0.f, 1.f, 0), 5.0f, 5.0f, 5.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["110E1"] = tempEntity;

    tempEntity = Entity(meshStorage["SWORD"], Vector3(338.f, 48.f, 350.f),  0, Vector3(0.f, 1.f, 0), 5.0f, 5.0f, 5.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(0.1f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["210E1"] = tempEntity;

    





    //tempEntity = Entity(meshStorage["GRASS"], Vector3(338.f, 47.f, 350.f),  -48.f, Vector3(0.f, 1.f, 0), 1.0f, 1.0f, 1.0f);      // final stage
    //m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    //m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    //m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    //m.setkShininess(1.f);
    //tempEntity.setMaterial(m);
    //tempEntity.setLightEnable(true);
    //entity["310E1"] = tempEntity;




   





    tempEntity = Entity(meshStorage["CUBE"], Vector3(336.f, 48.f, 350.f),  0, Vector3(0.f, 1.f, 0), 0.1f, 10.0f, 0.1f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.0f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["CUBE"] = tempEntity;


    tempEntity = Entity(meshStorage["BAZOOKA"], Vector3(333.f, 23.f, 350.f),  0, Vector3(0.f, 1.f, 0), 5.0f, 5.0f, 5.0f);      // final stage
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.0f);
    tempEntity.setMaterial(m);
    tempEntity.setLightEnable(true);
    entity["grenade"] = tempEntity;

}

void Model::SpriteAnimationInit(void)
{
    Entity tempEntity;

    animation2 = SpriteAnimation(meshStorage["FIRE"], Vector3(5, 20.f, 5),  0, Vector3(0.f, 0, 0), 30.0f, 30.0f, 30.0f, 7, 7);
    animation2.setAnimation(true);
    animation2.setLightEnable(false);
    animation2.renderFog = false;
    animation2.m_anim = new Animation();
    animation2.m_anim->Set(0, 47, 5, 3.f);
    


    animation = SpriteAnimation(meshStorage["CAT"], Vector3(500.f, 50.f, 250.f),  0, Vector3(0.f, 0, 0), 4.f, 4.f, 4.f, 4, 7);
    animation.setAnimation(true);
    animation.setLightEnable(false);
    animation.renderFog = false;
    animation.m_anim = new Animation();
    animation.m_anim->Set(0, 26, 0, 1.f);

    
    animation3 = SpriteAnimation(meshStorage["FLAME"], Vector3(380.f, 15.f, 390.f),  0, Vector3(0.f, 0, 0), 4.f, 4.f, 4.f, 1, 10);
    animation3.setAnimation(true);
    animation3.setLightEnable(false);
    animation3.renderFog = false;
    animation3.m_anim = new Animation();
    animation3.m_anim->Set(0, 9, 0, 1.f);
}


void Model::PlayerInit(void)
{
    Material m;     // just a temporary variable for setting up material

    float height = terrain["100T1"].getHeightOfTerrain(camera.getTarget().x, camera.getTarget().z) + 3.f;
    player1 = Player(meshStorage["BOXMAN"], Vector3(390.f, height, 390.f),  0, Vector3(0.f, 0, 0), 0.5f, 0.5f, 0.5f);
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.1f, 0.1f, 0.1f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.f);
    player1.setMaterial(m);
    player1.setLightEnable(true);
}

void Model::WeaponInit(void)
{
    Material m;     

    bazooka = Weapon(meshStorage["GUN"], Vector3(0.13413f, -0.16895f, -0.52918f),  180.f, Vector3(0.f, 1.f, 0), 0.1f, 0.1f, 0.1f);
    m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    m.setkShininess(1.0f);
    bazooka.setMaterial(m);
    bazooka.setLightEnable(true);
    bazooka.setup = true;

    bazooka.SetSliderandMagazine(meshStorage["GUNSLIDER"], meshStorage["GUNMAGAZINE"]);


    Line = Entity(meshStorage["LINE"], Vector3(0, 0, 0),  0, Vector3(0.f, 0, 0), 0.09f, 0.09f, 0.09f);

    // tempEntity = Entity(meshStorage["BAZOOKA"], Vector3(aa, bb, cc),  180, Vector3(0.f, 1.f, 0), 1.0f, 1.0f, 1.0f);      // final stage
    //m.setkDiffuse(Component(1.0f, 1.0f, 1.0f));
    //m.setkSpecular(Component(0.2f, 0.2f, 0.2f));
    //m.setkAmbient(Component(0.01f, 0.01f, 0.01f));
    //m.setkShininess(1.0f);
    //tempEntity.setMaterial(m);
    //tempEntity.setLightEnable(true);
    //entity["410E1"] = tempEntity;
    //entity["410E1"].setup = true;
}

void Model::TerrainInit(void)
{
    terrain["100T1"] = Terrain(0, 0, *loader, loader->loadMultiTexture("Image//blood.tga"), loader->loadMultiTexture("Image//grass.tga"), "Image//heightmap.raw");
    terrain["100T1"].setLightEnable(true);
}

void Model::TextEntityInit(void)
{// 26.25 13.125
    text["CURSOR1"] = TextData(textMeshStorage["JOKERFONT"], "-", Color(0.f, 1.f, 0.f), 2.f, Vector2(1.7955f + 40.f, 0.15879f + 30.f)); 
    text["CURSOR1"].v = Vector3(0, 0, 1);
    text["CURSOR1"].w = 0.f;

    text["CURSOR2"] = TextData(textMeshStorage["JOKERFONT"], "-", Color(0.f, 1.f, 0.f), 2.f, Vector2(-(1.7955f / 2)  + 40.f, 0.15879f + 30.f)); 
    text["CURSOR2"].v = Vector3(0, 0, 1);
    text["CURSOR2"].w = 0.f;

    text["CURSOR3"] = TextData(textMeshStorage["JOKERFONT"], "-", Color(0.f, 1.f, 0.f), 2.f, Vector2(-0.13093f + 40.f, (1.58622f + 30.f) + 0.47435)); 
    text["CURSOR3"].v = Vector3(0, 0, 1);
    text["CURSOR3"].w = 90.f;

    text["CURSOR4"] = TextData(textMeshStorage["JOKERFONT"], "-", Color(0.f, 1.f, 0.f), 2.f, Vector2(-0.13093f + 40.f, (-0.52874 + 30.f) - 0.64432f)); 
    text["CURSOR4"].v = Vector3(0, 0, 1);
    text["CURSOR4"].w = 90.f;

    text["bulletInfo"] = TextData(textMeshStorage["JOKERFONT"], "15 / ", Color(1.f, 1.f, 1.f), 3.f, Vector2(10.375f, 5.8125f)); 
}

void Model::UIInit(void)
{
    bulletUI = Entity(meshStorage["BULLETUI"], Vector3(5, 5, 0), 0, Vector3(0, 0, 0), 5, 5, 5);
    miniMap = Entity(meshStorage["MINIMAP"], Vector3(10, 50, 0), 0, Vector3(0, 0, 0), 5, 5, 5);
    Cursor = Entity(meshStorage["CURSOR"], Vector3(10, 50, 1), 0, Vector3(0, 0, 0), 1, 1, 1);
}
float tempan = 0;
void Model::Update(const double dt)
{ 
    updateGL(dt);

    if(camera.getCameraType() == TPS_TYPE)
    {
        camera.UpdateTPS(dt, player1);      // update the camera
        player1.move(dt, terrain["100T1"]);
        
        //camera.setTarget(Vector3(player1.getPosition().x, 3.f, player1.getPosition().z));
        camera.setTarget(player1.getPosition());
    }

    else
    {
        camera.UpdateFPS(dt, terrain["100T1"]);      // update the camera
        //light[7].setPosition(camera.getPosition());
    }


    std::ostringstream spos;
	spos.precision(5);
    spos << "15/" << countBullet;// " reloadTime: " << reloadTime << " cc: " << cc << " aaa: " << aaa << " bbb: " << bbb;
    text["bulletInfo"].setString(spos.str());

   

    for(int i = 0 ; i < 10; i++)
    {
        arrBullets[i].Update(dt);
    }

    entity["300E1"].setPosition(arrBullets[0].getPosition());

    // animation update here
    animation.Update(dt);
    
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



    if(!animation2.m_anim->ended)
    {
        animation2.Update(dt);
    }

    else
    {
        animation2.setPosition(Vector3(0, 0, 0));
        collision = false;
    }

    gunAnimation(dt);

    Cursor.setRVector(Vector3(0, 0, 1));
    tempan += camera.yaw;
    Cursor.setAngle(tempan);

    if(throwG == true)
         UpdateGrenade(dt);
}



void Model::switchWeapon(const double dt)
{
    static bool bLButtonState = false;
    if(!bLButtonState &&controller.getKeysInputs('0'))
    {
        bLButtonState = true;
    }

    else if(bLButtonState &&controller.getKeysInputs('0'))
    {  
        bLButtonState = false;
        bazooka.SetSliderandMagazine(meshStorage["NULL"], meshStorage["NULL"]);
        bazooka.setMesh(meshStorage["BAZOOKA"]);
        
        switchWeaponLiao = true;
    }

    if(controller.getKeysInputs('9'))
    {
        bazooka.SetSliderandMagazine(meshStorage["GUNSLIDER"], meshStorage["GUNMAGAZINE"]);
        bazooka.setMesh(meshStorage["GUN"]);
        switchWeaponLiao = false;
    }
}

void Model::gunAnimation(const double dt)
{
    if(!reloadTime)
    {
        gunRotateXWhenFiring(dt);
    
        gunWalking(dt);
    }
    

    else
    {
        gunReloadAni(dt);
    }

    switchWeapon(dt);

    
}

float z = 0;
bool ani = false;
float angle = 0;
bool gunrotate = false;

double timer = 0;
double timer2 = 0;
bool finishRotateAni = false;
void Model::gunRotateXWhenFiring(const double dt)
{
    if(ani == true)
    {
        z += 0.1 * dt;
        Line.setPositionZ(z);
    }

    if(z > 0.02)
    {
        z = 0;
        Line.setPositionZ(0);
        ani = false;
        Line.lineRender = false;
    }

    if(gunrotate == true && finishRotateAni == false)
    {
        timer += dt;
        angle -= dt * 100;

        bazooka.setVX(Vector3(1, 0, 0));
        bazooka.setWX(angle);

        bazooka.silderAni -= dt * 2;

        if(timer > 0.1)
        {
            timer = 0;
            gunrotate = false;
            finishRotateAni = true;
            countBullet--;
        }
    }
    
    else
    {
        angle = 0;
        bazooka.setVX(Vector3(1, 0, 0));
        bazooka.setWX(0);
        bazooka.silderAni = 0;
        
        finishRotateAni = false;
        
    }
}

bool switchliao = false;
float up = 0;
void Model::gunWalking(const double dt)
{
    if(camera.moving == true && switchliao == false)
    {
        up += dt * 0.05;
        bazooka.setPositionZ(up -0.52918f);

        if(up > 0.01)
        {
            switchliao = true;
        }
    }

    if(camera.moving == true && switchliao == true)
    {
        up -= dt * 0.05;
        bazooka.setPositionZ(up -0.52918f );

        if(up < -0.01)
        {
            switchliao = false;
        }
    }

    if(camera.moving == false)
    {
        up = 0;
        bazooka.setPositionZ( -0.52918f );
    }
  
    camera.moving = false;
}

float reloadUp = 0;
float swapMagazineAni = 0;
bool swapLe = false;
bool gunReachTopLe = false;
bool LockandLoad = false;
void Model::gunReloadAni(const double dt)
{
    if(reloadTime == true && gunReachTopLe == false)
    {
        reloadUp += dt * 0.3;
        bazooka.setPositionY(reloadUp - 0.16895f);

        if(reloadUp > 0.1)
        {
            gunReachTopLe = true;
        }
    }

    if(gunReachTopLe == true && swapLe == false)
    {
        swapMagazineAni -= dt * 5;

        bazooka.magazineAni = swapMagazineAni;

        if(swapMagazineAni < -2.0)
        {
            
            swapLe = true;
        }
    }

    if(swapLe == true && LockandLoad == false)
    {
        swapMagazineAni += dt * 5;

        bazooka.magazineAni = swapMagazineAni;

        if(swapMagazineAni > 0)
        {
            LockandLoad = true;
            bazooka.magazineAni = 0;
        }
    }

    if(LockandLoad == true)
    {
        reloadUp -= dt * 0.3;
        bazooka.setPositionY(reloadUp - 0.16895f);

        if(reloadUp < 0)
        {
            bazooka.setPositionY(-0.16895f);
            reloadTime = false;
            
            countBullet = 15;


            reloadUp = 0;
            swapMagazineAni = 0;
            swapLe = false;
            gunReachTopLe = false;
            LockandLoad = false;
        }
    }
}


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
    
}

void Model::UpdatePlayerStatus(const unsigned char key)
{
    player1.getInput().UpdateMyKeysStatus(key);
}


void Model::UpdateWeaponStatus(const unsigned char key)
{
    if(key == WA_FIRE)
    {
        //arrBullets[0].Init(camera.getTarget(), player1.facingDirection, 10.f, 50.f);
        
        if(switchWeaponLiao == true)
        {
            Vector3 dir = camera.getTarget() - camera.getPosition();
            velociyforGrenade.Set(dir.x, dir.y, dir.z);
            entity["grenade"].setPosition(camera.getTarget());
            throwG = true;
        }

        else
        {

            if(countBullet > 0)
            {
                Line.lineRender = true;
                ani = true;
                gunrotate = true;
            }

            else
            {

                reloadTime = true;
            }
        }
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

void Model::UpdateGrenade(const double dt)
{
    if(collision == false)
    {
        Vector3 vel = velociyforGrenade;
        vel += m_gravity * static_cast<float> (dt) * 2; 
        velociyforGrenade.Set(vel.x, vel.y, vel.z);

        Vector3 pos = entity["grenade"].getPosition();
        pos += velociyforGrenade * static_cast<float> (dt) * 2; 
        entity["grenade"].setPosition(pos);
    }

    float terrainHeight = terrain["100T1"].getHeightOfTerrain(entity["grenade"].getPosition().x, entity["grenade"].getPosition().z);
    if(entity["grenade"].getPosition().y <= terrainHeight)
    {
        animation2.setPosition(Vector3(entity["grenade"].getPosition().x, terrainHeight + 15.f, entity["grenade"].getPosition().z));
        animation2.m_anim->ended = false;
        collision = true;
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