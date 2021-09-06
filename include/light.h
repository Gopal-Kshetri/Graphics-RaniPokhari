#pragma once
#include "maths.h"
#include "canvas.h"
// #include "camera.h"
// #include "mesh.h"

//Phong Lighting Model
class Light
{
public:
    Light();
    Light(maths::vec3f position);
    Light(maths::vec3f position, float, float, float);

    void setParams(float,float,float,float);

    // Mesh* lightobj;
    maths::vec3f position;

    float ambientInt;
    float pointInt;
    float specularCoefficient;

    float ambientConstant;
    float diffuseConstant;
    float specularConstant;

    float calculateIntensity(maths::vec3f,maths::vec3f, maths::vec3f);
    bool applyShadows(maths::vec2i);
    // Camera* lightcam;

    void processKeyboard(int, float);
    maths::mat4f getLightTransform();

    // void setObject(Mesh& mesh);
    // void render();
};