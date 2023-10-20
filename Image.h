//
// Created by leroy on 05/04/2023.
//
#include <SFML/Graphics.hpp>
#include "Color.h"
#include <vector>

#ifndef RAY_TRACING_IMAGE_H
#define RAY_TRACING_IMAGE_H


class Image {
protected:
    int height,width;
    std::vector<Color> pixels;
    std::vector<int> numOfStackedPixel;
public:
    Image();
    Image(Image &newImage);
    Image(int _width,int _height);
    Image(int _width,int _height,std::vector<Color> _pixels);
    int getWidth() const;
    int getHeight() const;
    int getNumOfStack() const;
    sf::Uint8* getPixels();
    void resetStack();
    void setPixels(std::vector<Color> _pixels);
    void setPixel(int x,int y,Color color);
    void stackPixel(int x,int y,Color color);
};


#endif //RAY_TRACING_IMAGE_H
