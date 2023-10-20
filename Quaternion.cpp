//
// Created by leroy on 06/04/2023.
//
#include <iostream>
#include <cmath>
#include "Quaternion.h"

float Quaternion::i() {
    return v.x;
}
float Quaternion::j() {
    return v.y;
}
float Quaternion::k() {
    return v.z;
}

Quaternion Quaternion::conjugate() {
    return Quaternion(w,-v);
}

double Quaternion::norm() {
    return sqrt(pow(w,2)+pow(v.x,2)+pow(v.y,2)+pow(v.z,2));
}

Quaternion Quaternion::normalized() {
    double norm=this->norm();
    return Quaternion(w/norm,v/norm);
}

void Quaternion::normalize(){
    double norm=this->norm();
    w/=norm;
    v/=norm;
}

Quaternion Quaternion::inverse() {
    double norm=this->norm();
    return this->conjugate()/pow(norm,2);
}

void Quaternion::display() {
    std::cout << "{" << w << ",{" << v.x << "," << v.y << "," << v.z << "}}" << std::endl;
}

Quaternion Quaternion::operator+(Quaternion q) const {
    return Quaternion(w+q.w,v+q.v);
}

Quaternion &Quaternion::operator+=(Quaternion &q) {
    w+=q.w;
    v+=q.v;
    return *this;
}

Quaternion Quaternion::operator-(Quaternion q) const {
    return Quaternion(w-q.w,v-q.v);
}

Quaternion &Quaternion::operator-=(Quaternion &q) {
    w-=q.w;
    v-=q.v;
    return *this;
}

Quaternion Quaternion::operator*(Quaternion q) const{
    float scalar=w*q.w-v*q.v;
    Vector3 vect=q.v*w + v*q.w;
    Vector3 crossProduct= v^q.v;
    vect += crossProduct;
    return Quaternion(scalar,vect);
}

Quaternion &Quaternion::operator*=(Quaternion &q) {
    w=w*q.w-v*q.v;
    Vector3 vect=q.v*w + v*q.w;
    vect = vect + v^q.v;
    v=vect;
    return *this;
}

Quaternion Quaternion::operator*(float scalar) const {
    return Quaternion(w*scalar,v*scalar);
}

Quaternion &Quaternion::operator*=(float &scalar) {
    w*=scalar;
    v*=scalar;
    return *this;
}

Quaternion Quaternion::operator/(Quaternion q) const {
    return *this * q.inverse();
}

Quaternion &Quaternion::operator/=(Quaternion &q) {
    double norm= this->norm();
    w=this->conjugate().w/pow(norm,2);
    v=this->conjugate().v/pow(norm,2);
    return *this;
}

Quaternion Quaternion::operator/(float scalar) const {
    return Quaternion(w/scalar,v/scalar);
}

Quaternion &Quaternion::operator/=(float &scalar) {
    w/=scalar;
    v/=scalar;
    return *this;
}

Quaternion &Quaternion::operator=(Quaternion &q) {
    w=q.w;
    v=q.v;
    return *this;
}











