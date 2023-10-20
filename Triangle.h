//
// Created by leroy on 18/04/2023.
//
#include "Shape.h"

#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H


class Triangle: public Shape {
private:
    Vector3 a,b,c;
    Vector3 n;
public:
    Triangle(Triangle &triangle)=default;
    Triangle():Shape(),a({1,0,0}),b({0,1,0}),c({0,0,1}){
        updateNormal();
    }
    Triangle(Vector3 _a,Vector3 _b,Vector3 _c,int _materialIndex)
    :Shape(_materialIndex),a(_a),b(_b),c(_c){
        updateNormal();
    }

    Triangle* clone() override;
    hitInfo ray(Vector3 origin,Vector3 rayVector) override;
    double area() override;

    void updateNormal();
    void moveTriangle(Vector3 vect);
    Vector3 getA();
    Vector3 getB();
    Vector3 getC();
    Vector3 getNormal();

    void setA(Vector3 newA);
    void setB(Vector3 newB);
    void setC(Vector3 newC);

};


#endif //RAY_TRACING_TRIANGLE_H
