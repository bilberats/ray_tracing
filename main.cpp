#include <iostream>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Image.h"
#include "Inputs.h"
#include "JSON.h"
#include "multithreadingFunc.h"
#include "Quaternion.h"
#include "Render.h"
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vector3.h"

#include "Color.h"



#define HEIGHT 500
#define WIDTH 500
#define TOTALTHREAD 6
#define AASAMPLINGSIZE 1
#define NUMBEROFBOUNCE 6
#define SAMPLENUMBER 200
#define SCENEPATH "C:\\Fernand\\programmation\\c++\\ray_tracing\\cornellBoxScene.json"
#define RENDERPATH "C:\\Fernand\\programmation\\c++\\ray_tracing\\rendus\\"



int main() {

    srand (static_cast <unsigned> (time(0)));
    Scene scene(SCENEPATH,WIDTH,HEIGHT);

    //special scene


    Render render(WIDTH,HEIGHT);
    Inputs inputs=Inputs();

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ray Casting !");
    Image im(WIDTH,HEIGHT);
    pthread_t threads[TOTALTHREAD];
    multiThreadArgs *args[TOTALTHREAD];


    //setup arguments for threads
    for(int i=0;i<TOTALTHREAD;i++){
        args[i] = (multiThreadArgs*) malloc(sizeof(multiThreadArgs));
        args[i]->render = &render;
        args[i]->scene = &scene;
        args[i]->image = &im;
        args[i]->totalThread = TOTALTHREAD;
        args[i]->threadNum = i;
        args[i]->sampleNum = AASAMPLINGSIZE;
        args[i]->numberOfBounce = NUMBEROFBOUNCE;
        //thread_local std::default_random_engine generator(std::random_device{}());
        thread_local std::mt19937 generator(std::random_device{}());
        args[i]->generator= generator;
    }

    while (window.isOpen() && im.getNumOfStack()<SAMPLENUMBER)
    {
        // Get starting timepoint to get framerate
        auto start = std::chrono::high_resolution_clock::now();
        bool cameraMoved=false;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            cameraMoved = inputs.inputs(&window,event);
        }
        inputs.updateCamera(&scene.camera);
        if(inputs.moving){
            im.resetStack();
        }

        //launch threads
        for(int i=0;i<TOTALTHREAD;i++){
            pthread_create(&threads[i],NULL,&callRenderMultiThread,args[i]);
        }

        for(int i=0;i<TOTALTHREAD;i++){
            pthread_join(threads[i],NULL);
        }


        sf::Texture texture;
        texture.create(WIDTH,HEIGHT);
        texture.update(im.getPixels());
        sf::Sprite sprite(texture);
        window.clear();
        window.draw(sprite);
        window.display();

        // Get ending timepoint for framerate
        auto stop = std::chrono::high_resolution_clock::now();
        //difference
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        int numOfSample=im.getNumOfStack();
        std::cout<<"Time to generate frame: "<<duration.count()<<"ms, number of samples: "<<numOfSample<<std::endl;
    }
    sf::Texture texture;
    texture.create(WIDTH,HEIGHT);
    texture.update(im.getPixels());
    std::string path = RENDERPATH;
    path += std::to_string(rand());
    path += "_";
    path += std::to_string(SAMPLENUMBER);
    path += "-samples.png";
    std::cout<<"Image saved :"<<std::endl;
    std::cout<<path<<std::endl;
    texture.copyToImage().saveToFile(path);


    return 0;
}
