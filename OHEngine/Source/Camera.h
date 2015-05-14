/******************************************************************************/
/*!
\file	Camera.h
\author Chuk Yih Jou
\brief
To store camera position, target and up
*/
/******************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Quaternion.h"
#include "InputsController.h"
#include "Player.h"

/******************************************************************************/
/*!
		Class Camera:
\brief	To store camera position, target and up
*/
/******************************************************************************/

enum CAMERA_TYPE
{
    FPS_TYPE = 0,
    TPS_TYPE,
    FREE_TYPE,
    TOTAL_TYPE
};

class Camera
{
private:
    static float GRAVITY;
    static float JUMP_POWER;
    static float TERRAIN_HEIGHT;

	Vector3 position;
	Vector3 target;
	Vector3 up;

    bool isInAir;
    float upwardSpeed;
    float pitch, yaw;
    static float turnLimit, CAMERA_MOVING_SPEED, MOUSE_SENSITIVITY;
    CAMERA_TYPE CamType;
    Vector3 *point;
    Vector3 *pivot;

    Quaternion q;

    InputsController inputs;

    void RotateAroundThePoint(Vector3 &point, Vector3 &pivot, const float &w, const Vector3 &v);
    void jump(void);

public:
	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
    virtual void UpdateTPS(const double dt, Player &p);
    virtual void UpdateFPS(const double dt, Terrain &terrain);
	virtual void Reset();
    virtual void RotateLeft(const double dt);
    virtual void RotateRight(const double dt);
    virtual void LookUp(const double dt);
    virtual void LookDown(const double dt);
    
    virtual void MoveForward(const double dt);
    virtual void MoveLeft(const double dt);
    virtual void MoveRight(const double dt);
    virtual void MoveBack(const double dt);
    virtual void ZoomIn(const double dt);
    virtual void ZoomOut(const double dt);

    virtual void FollowPlayer(const double dt, Player &p);
    virtual void increasePosition(const Vector3& pos);
    virtual void increaseTarget(const Vector3& tar);

    virtual void MouseControl(const double dt);

    Vector3 getPosition(void);
    void setPosition(Vector3 position);
    void setPositionY(float y);

    Vector3 getTarget(void);
    void setTarget(const Vector3 &Target);

    Vector3 getUp(void);
    void setUp(Vector3 Up);

    CAMERA_TYPE getCameraType(void);
    void setCameraType(CAMERA_TYPE type);

    InputsController& getInputs(void);
};

#endif