#include "Material.h"

Material::Material(void)
{
    kShininess = 1.f;
}

Material::~Material(void)
{

}

Component Material::getkAmbient(void)
{
    return kAmbient;
}

void Material::setkAmbient(Component kAmbient)
{
    this->kAmbient = kAmbient;
}

Component Material::getkDiffuse(void)
{
    return kDiffuse;
}

void Material::setkDiffuse(Component kDiffuse)
{
    this->kDiffuse = kDiffuse;
}

Component Material::getkSpecular(void)
{
    return kSpecular;
}

void Material::setkSpecular(Component kSpecular)
{
    this->kSpecular = kSpecular;
}

float Material::getkShininess(void)
{
    return kShininess;
}

void Material::setkShininess(float kShininess)
{
    this->kShininess = kShininess;
}