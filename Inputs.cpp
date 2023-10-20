//
// Created by leroy on 07/04/2023.
//

#include "Inputs.h"
#include <cmath>
#include <iostream>

Inputs::Inputs()
:upFlag(false),
downFlag(false),
leftFlag(false),
rightFlag(false),
ctrlFlag(false),
shiftFlag(false),
iFlag(false),
kFlag(false),
jFlag(false),
lFlag(false),
oFlag(false),
pFlag(false),
zFlag(false),
sFlag(false),
angleChange(M_PI/70),
moveSpeed(3),
focalMoveSpeed(1){}

Inputs::Inputs(float _angleChange,float _moveSpeed,float _focalMoveSpeed)
:upFlag(false),
 downFlag(false),
 leftFlag(false),
 rightFlag(false),
 ctrlFlag(false),
 shiftFlag(false),
 iFlag(false),
 kFlag(false),
 jFlag(false),
 lFlag(false),
 oFlag(false),
 pFlag(false),
 zFlag(false),
 sFlag(false),
 angleChange(_angleChange),
 moveSpeed(_moveSpeed),
 focalMoveSpeed(_focalMoveSpeed){}

bool Inputs::inputs(sf::RenderWindow* window,sf::Event event) {
    bool cameraMoved=false;
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
                // If escape is pressed, close the application
            case  sf::Keyboard::Escape : window->close(); break;

                // Process the up, down, left and right keys
            case sf::Keyboard::Up :     upFlag=true; break;
            case sf::Keyboard::Down:    downFlag=true; break;
            case sf::Keyboard::Left:    leftFlag=true; break;
            case sf::Keyboard::Right:   rightFlag=true; break;
            case sf::Keyboard::LControl:ctrlFlag=true; break;
            case sf::Keyboard::LShift:  shiftFlag=true; break;
            case sf::Keyboard::I:       iFlag=true; break;
            case sf::Keyboard::K:       kFlag=true; break;
            case sf::Keyboard::J:       jFlag=true; break;
            case sf::Keyboard::L:       lFlag=true; break;
            case sf::Keyboard::O:       oFlag=true; break;
            case sf::Keyboard::P:       pFlag=true; break;
            case sf::Keyboard::Z:       zFlag=true; break;
            case sf::Keyboard::S:       sFlag=true; break;
        }
    }

    // If a key is released
    if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
            // Process the up, down, left and right keys
            case sf::Keyboard::Up :     upFlag=false; break;
            case sf::Keyboard::Down:    downFlag=false; break;
            case sf::Keyboard::Left:    leftFlag=false; break;
            case sf::Keyboard::Right:   rightFlag=false; break;
            case sf::Keyboard::LControl:ctrlFlag=false; break;
            case sf::Keyboard::LShift:  shiftFlag=false; break;
            case sf::Keyboard::I :      iFlag=false; break;
            case sf::Keyboard::K:       kFlag=false; break;
            case sf::Keyboard::J:       jFlag=false; break;
            case sf::Keyboard::L:       lFlag=false; break;
            case sf::Keyboard::O:       oFlag=false; break;
            case sf::Keyboard::P:       pFlag=false; break;
            case sf::Keyboard::Z:       zFlag=false; break;
            case sf::Keyboard::S:       sFlag=false; break;
            default : break;
        }
    }
    return cameraMoved;
}

void Inputs::updateCamera(Camera* cam) {
    moving=false;
    if(upFlag){
        moving=true;
        Vector3 addVect = cam->getZAxis()*moveSpeed;
        cam->setPosition(cam->getPosition()+addVect);
    }
    if(downFlag){
        moving=true;
        Vector3 addVect = -cam->getZAxis()*moveSpeed;
        cam->setPosition(cam->getPosition()+addVect);
    }
    if(rightFlag){
        moving=true;
        Vector3 addVect = cam->getXAxis()*moveSpeed;
        cam->setPosition(cam->getPosition()+addVect);
    }
    if(leftFlag){
        moving=true;
        Vector3 addVect = -cam->getXAxis()*moveSpeed;
        cam->setPosition(cam->getPosition()+addVect);
    }
    if(shiftFlag){
        moving=true;
        Vector3 addVect = -cam->getYAxis()*moveSpeed;
        cam->setPosition(cam->getPosition()+addVect);
    }
    if(ctrlFlag){
        moving=true;
        Vector3 addVect = cam->getYAxis()*moveSpeed;
        cam->setPosition(cam->getPosition()+addVect);
    }
    if(iFlag){
        moving=true;
        cam->setAngleY(cam->getAngleY()-angleChange);
    }
    if(kFlag){
        moving=true;
        cam->setAngleY(cam->getAngleY()+angleChange);
    }
    if(jFlag){
        moving=true;
        cam->setAngleX(cam->getAngleX()+angleChange);
    }
    if(lFlag){
        moving=true;
        cam->setAngleX(cam->getAngleX()-angleChange);
    }
    if(oFlag){
        moving=true;
        cam->setAngleZ(cam->getAngleZ()+angleChange);
    }
    if(pFlag){
        moving=true;
        cam->setAngleZ(cam->getAngleZ()-angleChange);
    }
    if(zFlag){
        moving=true;
        cam->setFocalDistance(cam->getFocalDistance()+focalMoveSpeed);
    }
    if(sFlag){
        moving=true;
        cam->setFocalDistance(cam->getFocalDistance()-focalMoveSpeed);
    }
    if(moving)
        cam->update();
}
