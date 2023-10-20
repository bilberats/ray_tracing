//
// Created by leroy on 05/04/2023.
//
#include "Shape.h"

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H


class Sphere: public Shape {
private:
     Vector3 center;
     float radius;
public:
    Sphere(Sphere &sphere);
    Sphere():Shape(),center(Vector3()){}
    Sphere(Vector3 _center,float _radius,int _materialIndex)
    :Shape(_materialIndex),center(_center),radius(_radius){}

    hitInfo ray(Vector3 origin,Vector3 rayVector) override;
    double area() override;
    virtual Sphere* clone() override;
    Vector3 getCenter();
    float getRadius();
    void setCenter(Vector3 newCenter);
    void setRadius(float newRadius);
};


#endif //RAY_TRACING_SPHERE_H
