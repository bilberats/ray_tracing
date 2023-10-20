//
// Created by leroy on 05/04/2023.
//

#include "Shape.h"
unsigned int Shape::IDTotal;

unsigned int Shape::getID() {
    return ID;
}


int Shape::getMaterialIndex() {
    return materialIndex;
}

void Shape::setMaterialIndex(int newMaterialIndex) {
    materialIndex=newMaterialIndex;
}



