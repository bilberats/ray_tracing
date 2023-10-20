//
// Created by leroy on 05/04/2023.
//
#include <iostream>
#include "Camera.h"
#include <cmath>
#include <random>

Camera::Camera()
        :width(100),height(100),pWidth(500),pHeight(500),focalDistance(50),
        focalLength(100),apertureSize(0),
         angleX(0),angleY(0),angleZ(0),
         position(Vector3(0,0,0))
{
    update();
}

Camera::Camera(int _pWidth,int _pHeight,
               float _width,float _height,
               Vector3 _position,float _focalDistance,
               float _focalLength,float _apertureSize,
               float _angleX,float _angleY,float _angleZ)
        :width(_width),height(_height),pWidth(_pWidth),
        pHeight(_pHeight),focalDistance(_focalDistance),
        focalLength(_focalLength),apertureSize(_apertureSize),
         angleX(_angleX),angleY(_angleY),angleZ(_angleZ),position(_position)
{
    update();
}

Camera::Camera(Camera &_camera)
        :width(_camera.width),height(_camera.height),pWidth(_camera.pWidth),
         pHeight(_camera.pHeight),focalDistance(_camera.focalDistance),
         focalLength(_camera.focalLength),apertureSize(_camera.apertureSize),
         angleX(_camera.angleX),angleY(_camera.angleY),
         angleZ(_camera.angleZ),position(_camera.position)
{
    update();
}


void Camera::update() {
    //transforming spheric coordonates to cartesian coordonates;
    zAxis=Vector3(
            sin(angleY)*cos(angleX),
            sin(angleY)*sin(angleX),
            cos(angleY));
    xAxis=Vector3(
            sin(angleX),
            -cos(angleX),
            0);
    yAxis=Vector3(
            cos(angleY)*cos(angleX),
            cos(angleY)*sin(angleX),
            -sin(angleY));
    //rotating vectors of the plane around the direction axis with the angle angleZ
    xAxis=xAxis.rotateAroundAxis(angleZ,zAxis);
    yAxis=yAxis.rotateAroundAxis(angleZ,zAxis);
}

///A OPTIMISER
Vector3 Camera::getRay(int x, int y,Vector3& originPoint,std::mt19937 &generator) {
    //creating vectors for the pixels in the plane

    float positionOnScreenX,positionOnScreenY,pixW,pixH;
    pixW = width/(float)pWidth;
    pixH = height/(float)pHeight;
    //the (0,0) is in the top left corner
    positionOnScreenX=pixW*((float)x-(float)pWidth/2);
    positionOnScreenY=pixH*((float)y-(float)pHeight/2);

    //randomize + add aperture size
    float xOffset = floatRand(-(apertureSize+0.5f),apertureSize+0.5f,generator)*pixW;
    float yOffset = floatRand(-(apertureSize+0.5f),apertureSize+0.5f,generator)*pixH;

    //get the intersection point with the focal plane
    Vector3 pixelVector = yAxis*positionOnScreenY+xAxis*positionOnScreenX;
    Vector3 offsetVector = yAxis*yOffset+xAxis*xOffset;
    Vector3 ray = zAxis*focalDistance+pixelVector;
    Vector3 screenPoint = ray + offsetVector + position;
    ray.normalize();
    Vector3 focalPoint = ray*focalLength + position;

    //passing origin point by address
    originPoint=screenPoint;

    //Now we have all the vectors we need to constitute the ray vector
    ray = focalPoint-screenPoint;
    ray.normalize();

    return ray;
}


int Camera::getHeight() {
    return pHeight;
}
int Camera::getWidth() {
    return pWidth;
}

float Camera::getFocalDistance() {
    return focalDistance;
}

float Camera::getAngleX() {
    return angleX;
}

float Camera::getAngleY() {
    return angleY;
}

float Camera::getAngleZ() {
    return angleZ;
}

Vector3 Camera::getPosition() {
    return position;
}

void Camera::setWidth(float _width) {
    width=_width;
}
void Camera::setPWidth(int _pWidth) {
    pWidth=_pWidth;
    width=(float)pWidth/10;
}

void Camera::setPHeight(int _pHeight) {
    pHeight=_pHeight;
    height=(float)pHeight/10;
}

void Camera::setHeight(float _height) {
    height=_height;
}

void Camera::setFocalDistance(float _focalDistance) {
    if(_focalDistance>0){
        focalDistance=_focalDistance;
    }
}

void Camera::setAngleX(float _angleX) {
    angleX=_angleX;
}

void Camera::setAngleY(float _angleY) {
    if(_angleY<=(0)){
        angleY=0;
    }
    if(_angleY>=(M_PI)){
        angleY=-M_PI;
    }
    else{
        angleY=_angleY;
    }

}

void Camera::setAngleZ(float _angleZ) {
    angleZ=_angleZ;
}

void Camera::setPosition(Vector3 _position) {
    position=_position;
}

Vector3 Camera::getZAxis() {
    return zAxis;
}
Vector3 Camera::getXAxis() {
    return xAxis;
}
Vector3 Camera::getYAxis() {
    return yAxis;
}
/*
float Camera::floatRand(const float& min, const float& max) {
    static thread_local std::mt19937 generator;
    std::uniform_real_distribution<> distribution(min,max);
    return (float)distribution(generator);
}
*/

float Camera::floatRand(const float & min, const float & max,std::mt19937 &generator) {
    std::uniform_real_distribution<float> distribution(min,max);
    return distribution(generator);
}
