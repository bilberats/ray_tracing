//
// Created by leroy on 04/04/2023.
//
#include <iostream>
#include "Color.h"
#include <cmath>


void Color::display() const {
    std::cout << "{" << r << "," << g << "," << b << "}" << std::endl;
}

bool Color::compare(Color vec) const {
    return r==vec.r && g==vec.g && b==vec.b;
}

float Color::length() const{
    return (float) sqrt((double)r*r+g*g+b*b);
}

Color Color::normal() const{
    float len =length();
    if(len!=0){
        return *this/len;
    }
    else{
        return *this;
    }
}

void Color::normalize() {
    *this=this->normal();
}


Color Color::operator+(Color vec) const{
    return {r+vec.r,g+vec.g,b+vec.b};
}
Color& Color::operator+=(Color& vec){
    r+=vec.r;
    g+=vec.g;
    b+=vec.b;
    return *this;
}

Color Color::operator-(Color vec) const{
    return {r-vec.r,g-vec.g,b-vec.b};
}
Color Color::operator-() const{
    return {-r, -g, -b};
}
Color& Color::operator-=(Color& vec){
    r-=vec.r;
    g-=vec.g;
    b-=vec.b;
    return *this;
}

Color Color::operator/(float scalar) const{
    return {r / scalar, g / scalar, b / scalar};
}
Color& Color::operator/=(float scalar){
    r/=scalar;
    g/=scalar;
    b/=scalar;
    return *this;
}

Color Color::operator*(float scalar) const{
    return {r * scalar, g * scalar, b * scalar};
}

Color Color::operator*(Color vec) {
    return {(float)fmin(vec.r,r),(float)fmin(vec.g,g),(float)fmin(vec.b,b)};
}

Color& Color::operator*=(float scalar){
    r*=scalar;
    g*=scalar;
    b*=scalar;
    return *this;
}

Color& Color::operator*=(Color& vec){
    r=(float)fmin(vec.r,r);
    g=(float)fmin(vec.g,g);
    b=(float)fmin(vec.b,b);
    return *this;
}


void Color::conform() {
    if(r>1)
        r=1;
    if(g>1)
        g=1;
    if(b>1)
        b=1;
    if(r<0)
        r=0;
    if(g<0)
        g=0;
    if(b<0)
        b=0;
}

Color Color::linearToSRGB() {
    Color color=*this;
    color.conform();
    float const CUTOFF = 0.0031308f;
    if(color.r <= CUTOFF){
        color.r *= 12.92f;
    }else{
        color.r = 1.055f*pow(color.r,1.0f/2.4f) - 0.055f;
    }
    if(color.g <= CUTOFF){
        color.g *= 12.92f;
    }else{
        color.g = 1.055f*pow(color.g,1.0f/2.4f) - 0.055f;
    }
    if(color.b <= CUTOFF){
        color.b *= 12.92f;
    }else{
        color.b = 1.055f*pow(color.b,1.0f/2.4f) - 0.055f;
    }
    return color;
}

Color Color::sRGBToLinear() {
    Color color=*this;
    color.conform();
    float const CUTOFF = 0.04045f;
    if(color.r <= CUTOFF){
        color.r /= 12.92f;
    }else{
        color.r = pow((color.r + 0.055f)/1.055f,2.4f);
    }
    if(color.g <= CUTOFF){
        color.g /= 12.92f;
    }else{
        color.g = pow((color.g + 0.055f)/1.055f,2.4f);
    }
    if(color.b <= CUTOFF){
        color.b /= 12.92f;
    }else{
        color.b = pow((color.b + 0.055f)/1.055f,2.4f);
    }
    return color;
}

Color Color::ACESFilm() {
    Color color=*this;

    float a = 2.51f;
    float coeffb = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;

    color.r = (color.r*(a*color.r + coeffb)) / (color.r*(c*color.r + d) + e);
    color.g = (color.g*(a*color.g + coeffb)) / (color.g*(c*color.g + d) + e);
    color.b = (color.b*(a*color.b + coeffb)) / (color.b*(c*color.b + d) + e);
    color.normalize();
    return *this;
}





