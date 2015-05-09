#pragma once

#include "Mtx44.h"

class Quaternion
{
public:
    Quaternion(void);
    Quaternion(float a, const Vector3& n);
    ~Quaternion(void);
    
    const Quaternion Inverted() const;
    const Quaternion operator*(const Quaternion& q) const;
    const Vector3 operator*(const Vector3& V) const;

    float Length( void ) const;
    Quaternion Normalized( void ) const throw( DivideByZero );
    Quaternion& Normalize( void ) throw( DivideByZero );

    // convert Quaternion to matrix
    Mtx44 convertToMtx44(void);
    const Quaternion Slerp(const Quaternion& other, float t) const;
    void ToAxisAngle(Vector3& vecAxis, float& flAngle) const;

    float w;
    Vector3 v;
};

