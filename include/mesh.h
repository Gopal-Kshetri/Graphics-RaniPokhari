#pragma once
#include "triangle.h"
#include <vector>
#include <string>
#include<iostream>
#include <fstream>
#include <sstream>
#include "maths.h"
#include "camera.h"
#include "light.h"
#include "utils.h"

class Mesh{
public:
    Mesh(Canvas*);
    void load(std::string);
    void parse(std::string);
    void parseMaterial(std::string);

    void xrotate(float);
    void yrotate(float);
    void zrotate(float);
    void translate(float,float,float);
    void scale(float, float, float);

    bool backFaceCulling(Triangle&);

    void flatShading(Triangle& tri);
    void gouraudShading(Triangle& tri);
    void phongShading(Triangle& tri);

    void setView(maths::mat4f);
    void setProjection(maths::mat4f);
    void setTransform(maths::mat4f);

    void processKeyboard(char, float);
    void render();
    void draw_thread(int,int,bool);

    Camera* camera;
    Canvas* canvas;
    Light* light;

private:
    std::vector<Triangle> triangles;
    std::vector<Triangle> finalTris;
    std::vector<Triangle> shadowTris;

    bool isWireframe;
    bool isGouraudShade;
    bool isTexture;

    std::map<std::string, Material> material_list;
    std::map<std::string, Image> image_list;

    maths::vec3f colors[8] = {
                {34,139,34}, // green
                {220,20,60}, //red
                {255,69,0}, // orange red
                {0,128,0}, // green 
                {240,240,250}, //whitish greyish 
                {100,100,100}, // dark grey
                {72,61,139}, //violet
                {0,0,205} // blue medium
        };
    maths::mat4f view;
    maths::mat4f projection;
    maths::mat4f transform;
};