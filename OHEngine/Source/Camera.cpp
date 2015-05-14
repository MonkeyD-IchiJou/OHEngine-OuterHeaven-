/******************************************************************************/
/*!
\file	Camera.cpp
\author Chuk Yih Jou
\brief
Camera funtions that calculate and return the latest position of the camera
*/
/******************************************************************************/
#include "Camera.h"
#include "Mtx44.h"
#include "Controller.h"

float Camera::GRAVITY = -50.f;
float Camera::JUMP_POWER = 30.f;
float Camera::TERRAIN_HEIGHT = 5.f;

float Camera::CAMERA_MOVING_SPEED = 15.f;
float Camera::turnLimit = 0;
float Camera::MOUSE_SENSITIVITY = 500.f;

Camera::Camera()
{
	Reset();
}

Camera::~Camera()
{
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;

    yaw = pitch = 0;
    turnLimit = (position - target).Length();

    point = new Vector3();
    pivot = new Vector3();

    upwardSpeed = 0;

    setCameraType(FPS_TYPE);
}

void Camera::Reset()
{
	position.Set(1, 0, 0);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);
}

void Camera::increasePosition(const Vector3& pos)
{
    position.x += pos.x;
    position.z += pos.z;
    position.y += pos.y;
}

void Camera::increaseTarget(const Vector3& tar)
{
    target.y += tar.y;
}

void Camera::FollowPlayer(const double dt, Player &p)
{
    if (inputs.getKeysInputs('w') == true)
    {
        position += p.facingDirection * (float)dt * 20.f;
    }

    if (inputs.getKeysInputs('s') == true)
    {
        position -= p.facingDirection * (float)dt * 20.f;
    }

}

void Camera::UpdateTPS(const double dt, Player &p)
{
    FollowPlayer(dt, p);

    if (inputs.getMouseInputs(InputsController::SCROLL_UP) == true)
    {
        ZoomIn(dt);
    }

    if (inputs.getMouseInputs(InputsController::SCROLL_DOWN) == true)
    {
        ZoomOut(dt);
    }

    

    MouseControl(dt);
}

void Camera::UpdateFPS(const double dt, Terrain &terrain)
{
    if (inputs.getMouseInputs(InputsController::SCROLL_UP) == true)
    {
        ZoomIn(dt);
    }

    if (inputs.getMouseInputs(InputsController::SCROLL_DOWN) == true)
    {
        ZoomOut(dt);
    }

    if (inputs.getKeysInputs('w') == true)
    {
        MoveForward(dt);
    }

    if (inputs.getKeysInputs('a') == true)
    {
        MoveLeft(dt);
    }

    if (inputs.getKeysInputs('s') == true)
    {
        MoveBack(dt);
    }

    if (inputs.getKeysInputs('d') == true)
    {
        MoveRight(dt);
    }

    upwardSpeed += GRAVITY * static_cast<float>(dt);
    increasePosition(Vector3(0, upwardSpeed * static_cast<float>(dt), 0));
    
    float terrainHeight = terrain.getHeightOfTerrain(getPosition().x, getPosition().z) + TERRAIN_HEIGHT;

    if(getPosition().y < terrainHeight)
    {
        upwardSpeed = 0;
        isInAir = false;
        setPosition(Vector3(getPosition().x, terrainHeight, getPosition().z));
    }

    if (inputs.getKeysInputs(' '))
    {
        jump();
        target.y += upwardSpeed * static_cast<float>(dt);
    }

    MouseControl(dt);
}

void Camera::jump(void)
{
    if(!isInAir)
    {
        this->upwardSpeed = JUMP_POWER;
        isInAir = true;
    }
}

void Camera::setPositionY(float y)
{
    position.y = y + TERRAIN_HEIGHT;
}

void Camera::MoveForward(const double dt)
{
    Vector3 view = (target - position).Normalized();
    position.x += view.x * CAMERA_MOVING_SPEED * (float)dt;
    position.z += view.z * CAMERA_MOVING_SPEED * (float)dt;
    target.x += view.x * CAMERA_MOVING_SPEED * (float)dt;
    target.z += view.z * CAMERA_MOVING_SPEED * (float)dt;
}

void Camera::MoveLeft(const double dt)
{

    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    position.x -= right.x * CAMERA_MOVING_SPEED * (float)dt;
    position.z -= right.z * CAMERA_MOVING_SPEED * (float)dt;
    target.x -= right.x * CAMERA_MOVING_SPEED * (float)dt;
    target.z -= right.z * CAMERA_MOVING_SPEED * (float)dt;
}

