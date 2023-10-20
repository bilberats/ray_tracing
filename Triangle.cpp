//
// Created by leroy on 18/04/2023.
//

#include "Triangle.h"
#include <iostream>


Triangle *Triangle::clone() {
    return new Triangle(*this);
}
/*
hitInfo Triangle::ray(Vector3 camPos, Vector3 rayVector) {
    hitInfo infos={false,{0,255,0},Vector3(),Vector3(),0};
    const float EPSILON = 0.0000001;
    Color edge1, edge2, h, s, q;
    float d, f, u, v;

    edge1 = b-a;
    edge2 = c-a;

    h = rayVector^edge2;
    d = edge1*h;
    if (d > -EPSILON && d < EPSILON)
        return infos;   // This ray is parallel to this triangle.
    f = 1.0 / d;
    s = camPos - a;
    u = (s*h)*f;
    if (u < 0.0 || u > 1.0)
        return infos;

    q = s^edge1;
    v = f * (rayVector*q);

    if (v < 0.0 || u + v > 1.0)
        return infos;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * (edge2*q);
    if (t > EPSILON) // ray intersection
    {
        infos.material = material;
        infos.color = color;
        infos.hitPos = camPos + rayVector * t;
        infos.distance = (camPos-rayVector).length();
        infos.hit=true;
        infos.normalVector = n;
        infos.ID = ID;
        return infos;
    }else // This means that there is a line intersection but not a ray intersection.
        return infos;
}
*/

hitInfo Triangle::ray(Vector3 origin, Vector3 rayVector) {
    hitInfo infos={false,Vector3(),Vector3(),0,0,0};
    const float EPSILON = 0.0000001;

    // compute the plane's normal

    Vector3 v0v1 = b - a;
    Vector3 v0v2 = c - a;
    // no need to normalize
    Vector3 N = v0v1^v0v2; // N

    // Step 1: finding P

    // check if the ray and plane are parallel.
    float NdotRayDirection = N*rayVector;
    if (abs(NdotRayDirection) < EPSILON){   // almost 0
        return infos;// they are parallel, so they don't intersect!
    }

    // compute d parameter using equation 2
    float d = -(N*a);
    // compute t (equation 3)
    float t = -(N*origin + d) / NdotRayDirection;

    // check if the triangle is behind the ray
    if (t < 0) return infos; // the triangle is behind

    // compute the intersection point using equation 1
    Vector3 P = origin + rayVector*t;


    // Step 2: inside-outside test
    Vector3 C; // vector perpendicular to triangle's plane

    // edge 0
    Vector3 edge0 = b - a;
    Vector3 vp0 = P - a;
    C = edge0^vp0;
    if (N*C < 0) return infos; // P is on the right side

    // edge 1
    Vector3 edge1 = c - b;
    Vector3 vp1 = P - b;
    C = edge1^vp1;
    if (N*C < 0)  return infos; // P is on the right side

    // edge 2
    Vector3 edge2 = a - c;
    Vector3 vp2 = P - c;
    C = edge2 ^ vp2;
    if (N*C < 0){
        return infos;
    }  // P is on the right side;

    // this ray hits the triangle
    infos.materialIndex = materialIndex;
    infos.hitPos = P;
    infos.distance = (origin-P).length();
    infos.hit=true;
    infos.normalVector = n;
    infos.ID = ID;
    return infos;
}

double Triangle::area() {
    return ((b-a)^(c-a)).length()/2;
}

void Triangle::updateNormal() {
    n = (b-a)^(c-a);
    n.normalize();
}

void Triangle::moveTriangle(Vector3 vect) {
    a+=vect;
    b+=vect;
    c+=vect;
}

Vector3 Triangle::getA() {
    return a;
}

Vector3 Triangle::getB() {
    return b;
}

Vector3 Triangle::getC() {
    return c;
}

Vector3 Triangle::getNormal() {
    return n;
}

void Triangle::setA(Vector3 newA) {
    a=newA;
}

void Triangle::setB(Vector3 newB) {
    b=newB;
}

void Triangle::setC(Vector3 newC) {
    c=newC;
}
