//
// Created by leroy on 06/04/2023.
//

#include "Scene.h"
#include <cstdlib>
#include <iostream>

#include "JSON.h"
#include "Triangle.h"
#include "Sphere.h"

using namespace std;

Scene::Scene()
        :numberOfShapes(0),
         numberOfLights(0)
{
    camera = Camera();
    lights = (Light*) malloc(sizeof(Light));
    shapes = (Shape**) malloc(sizeof(Shape*));
}


Scene::Scene(std::string source,int width,int height)
        :numberOfShapes(0),
         numberOfLights(0)
{
    shapes = (Shape**) malloc(sizeof(Shape*));
    lights = (Light*) malloc(sizeof(Light));
    JSON json=JSON();
    json.parseFile(source);
    camera=Camera(width,height,
                  stof(json["camera"]["width"].getValue()),
                  stof(json["camera"]["height"].getValue()),
                  {stof(json["camera"]["position"]["x"].getValue()),
                   stof(json["camera"]["position"]["y"].getValue()),
                   stof(json["camera"]["position"]["z"].getValue())},
                  stof(json["camera"]["focalDistance"].getValue()),
                  stof(json["camera"]["focalLength"].getValue()),
                  stof(json["camera"]["apertureSize"].getValue()),
                  stof(json["camera"]["angleX"].getValue()),
                  stof(json["camera"]["angleY"].getValue()),
                  stof(json["camera"]["angleZ"].getValue()));
    backGroundColor=Color(stof(json["backGroundColor"]["r"].getValue()),
                          stof(json["backGroundColor"]["g"].getValue()),
                          stof(json["backGroundColor"]["b"].getValue()));

    for(int i=0;i<json["materials"].getLength();i++){
        Material material={
                stof(json["materials"][i]["roughness"].getValue()),
                stof(json["materials"][i]["metallic"].getValue()),
                stof(json["materials"][i]["emittance"].getValue()),
                {
                        stof(json["materials"][i]["albedo"]["r"].getValue()),
                        stof(json["materials"][i]["albedo"]["g"].getValue()),
                        stof(json["materials"][i]["albedo"]["b"].getValue())
                },
                {
                        stof(json["materials"][i]["emittedColor"]["r"].getValue()),
                        stof(json["materials"][i]["emittedColor"]["g"].getValue()),
                        stof(json["materials"][i]["emittedColor"]["b"].getValue())
                }
        };
        std::cout<<"Adding material------";
        materials.push_back(material);
        std::cout<<"added"<<std::endl;
    }
    for(int i=0;i<json["shapes"].getLength();i++){
        if(!json["shapes"][i]["shapeType"].getValue().compare("triangle")){
            Triangle t({
                               stof(json["shapes"][i]["pointA"]["x"].getValue()),
                               stof(json["shapes"][i]["pointA"]["y"].getValue()),
                               stof(json["shapes"][i]["pointA"]["z"].getValue())},
                       {
                               stof(json["shapes"][i]["pointB"]["x"].getValue()),
                               stof(json["shapes"][i]["pointB"]["y"].getValue()),
                               stof(json["shapes"][i]["pointB"]["z"].getValue())},
                       {
                               stof(json["shapes"][i]["pointC"]["x"].getValue()),
                               stof(json["shapes"][i]["pointC"]["y"].getValue()),
                               stof(json["shapes"][i]["pointC"]["z"].getValue())},
                       stoi(json["shapes"][i]["materialIndex"].getValue())
                       );
            std::cout<<"Adding triangle------";
            addShape(t);
            std::cout<<"added"<<std::endl;
        }else{
            Sphere s({
                             stof(json["shapes"][i]["center"]["x"].getValue()),
                             stof(json["shapes"][i]["center"]["y"].getValue()),
                             stof(json["shapes"][i]["center"]["z"].getValue())
                             },
                     stof(json["shapes"][i]["radius"].getValue()),
                     stoi(json["shapes"][i]["materialIndex"].getValue())
                     );
            std::cout<<"Adding sphere------";
            addShape(s);
            std::cout<<"added"<<std::endl;
        }
    }
}


Scene::Scene(Light *_lights, Shape **_shapes, int numLights,int numShapes,Camera _camera,Color _backGroundColor,int width,int height)
        :numberOfShapes(numShapes),
         numberOfLights(numLights),
         backGroundColor(_backGroundColor)
{
    camera = Camera(_camera);
    lights = (Light*) malloc(sizeof(Light));
    shapes = (Shape**) malloc(sizeof(Shape*));
    copyList(_lights,numLights);
    copyList(_shapes,numShapes);

}

void Scene::copyList(Light *listSource, int sourceL) {
    lights = (Light*) realloc(lights,sizeof(Light)*sourceL);
    for(int i=0;i<sourceL;i++){
        lights[i]=listSource[i];
    }
    numberOfLights=sourceL;
}

void Scene::copyList(Shape **listSource, int sourceL) {
    shapes = (Shape**) realloc(shapes,sizeof(Shape*)*sourceL);
    for(int i=0;i<sourceL;i++){
        shapes[i] = (Shape*) malloc(sizeof(Shape));
        shapes[i] = listSource[i]->clone();
    }
    numberOfShapes=sourceL;
}

void Scene::addLight(Light newLight) {
    numberOfLights++;
    lights=(Light*) realloc(lights,sizeof(Light)*numberOfLights);
    lights[numberOfLights-1]=newLight;
}

void Scene::addLights(Light *newLights,int numLight) {
    lights = (Light*) realloc(lights,sizeof(Light)*(numberOfLights+numLight));
    for(int i=0;i<numLight;i++){
        lights[i+numLight]=newLights[i];
    }
    numberOfLights+=numLight;
}

void Scene::addShape(Shape &newShape) {
    numberOfShapes++;
    shapes = (Shape**) realloc(shapes,sizeof(Shape*)*numberOfShapes);
    shapes[numberOfShapes-1]= newShape.clone();
}

void Scene::addShapes(Shape **newShapes,int numShape) {
    shapes = (Shape**) realloc(shapes,sizeof(Shape*)*(numberOfShapes+numShape));
    for(int i=0;i<numShape;i++){
        shapes[numberOfShapes+i] = (Shape*) malloc(sizeof(Shape));
        shapes[numberOfShapes+i] = newShapes[i]->clone();
    }
    numberOfShapes+=numShape;
}

void Scene::setShapes(Shape **newShapes,int numberOfShape) {
    copyList(newShapes,numberOfShape);
}

void Scene::setLights(Light *newLights,int numberOfLight) {
    copyList(newLights,numberOfLight);
}

Light *Scene::getLights() {
    return lights;
}

Shape **Scene::getShapes() {
    return shapes;
}

int Scene::getNumberOfLights() {
    return numberOfLights;
}

int Scene::getNumberOfShapes() {
    return numberOfShapes;
}

Scene::~Scene() {
    free(shapes);
    free(lights);
}

void Scene::setBackGroundColor(Color newColor) {
    backGroundColor =newColor;
}

Color Scene::getBackGroundColor() {
    return backGroundColor;
}






