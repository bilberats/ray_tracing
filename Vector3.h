//
// Created by leroy on 04/04/2023.
//

#ifndef RAY_TRACING_VECTOR3_H
#define RAY_TRACING_VECTOR3_H


class Vector3 {
public:
    float x,y,z;
    Vector3():x(0),y(0),z(0){}
    Vector3(float _x,float _y,float _z)
    :x(_x),y(_y),z(_z){}
    bool compare(Vector3 vec) const;
    float length();
    Vector3 normal();
    void normalize();
    void display() const;
    Vector3 rotateAroundAxis(float angle,Vector3 axis);

    //operators
    Vector3 operator+(Vector3 vec) const;
    Vector3& operator+=(Vector3& vec);
    Vector3 operator-(Vector3 vec) const;
    Vector3 operator-() const;
    Vector3& operator-=(Vector3& vec);
    Vector3 operator/(float scalar) const;
    Vector3& operator/=(float scalar);
    Vector3 operator*(float scalar) const;
    Vector3& operator*=(float scalar);
    double operator*(Vector3 vect) const;
    Vector3 operator^(Vector3 vec) const;
    Vector3& operator=(Vector3 vec);
};


#endif //RAY_TRACING_VECTOR3_H
