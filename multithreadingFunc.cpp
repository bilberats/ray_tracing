//
// Created by leroy on 14/05/2023.
//
#include "multithreadingFunc.h"
#include <iostream>
#include <random>

void* callRenderMultiThread(void *args){
     multiThreadArgs *mydata;
     mydata = (multiThreadArgs *)args;

     mydata->render->renderSceneMultiThreaded(
             *mydata->scene,
             *mydata->image,
             mydata->totalThread,
             mydata->threadNum,
             mydata->sampleNum,
             mydata->numberOfBounce,
             mydata->generator);
     return 0;
}