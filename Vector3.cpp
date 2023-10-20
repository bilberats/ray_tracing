//
// Created by leroy on 04/04/2023.
//
#include <iostream>
#include <cmath>
#include "Vector3.h"
#include "Quaternion.h"


void Vector3::display() const {
    std::cout << "{" << x << "," << y << "," << z << "}" << std::endl;
}

bool Vector3::compare(Vector3 vec) const {
    return x==vec.x && y==vec.y && z==vec.z;
}

float Vector3::length() {
    return sqrt(x*x+y*y+z*z);
}

Vector3 Vector3::normal(){
    float len =length();
    return *this/len;
}

void Vector3::normalize() {
    *this=this->normal();
}

Vector3 Vector3::rotateAroundAxis(float angle,Vector3 axis) {
    Quaternion vectorQuaternion(0,*this);
    Quaternion axisQuaternion(cos(angle/2),axis.normal()*sin(angle/2));


    //axisQuaternion.normalized();
    Quaternion inverse = axisQuaternion.inverse();
    Quaternion rotatedQuaternion= axisQuaternion*vectorQuaternion*inverse;

    return rotatedQuaternion.v;
}

Vector3 Vector3::operator+(Vector3 vec) const{
    return {x+vec.x,y+vec.y,z+vec.z};
}
Vector3& Vector3::operator+=(Vector3& vec){
    x+=vec.x;
    y+=vec.y;
    z+=vec.z;
    return *this;
}

Vector3 Vector3::operator-(Vector3 vec) const{
    return {x-vec.x,y-vec.y,z-vec.z};
}
Vector3 Vector3::operator-() const{
    return {-x, -y, -z};
}
Vector3& Vector3::operator-=(Vector3& vec){
    x-=vec.x;
    y-=vec.y;
    z-=vec.z;
    return *this;
}

Vector3 Vector3::operator/(float scalar) const{
    return {x / scalar, y / scalar, z / scalar};
}
Vector3& Vector3::operator/=(float scalar){
    x/=scalar;
    y/=scalar;
    z/=scalar;
    return *this;
}

Vector3 Vector3::operator*(float scalar) const{
    return {x * scalar, y * scalar, z * scalar};
}
Vector3& Vector3::operator*=(float scalar){
    x*=scalar;
    y*=scalar;
    z*=scalar;
    return *this;
}

double Vector3::operator*(Vector3 vect) const {
    return (x*vect.x+y*vect.y+z*vect.z);
}

Vector3 Vector3::operator^(Vector3 vec) const{
    return {y*vec.z-z*vec.y,
            z*vec.x-x*vec.z,
            x*vec.y-y*vec.x};
}

Vector3& Vector3::operator=(Vector3 vec){
    x=vec.x;
    y=vec.y;
    z=vec.z;
    return *this;
}



