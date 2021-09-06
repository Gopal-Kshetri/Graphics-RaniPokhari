#pragma once
#include "maths.h"

struct Vertex{
    maths::vec3f normal;
    maths::vec2f texCoords;
    maths::vec3f position;
    maths::vec3f color;
    float intensity;

    Vertex() = default;
    Vertex(const maths::vec3f &pos, const maths::vec3f &normal, const maths::vec3f &c);
    Vertex &operator+=(const Vertex &rhs);
    Vertex operator+(const Vertex &rhs) const;
    Vertex &operator-=(const Vertex &rhs);
    Vertex operator-(const Vertex &rhs) const;
    Vertex &operator*=(float rhs);
    Vertex operator*(float rhs) const;
    Vertex &operator/=(float rhs);
    Vertex operator/(float rhs) const;

};  