void Camera::MoveRight(const double dt)
{

    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    position.x += right.x * CAMERA_MOVING_SPEED * (float)dt;
    position.z += right.z * CAMERA_MOVING_SPEED * (float)dt;
    target.x += right.x * CAMERA_MOVING_SPEED * (float)dt;
    target.z += right.z * CAMERA_MOVING_SPEED * (float)dt;

}

void Camera::MoveBack(const double dt)
{

    Vector3 view = (target - position).Normalized();
    position.x -= view.x * CAMERA_MOVING_SPEED * (float)dt;
    position.z -= view.z * CAMERA_MOVING_SPEED * (float)dt;
    target.x -= view.x * CAMERA_MOVING_SPEED * (float)dt;
    target.z -= view.z * CAMERA_MOVING_SPEED * (float)dt;

}

void Camera::RotateAroundThePoint(Vector3 &point, Vector3 &pivot, const float &w, const Vector3 &v)
{
    q = Quaternion(w, v);
   
    Vector3 dir = point - pivot;
    dir = q * dir;
    point = dir + pivot;
}

void Camera::RotateLeft(const double dt)
{
    yaw = (float)(-MOUSE_SENSITIVITY * (float)dt);
    RotateAroundThePoint(position, target, yaw, up);
}

void Camera::RotateRight(const double dt)
{  
    yaw = (float)(MOUSE_SENSITIVITY * (float)dt);
    RotateAroundThePoint(position, target, yaw, up);
}

void Camera::LookUp(const double dt)
{
    Vector3 view = (position - target).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();

    pitch = (float)(dt) * MOUSE_SENSITIVITY;
    
    RotateAroundThePoint(position, target, pitch, right);
}

void Camera::LookDown(const double dt)
{
    //// first person
    //float pitch = (float)(-100.f * (float)dt);
    //q = Quaternion(pitch, right);
    //Vector3 dir = target - position;
    //dir = q * dir;
    //target = dir + position;









    ////third person
    //Vector3 view = (*point - *pivot).Normalized();
    //Vector3 right = view.Cross(up);
    //right.y = 0;
    //right.Normalize();

    //pitch = -(float)(dt) * MOUSE_SENSITIVITY;
    //std::cout << point->y << ", " << (*point - *pivot).Length() << std::endl;
  
    //
    //if(point->y > -turnLimit + turnDownLimit)
    //    RotateAroundThePoint(*point, *pivot, pitch, right);
}

void Camera::ZoomIn(const double dt)
{
    Vector3 view = (target - position).Normalized();
    position += view;
    turnLimit = (target - position).Length();
}
void Camera::ZoomOut(const double dt)
{
    Vector3 view = (target - position).Normalized();
    position -= view;
    turnLimit = (target - position).Length();
}

void Camera::MouseControl(const double dt)
{
    // up and down
    {
        Vector3 view = (target - position).Normalized();
        Vector3 right = view.Cross(up);
        right.y = 0;
        right.Normalize();

        pitch = (float)(dt* Controller::camera_pitch) * -MOUSE_SENSITIVITY;

        RotateAroundThePoint(*point, *pivot, pitch, right);
    }

    // left and right
    {
        yaw = MOUSE_SENSITIVITY * (float)(dt * Controller::camera_yaw);

        RotateAroundThePoint(*point, *pivot, yaw, up);
    }
}

Vector3 Camera::getPosition(void)
{
    return position;
}

void Camera::setPosition(Vector3 position)
{
    this->position = position;
}

Vector3 Camera::getTarget(void)
{
    return target;
}

void Camera::setTarget(const Vector3 &Target)
{
    this->target = Target;
}

Vector3 Camera::getUp(void)
{
    return up;
}

void Camera::setUp(Vector3 Up)
{
    this->up = Up;
}

CAMERA_TYPE Camera::getCameraType(void)
{
    return CamType;
}

void Camera::setCameraType(CAMERA_TYPE CameType)
{
    this->CamType = CameType;

    if (CameType == FPS_TYPE)
    {
        point = &this->target;
        pivot = &this->position;
    }

    else if(CameType == TPS_TYPE)
    {
        point = &this->position;
        pivot = &this->target;
    }

    else
    {
        point = &this->position;
        pivot = &this->target;
    }
}

InputsController& Camera::getInputs(void)
{
    return inputs;
}