/******************************************************************************/
/*!
\file	View.h
\author Chuk Yih Jou
\brief
only rendering entities
*/
/******************************************************************************/

#ifndef VIEW_H
#define VIEW_H

#include "Model.h"
#include "MasterRenderer.h"

class View
{
private:
    Model *theModel;
    MasterRenderer *render;     // scene has a render to help me render all the stuff

public:
    View(void);
    View(Model *theModel);
    ~View(void);

    void Draw(void);
    void InitRenderer(void);
};

#endif 