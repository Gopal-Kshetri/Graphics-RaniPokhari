#include "light.h"
#include <GL/glut.h>

Light::Light(){
    position = {10,10,20};

    ambientInt = 0.4;
    pointInt = 0.5;

    specularCoefficient = 32;
    ambientConstant = 1;
    diffuseConstant = 1;
    specularConstant = 1;

}

float Light::calculateIntensity(maths::vec3f point, maths::vec3f normal, maths::vec3f view){

    maths::vec3f l_dir = maths::normalize(maths::sub(position,point));

    float ambientLight = ambientConstant*ambientInt;
    
    float diffuseLight = maths::max(diffuseConstant* pointInt *maths::dot(normal,l_dir),0.0f);

    maths::vec3f reflection = maths::normalize(maths::sub(maths::mul(normal,(2* maths::dot(normal,l_dir))),l_dir));
    float specularLight = specularConstant * pointInt * pow(maths::dot(reflection,view),specularCoefficient);
    
    float tmp = ambientLight+diffuseLight+specularLight;
    tmp = (tmp > 1) ? 1: tmp;
    return tmp;

}

// maths::mat4f Light::getLightTransform(){
//     maths::mat4f proj = maths::perspective(lightcam->zoom, (float)1920/1080);
//     maths::mat4f view = lightcam->getViewMatrix();
//     maths::mat4f product = maths::mul(proj,view);
//     return product;
// }

void Light::setParams(float aconst, float dconst,float sconst, float spec){
    ambientConstant = aconst;
    diffuseConstant = dconst;
    specularCoefficient = sconst;
    specularCoefficient = spec;
}

void Light::processKeyboard(int key, float dt){
    float speed = 20;
    float tmp = pointInt + ambientInt;
    switch (key){
        case GLUT_KEY_RIGHT:
            position[0] += speed*dt;
            break;

        case GLUT_KEY_LEFT:
            position[0] -= speed*dt;
            break;

        case GLUT_KEY_UP:
            position[1] += speed*dt;
            break;

        case GLUT_KEY_DOWN:
            position[1] -= speed*dt;
            break;
        
        case GLUT_KEY_PAGE_UP:
            position[2] += speed*dt;
            break;
        
        case GLUT_KEY_PAGE_DOWN:
            position[2] -= speed*dt;
            break;

        case 'p':
            ambientInt = ambientInt > 0.8 ? 0.8 : ambientInt+dt/speed;
            break;

        case 'o':
            ambientInt = ambientInt < 0.01 ? 0.01 : ambientInt-dt/speed;
            break;  
        
        case 'm':
            pointInt = pointInt > 0.8 ? 0.8 : pointInt+dt/speed;
            break;
        
        case 'n':
            pointInt = pointInt < 0.01 ? 0.01 : pointInt-dt/speed;
            break;
    }
    float diff = tmp-(pointInt+ambientInt);
    Canvas::bgcolor = maths::sub(Canvas::bgcolor, maths::mul({20,100,100},diff));
}
