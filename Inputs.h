//
// Created by leroy on 07/04/2023.
//
#include "Camera.h"
#include <SFML/Graphics.hpp>

#ifndef RAY_TRACING_INPUTS_H
#define RAY_TRACING_INPUTS_H


class Inputs {
private:
    // Flags for key pressed
    bool upFlag;
    bool downFlag;
    bool leftFlag;
    bool rightFlag;
    bool ctrlFlag;
    bool shiftFlag;
    bool iFlag;
    bool kFlag;
    bool jFlag;
    bool lFlag;
    bool oFlag;
    bool pFlag;
    bool zFlag;
    bool sFlag;
    float angleChange;
    float moveSpeed;
    float focalMoveSpeed;
public:
    bool moving;
    Inputs();
    Inputs(float _angleChange,float _moveSpeed,float _focalMoveSpeed);
    bool inputs(sf::RenderWindow* window,sf::Event event);
    void updateCamera(Camera* cam);
};


#endif //RAY_TRACING_INPUTS_H
