#pragma once
#include "maths.h"
#include <GL/glut.h>
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <limits>
#include <vertex.h>
#include "utils.h"

struct Buffer{
    maths::vec2i cords;
    maths::vec3f color;
    float zBuffer=std::numeric_limits<float>::min();
};

struct ShadowBuffer{
    maths::vec2i cords;
    float zBuffer=std::numeric_limits<float>::max();
};

class Canvas{
public:
    Canvas(int, char**);
    static void reshape(int,int);
    void display();
    static void update(int fps=30);
    void cleargrid();
    void putpixel(float x, float y,float zBuf, const maths::vec3f col);
    void drawline(float x1, float y1, float x2, float y2, const maths::vec3f color);
    static int scrHeight, scrWidth;
    std::map<int,Buffer> buffermaps;
    std::map<int,float> shadowmaps;
    static maths::vec3f bgcolor;
};