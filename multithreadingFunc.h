//
// Created by leroy on 14/05/2023.
//

#include "Scene.h"
#include "Image.h"
#include "Render.h"
#include <random>

#ifndef RAY_TRACING_MULTITHREADINGFUNC_H
#define RAY_TRACING_MULTITHREADINGFUNC_H

typedef struct{
    Render *render;
    Scene *scene;
    Image *image;
    int totalThread;
    int threadNum;
    int sampleNum;
    int numberOfBounce;
    std::mt19937 generator;
}multiThreadArgs;

void* callRenderMultiThread(void *args);

#endif //RAY_TRACING_MULTITHREADINGFUNC_H

