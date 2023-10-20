//
// Created by leroy on 04/04/2023.
//

#ifndef RAY_TRACING_COLOR_H
#define RAY_TRACING_COLOR_H


class Color {
public:
    float r,g,b;
    Color():r(0),g(0),b(0){}
    Color(float _r, float _g, float _b)
            :r(_r),g(_g),b(_b){}
    bool compare(Color vec) const;
    float length() const;
    Color normal() const;
    void normalize();
    void conform();
    void display() const;
    Color linearToSRGB();
    Color sRGBToLinear();
    // ACES tone mapping curve fit to go from HDR to LDR
    //https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
    Color ACESFilm();

    //operators
    Color operator+(Color vec) const;
    Color& operator+=(Color& vec);
    Color operator-(Color vec) const;
    Color operator-() const;
    Color& operator-=(Color& vec);
    Color operator/(float scalar) const;
    Color& operator/=(float scalar);
    Color operator*(float scalar) const;
    Color operator*(Color vec);
    Color& operator*=(float scalar);
    Color& operator*=(Color& vec);
    Color& operator=(Color const& vec) =default;
};


#endif //RAY_TRACING_VECTOR3_H
