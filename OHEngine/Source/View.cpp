/******************************************************************************/
/*!
\file	View.cpp
\author Chuk Yih Jou
\brief
only rendering entities and creating window
*/
/******************************************************************************/

#include "View.h"

View::View(void)
{
}

View::View(Model *theModel)
{
    this->theModel = theModel;
}

void View::InitRenderer(void)
{
    render = new MasterRenderer();
    render->Init();
    render->prepareLight(theModel->light);
}

void View::Draw(void)   
{
    // gather all the datas in Model .. then send to masterRenderer to render

    render->processEntity(theModel->player1);

    for (map<std::string, Entity>::iterator it = theModel->entity.begin(); it != theModel->entity.end(); it++)
    {
        render->processEntity(it->second);
    }
   
    for (map<std::string, Terrain>::iterator it = theModel->terrain.begin(); it != theModel->terrain.end(); it++)
    {
        render->processTerrain(it->second);
    }

    for (map<std::string, TextData>::iterator it = theModel->text.begin(); it != theModel->text.end(); it++)
    {
        render->processText(it->second);
    }

    render->render(theModel->light, theModel->camera);          // render logic start here
}

View::~View(void)
{
    render->cleanUp();      // clean up renderer before delete
    delete render;
}