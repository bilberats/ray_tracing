//
// Created by leroy on 05/04/2023.
//
#include "Vector3.h"
#include <random>

#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H


class Camera {
private:
    int pWidth,pHeight;
    float width,height,focalDistance,focalLength,apertureSize,angleX,angleY,angleZ;
    Vector3 position,zAxis,xAxis,yAxis;
    //zAxis acts as the direction, xAxis and yAxis are the x and y axis in the screen plane
    float static floatRand(const float& min,const float& max,std::mt19937 &generator);
public:
    Camera();
    Camera(int _pWidth,int _pHeight,
           float _width,float _height,
           Vector3 _position,float _focalDistance,
           float _focalLength,float _apertureSize,
           float _angleX,float _angleY,float _angleZ);
    Camera(Camera &_camera);
    Vector3 getRay(int x,int y,Vector3& originPoint,std::mt19937 &generator);
    void update();

    int getWidth();
    int getHeight();
    float getFocalDistance();
    float getAngleX();
    float getAngleY();
    float getAngleZ();
    Vector3 getPosition();
    Vector3 getZAxis();
    Vector3 getXAxis();
    Vector3 getYAxis();


    void setWidth(float _width);
    void setPWidth(int _pWidth);
    void setHeight(float _height);
    void setPHeight(int _pHeight);
    void setFocalDistance(float _focalDistance);
    void setAngleX(float _angleX);
    void setAngleY(float _angleY);
    void setAngleZ(float _angleZ);
    void setPosition(Vector3 _position);
};


#endif //RAY_TRACING_CAMERA_H
