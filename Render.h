//
// Created by leroy on 06/04/2023.
//
#include "Image.h"
#include "Scene.h"
#include <random>

#ifndef RAY_TRACING_RENDER_H
#define RAY_TRACING_RENDER_H


class Render {
private:
    int height,widht;
    static hitInfo getClosestHit(Scene &scene,Vector3 ray,Vector3 origin,int ID,std::mt19937 &generator);
public:
    Render():height(500),widht(500){}
    Render(int _width,int _height):widht(_width),height(_height){}

    void renderScene(Scene &scene,Image &im,int numOfBounce);
    Color pathTracing(Scene &scene,int numOfBounce,hitInfo infos,Vector3 incomingRay,std::mt19937 &generator);
    void renderSceneMultiThreaded(Scene &scene,Image &im,int totalThread,int threadNum,int sampleNum,int numOfBounce,std::mt19937 &generator);
    void renderChunk(Scene &scene,Image &image,int initX,int initY,int chunckW,int chunckH,int sampleNum,int numOfBounce,std::mt19937 &generator);
    static Vector3 randomHemisphereDirection(hitInfo infos,std::mt19937 &generator);
    static Vector3 randomDirection(std::mt19937 &generator);

};


#endif //RAY_TRACING_RENDER_H
