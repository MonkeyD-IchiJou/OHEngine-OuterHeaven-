/******************************************************************************/
/*!
\file	Material.h
\author Chuk Yih Jou
\brief
Contain Component and Material structs
*/
/******************************************************************************/

#ifndef MATERIAL_H
#define MATERIAL_H
/******************************************************************************/
/*!
		Struct Component:
\brief	Set colors component
*/
/******************************************************************************/
struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f) 
	{
        Set(r, g, b);
    }
	void Set(float r, float g, float b) 
	{
        this->r = r; 
        this->g = g; 
        this->b = b;
    }
};

/******************************************************************************/
/*!
		Class Material:
\brief	Provide materials variable / initialise material object
*/
/******************************************************************************/

class Material
{
private:
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;

public:
	Material(void);
    ~Material(void);

    Component getkAmbient(void);
    void setkAmbient(Component kAmbient);

    Component getkDiffuse(void);
    void setkDiffuse(Component kDiffuse);

    Component getkSpecular(void);
    void setkSpecular(Component kSpecular);

    float getkShininess(void);
    void setkShininess(float kShininess);
};


#endif