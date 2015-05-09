/******************************************************************************/
/*!
\file	main.cpp
\author Chuk Yih Jou
\brief
Main program run loop
*/
/******************************************************************************/

#include "Model.h"
#include "View.h"
#include "Controller.h"

int main( void )
{
    Model *theModel = new Model();
    View *theView = new View(theModel);
    Controller *theController= new Controller(theModel, theView);
    theController->RunMainLoop();

    if ( theController != NULL)
	{
		delete theController;
		theController = NULL;
	}
	if ( theView != NULL)
	{
		delete theView;
		theView = NULL;
	}
	if ( theModel != NULL)
	{
		delete theModel;
		theModel = NULL;
	}
}