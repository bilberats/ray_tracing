//
// Created by leroy on 06/04/2023.
//
#include "Vector3.h"
#include "Shape.h"
#include "Camera.h"

#ifndef RAY_TRACING_SCENE_H
#define RAY_TRACING_SCENE_H

typedef struct{
    Vector3 position;
    Color color;
    double intensity;
}Light;

class Scene {
private:
    Light* lights;
    int numberOfLights;
    Shape** shapes;
    int numberOfShapes;
    Color backGroundColor;

    void copyList(Light* listSource,int sourceL);
    void copyList(Shape** listSource,int sourceL);
public:
    Camera camera;
    std::vector<Material> materials;

    Scene();
    Scene(std::string source,int width,int height);
    Scene(Light* _lights,Shape** _shapes,int numLights,int numShapes,Camera _camera,Color _backGroundColor,int width,int height);
    ~Scene();
    void addLight(Light newLight);
    void addLights(Light* newLights,int numLights);
    void addShape(Shape &newShape);
    void addShapes(Shape** newShapes,int numShape);
    void setShapes(Shape** newShapes,int numberOfShape);
    void setLights(Light* newLights,int numberOfLight);
    void setBackGroundColor(Color newColor);

    Light* getLights();
    int getNumberOfLights();
    int getNumberOfShapes();
    Shape** getShapes();
    Color getBackGroundColor();

};


#endif //RAY_TRACING_SCENE_H
