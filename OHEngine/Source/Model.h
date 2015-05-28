/******************************************************************************/
/*!
\file	Model.h
\author Chuk Yih Jou
\brief
All rendering datas storage is here, will merge physic framework soon
*/
/******************************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <string>

#include "TextData.h"
#include "StaticShader.h"
#include "terrain.h"
#include "Light.h"
#include "Camera.h"
#include "MeshLoader.h"
#include "Bullet.h"
#include "Player.h"
#include "SpriteAnimation.h"
#include "Weapon.h"

class Model
{
private:
    MeshLoader *loader;         //loader to help me create new buffer objects and distribute them

    void MeshInit(void);        
    void LightInit(void);       
    void PlayerInit(void);
    void SpriteAnimationInit(void);
    void EntityInit(void);
    void WeaponInit(void);
    void TerrainInit(void);
    void TextEntityInit(void);
    void UIInit(void);

    void updateGL(double dt);

public:
    Model(void);
    ~Model(void);

    std::map<std::string, TexturedModel> meshStorage;        // new way to store mesh data
    std::map<std::string, TexturedModel> textMeshStorage;        

    std::map<std::string, Entity> entity;               // new way to store entity, with id name
    std::map<std::string, TextData> text;               // store text with id name
    std::map<std::string, Terrain> terrain;             // store terrain with id name

    InputsController controller;       

    Camera camera;                          // my scene has a camera
    Light light[StaticShaders::MAX_LIGHT];  // my scene has light

    // Array of bullets
    CBulletInfo* arrBullets;

    Player player1;
    SpriteAnimation animation;
    SpriteAnimation animation2;
    SpriteAnimation animation3;


    Entity bulletUI;
    Entity miniMap;
    Entity Cursor;

    Weapon bazooka;
    Entity Line;

    virtual void UpdateCameraStatus(const unsigned char key);   
    virtual void UpdateMouseCameraStatus(const unsigned char key); 
    virtual void UpdateGLStatus(const unsigned char key);           
    virtual void UpdateWeaponStatus(const unsigned char key);   
    virtual void UpdatePlayerStatus(const unsigned char key);
    virtual void UpdateWordsStatus(const unsigned char key);

    virtual void UpdateGrenade(const double dt);

    std::string words;

    void InitModel(void);
    void Update(const double dt);

    enum WEAPON_ACTION
    {
        WA_NIL = 0,
        WA_FIRE,
        WA_RELOAD,
        WA_CHANGEWEAPON,
        WA_TOTAL,
    };

    void gunAnimation(const double dt);
    void gunRotateXWhenFiring(const double dt);
    void gunWalking(const double dt);
    void switchWeapon(const double dt);
    bool switchWeaponLiao;

    void gunReloadAni(const double dt);
    bool reloadTime;
    float countBullet;

    Vector3 velociyforGrenade;
    Vector3 m_gravity;

    bool throwG;

    bool collision;

};

#endif