//
// Created by leroy on 05/04/2023.
//

#include "Image.h"
#include <iostream>

using namespace std;

Image::Image()
:width(500),height(500)
{
    pixels.resize(width*height,Color());
    numOfStackedPixel.resize(width*height,0);
}

Image::Image(Image &newImage)
:width(newImage.width),height(newImage.height),
pixels(newImage.pixels),numOfStackedPixel(newImage.numOfStackedPixel)
{
}

Image::Image(int _width,int _height)
:width(_width),height(_height)
{
    pixels.resize(width*height,Color());
    numOfStackedPixel.resize(width*height,0);
}

Image::Image(int _width, int _height,std::vector<Color> _pixels)
:width(_width),height(_height),pixels(std::move(_pixels)){
    numOfStackedPixel.resize(width*height,1);
}

int Image::getNumOfStack() const{
    return numOfStackedPixel[0];
}

int Image::getHeight() const{
    return height;
}

int Image::getWidth() const{
    return width;
}

sf::Uint8 *Image::getPixels() {
    auto retPixels = new sf::Uint8[width*height*4];
    for(int i=0;i<width*height;i++){
        Color pixColor = pixels[i];
        // convert unbounded HDR color range to SDR color range

        // convert from linear to sRGB for display
        //pixColor = pixColor.linearToSRGB();
        //pixColor = pixColor.ACESFilm();

        retPixels[i*4] = (int)(pixColor.r*255);     //red
        retPixels[(i*4)+1] = (int)(pixColor.g*255);   //green
        retPixels[(i*4)+2] = (int)(pixColor.b*255);   //blue
        retPixels[(i*4)+3] = 255;          //alpha
    }
    return retPixels;
}

void Image::setPixels(std::vector<Color> _pixels) {
    pixels=std::move(_pixels);
}

void Image::setPixel(int x, int y,Color color) {
    //color = color.sRGBToLinear();
    pixels[y*width+x]=color;
}

void Image::stackPixel(int x, int y, Color color) {
    int pos=y*width+x;
    //n is the number of stacked pixel at this coordinate
    int n=numOfStackedPixel[pos];
    float weightOfPresentPix = (float)n/(float)(n+1);
    float weightOfAddedPix = 1/(float)(n+1);


    color*=weightOfAddedPix;
    pixels[pos]*=weightOfPresentPix;
    pixels[pos]+=color;
    numOfStackedPixel[pos]++;
}

void Image::resetStack() {
    std::fill(numOfStackedPixel.begin(),numOfStackedPixel.end(),0);
}







