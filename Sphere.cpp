//
// Created by leroy on 05/04/2023.
//
#include <iostream>
#include "Sphere.h"
#include <cmath>

Sphere::Sphere(Sphere &sphere):
Shape(sphere),center(sphere.center),radius(sphere.radius)
{IDTotal++;}


hitInfo Sphere::ray(Vector3 origin,Vector3 rayVector){
    hitInfo infos={false,Vector3(),Vector3(),0,0,0};
    /*Solving a quadratic equation in vector form
    /The equation of a sphere is: ||x-c||^2 = r^2
     /x: point on the sphere
     /c: center point
     /r: radius
    /Equation for a line starting at o: x = o+du
     /x: points on the line
     /o: origin of the line
     /d: distance from the origin of the line
     /u:: direction of line (a non-zero vector)

    /When combining those equations we get the final equation:
    /ad^2 + bd + c = 0  where:
     /a = u * u = ||u||^2
     /b = 2 * [u * (o-c)]
     /c = (o-c)*(o-c) - r^2 = ||o-c||^2 - r^2

    /since u(the ray) here is a unit vector we can simplify:
     /delta = [u * (o-c)]^2 - (||o-c||^2 - r^2) and
     /d = -[u * (o-c)] +/- delta
    /We can now start the computation  */
    Vector3 o_Minus_c =  origin - center;
    double delta = pow((rayVector * o_Minus_c),2)
            - ((pow(o_Minus_c.length(),2) - pow(radius,2)));

    //std::cout << "delta: " << delta << std::endl;
    if(delta<0){
        return infos;
    }

    double d1,d2;
    Vector3 hitPos;
    d1 = -(rayVector * o_Minus_c) - sqrt(delta);
    d2 = -(rayVector * o_Minus_c) + sqrt(delta);
    Vector3 hitPos1,hitPos2;

    if(d1<0 && d2<0){
        return infos;
    }
    hitPos1 = origin + rayVector * d1;
    hitPos2 = origin + rayVector * d2;

    Vector3 v1,v2;
    v2=origin-hitPos2;
    v1=origin-hitPos1;

    if(d1<0){
        hitPos = hitPos2;
    }else if(d2<0){
        hitPos = hitPos1;
    }else if(v1.length() <= v2.length()){
        hitPos = hitPos1;
    }else{
        hitPos = hitPos2;
    }

    infos.hit=true;
    Vector3 normalVector=hitPos-center;
    double distance=(hitPos-origin).length();
    infos.hitPos=hitPos;
    infos.normalVector=normalVector.normal();
    infos.distance=distance;
    //There will be processing on the color later
    infos.materialIndex=materialIndex;
    infos.ID = ID;

    return infos;
}

double Sphere::area() {
    return 4*M_PI*pow(radius,2);
}

Vector3 Sphere::getCenter() {
    return center;
}

float Sphere::getRadius() {
    return radius;
}

void Sphere::setCenter(Vector3 newCenter) {
    center = newCenter;
}

void Sphere::setRadius(float newRadius) {
    radius = newRadius;
}

Sphere *Sphere::clone() {
    return new Sphere(*this);
}



