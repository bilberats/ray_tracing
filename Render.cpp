//
// Created by leroy on 06/04/2023.
//
#include <iostream>
#include "Render.h"
#include <cmath>
#include <thread>

void Render::renderScene(Scene &scene,Image &im,int numOfBounce) {
    for(int y=0;y<height;y++){
        for(int x=0;x<widht;x++){
            Color pixColor;

            std::mt19937 generator;
            Vector3 origin;
            Vector3 ray = scene.camera.getRay(x,y,origin,generator);
            hitInfo closestHit = getClosestHit(scene,ray,origin,-1,generator);

            if(closestHit.hit){
                pixColor = scene.materials[closestHit.materialIndex].albedo;
            }else{
                pixColor = scene.getBackGroundColor();
            }
            im.stackPixel(x,y,pixColor);
        }
    }
}

void Render::renderSceneMultiThreaded(Scene &scene,Image &im,int totalThread,int threadNum,int sampleNum,int numOfBounce,std::mt19937 &generator) {
    int chunkW,chunkHN,chunkH;
    chunkHN = height/totalThread;
    chunkW = widht;
    if(totalThread-1==threadNum)
        chunkH = height/totalThread + height%totalThread;
    else
        chunkH = chunkHN;
    renderChunk(scene,im,0,threadNum*chunkHN,chunkW,chunkH,sampleNum,numOfBounce,generator);
}


void Render::renderChunk(Scene &scene,Image &image,int initX,int initY,int chunkW,int chunkH,int sampleNum,int numOfBounce,std::mt19937 &generator) {
    if(sampleNum<=0){
        sampleNum=1;
    }

    for(int y=initY;y<chunkH+initY;y++){
        for(int x=initX;x<chunkW+initX;x++){
            Color pixColor;
            for(int i=0;i<sampleNum;i++){
                Vector3 origin;
                Vector3 ray = scene.camera.getRay(x,y,origin,generator);
                hitInfo closestHit = getClosestHit(scene,ray,origin,-1,generator);

                pixColor = pixColor + pathTracing(scene,numOfBounce,closestHit,ray,generator);
                //pixColor.display();
            }
            pixColor/=(float)sampleNum;

            //pixColor.display();
            image.stackPixel(x,y,pixColor);
        }
    }
}


Color Render::pathTracing(Scene &scene,int numOfBounce,hitInfo infos,Vector3 incomingRay,std::mt19937 &generator) {
    if(!infos.hit){
        Color bgColor = scene.getBackGroundColor();
        //bgColor.linearToSRGB();
        //bgColor.display();
        return bgColor;
    }

    //color transformation based on the shape just hit
    Color color;
    Material mat = scene.materials[infos.materialIndex];
    color = mat.emittedColor * mat.emittance;

    //std::cout<<infos.ID<<std::endl;
    if(numOfBounce>0){
        //generate a new hit and compute the color received from this bounced ray recursively
        Vector3 reflection = incomingRay - infos.normalVector * 2 * (float)(infos.normalVector * incomingRay);
        reflection.normalize();

        Vector3 bouncedRay = randomHemisphereDirection(infos,generator);
        Vector3 ray = bouncedRay*mat.roughness + reflection*(1-mat.roughness);
        //Vector3 ray = reflection;
        ray.normalize();
        Vector3 origin = infos.hitPos;
        hitInfo newInfos = getClosestHit(scene,ray,origin,(int)infos.ID,generator);

        Color received = pathTracing(scene,numOfBounce-1,newInfos,ray,generator);
        //received.sRGBToLinear();
        //color.display();
        //received.display();

        received *= 2*mat.metallic*(infos.normalVector*ray);
        received *= mat.albedo;
        color += received;
        //color.display();
    }
    return color;
}



hitInfo Render::getClosestHit(Scene &scene,Vector3 ray,Vector3 origin,int ID,std::mt19937 &generator) {
    hitInfo closest,temp;
    bool firsthit = true;
    closest = {false,{0,0,0},{0,0,0},0,0,0};

    if(scene.getNumberOfShapes() == 0){
        return closest;
    }

    for(int i=0;i<scene.getNumberOfShapes();i++){
        temp = scene.getShapes()[i]->ray(origin,ray);
        if(firsthit && temp.hit && temp.ID!=ID){
            closest = temp;
            firsthit = false;
        }else if(temp.hit && temp.ID!=ID && temp.distance < closest.distance){
            closest= temp;
        }
    }
    return closest;
}

Vector3 Render::randomHemisphereDirection(hitInfo infos,std::mt19937 &generator) {
    Vector3 randomDir = randomDirection(generator);

    return randomDir * (float)(infos.normalVector*randomDir);
}

Vector3 Render::randomDirection(std::mt19937 &generator) {
    Vector3 randomDir;
    std::normal_distribution<float> dist(0,1);
    randomDir.x = dist(generator);
    randomDir.y = dist(generator);
    randomDir.z = dist(generator);
    randomDir.normalize();

    return randomDir;
}
