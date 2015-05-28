/******************************************************************************/
/*!
\file	MastererRenderer.h
\author Chuk Yih Jou
\brief
Optimised render class to render mesh faster
*/
/******************************************************************************/

#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "TextRenderer.h"
#include "WeaponRenderer.h"
#include "LineRenderer.h"
#include "2DRenderer.h"

class MasterRenderer
{
private:
    static double FOV, ASPECT, NEAR_PLANE, FAR_PLANE;
    static double LEFT, RIGHT, BOTTOM, TOP, NEAR_VAL, FAR_VAL;

    StaticShaders *shader;
    EntityRenderer *renderer;

    TerrainShader *terrainShader;
    TerrainRenderer *terrainRenderer;

    TextShader *textShader;
    TextRenderer *textRenderer;

    TwoDRenderer *twodrenderer;

    WeaponRenderer *weaponRenderer;

    LineShader *lineShader;
    LineRenderer *lineRenderer;

    Entity Line;

    map<TexturedModel, vector<Entity>> entities;
    std::vector<Terrain> terrains;
    std::vector<TextData> texts;
    std::vector<Entity> twoD;
    
    Weapon weapon;

    void prepare(void); // make it render it before all the renderer kick in
    void ready(void);   // normally place under scene::render

    Mtx44 createPerspectiveMatrix(double fovy, double aspect, double zNear, double zFar);
    Mtx44 createOrthoMatrix(void);

public:
    MasterRenderer(void);
    ~MasterRenderer(void);
    
    void Init(void);

    void processEntity(Entity &entity);
    void processTerrain(Terrain &terrain);
    void processText(TextData &text);
    void processWeapon(Weapon &weapon);
    void processLine(Entity &Line);
    void processTwoD(Entity &twoD);

    void prepareLight(Light *light);
    void prepareFog();

    void render(Light *light, Camera &camera);
    void cleanUp(void);
};

#endif