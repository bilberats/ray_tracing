//
// Created by leroy on 06/04/2023.
//
#include "Vector3.h"

#ifndef RAY_TRACING_QUATERNION_H
#define RAY_TRACING_QUATERNION_H


class Quaternion {
public:
    float w;
    Vector3 v;
    Quaternion():v(Vector3()),w(0){}
    Quaternion(float _w,Vector3 _v):w(_w),v(_v){}
    Quaternion conjugate();
    Quaternion normalized();
    void normalize();
    double norm();
    Quaternion inverse();
    float i();
    float j();
    float k();
    void display();

    //Operations
    Quaternion operator+(Quaternion q) const;
    Quaternion& operator+=(Quaternion& q);
    Quaternion operator-(Quaternion q) const;
    Quaternion& operator-=(Quaternion& q);
    Quaternion operator*(Quaternion q) const;
    Quaternion& operator*=(Quaternion& q);
    Quaternion operator*(float scalar) const;
    Quaternion& operator*=(float& scalar);
    Quaternion operator/(Quaternion q) const;
    Quaternion& operator/=(Quaternion& q);
    Quaternion operator/(float scalar) const;
    Quaternion& operator/=(float& scalar);
    Quaternion& operator=(Quaternion& q);

};


#endif //RAY_TRACING_QUATERNION_H
