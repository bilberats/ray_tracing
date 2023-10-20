//
// Created by leroy on 05/04/2023.
//
#include "Vector3.h"
#include "Image.h"

#ifndef RAY_TRACING_SHAPE_H
#define RAY_TRACING_SHAPE_H

typedef struct{
    float roughness;
    float metallic;
    float emittance;
    Color albedo;
    Color emittedColor;
}Material;

typedef struct{
    bool hit;
    Vector3 hitPos;
    Vector3 normalVector;
    double distance;
    int materialIndex;
    unsigned int ID;
}hitInfo;

class Shape {
protected:
    int materialIndex;
    static unsigned int IDTotal;
    unsigned int ID;
public:
    Shape(Shape &shape): materialIndex(shape.materialIndex),ID(shape.ID){}
    Shape():materialIndex(0),ID(IDTotal++){}
    Shape(int _materialIndex):materialIndex(_materialIndex),ID(IDTotal++){}
    unsigned int getID();
    int getMaterialIndex();
    void setMaterialIndex(int newMaterialIndex);

    virtual Shape* clone()=0;
    virtual hitInfo ray(Vector3 origin,Vector3 rayVector)=0;
    virtual double area()=0;
};


#endif //RAY_TRACING_SHAPE_H
