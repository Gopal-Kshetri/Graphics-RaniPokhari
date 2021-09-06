#include "maths.h"
#include "GL/glut.h"

namespace maths{

    float radians(float degree){
        return (3.1416*degree)/180;
    }

    float degrees(float radian){
        return (180*radian)/3.1416;
    }

    float dot(vec3f a, vec3f b){
        float product= 0;
        for (int i=0; i<3; i++){
            product += a[i]*b[i];
        }
        return product;
    }

    vec3f cross(vec3f a, vec3f b){
        vec3f product = {};
        for (int i=0; i<3; i++){
            int tmpindex = (i+1)%3;
            product[i] = a[tmpindex]*b[(tmpindex+1)%3] - a[(tmpindex+1)%3]*b[tmpindex];
        }
        return product;
    }

    float veclength(vec3f v){
        float temp = sqrt(maths::dot(v,v));
        return temp;
    }

    vec3f normalize(vec3f a){
        vec3f product = {0.0f,0.0f,0.0f};
        float length = maths::veclength(a);
        for (int i=0;i<3; i++){
            product[i] = a[i]/length;
        }
        return product;
    }

    mat4f mul(mat4f a, mat4f b){
        mat4f product = {0};
        for (int i=0;i<4; i++){
            for (int j=0; j<4; j++){
                for (int k=0; k<4; k++){
                    product[i][j] += a[i][k]*b[k][j];
                }
            }
        }
        return product;
    }

    vec3f mul(mat4f a, vec3f b){

        float homogenous_b[4] = {b[0],b[1],b[2],1};
        float homogenous_product[4] = {0};
        for (int i=0;i<4;i++){
            for (int j=0; j<4; j++){
                homogenous_product[i] += a[i][j] * homogenous_b[j]; 
            }
        }
        float tmp = homogenous_product[3];
        vec3f product = {homogenous_product[0]/tmp,homogenous_product[1]/tmp,homogenous_product[2]/tmp};
        return product;
    }

    vec3f mul(vec3f a, float num){
        vec3f product;
        for (int i=0;i<3;i++){
            product[i] = a[i]*num;
        }
        return product;
    }

    vec3f div(vec3f a, float num){
        return mul(a,1/num);
    }

    vec3f add(vec3f a, vec3f b){
        vec3f product = {};
        for (int i=0; i<3; i++){
            product[i] = a[i] + b[i];
        }
        return product;
    }

    vec3f sub(vec3f a, vec3f b){
        vec3f product = {};
        for (int i=0; i<3; i++){
            product[i] = a[i] - b[i];
        }
        return product;
    }

    vec2f mul(vec2f a, float num){
        vec2f product;
        for (int i=0;i<2;i++){
            product[i] = a[i]*num;
        }
        return product;
    }

    vec2f div(vec2f a, float num){
        return mul(a,1/num);
    }

    vec2f add(vec2f a, vec2f b){
        vec2f product = {};
        for (int i=0; i<2; i++){
            product[i] = a[i] + b[i];
        }
        return product;
    }

    vec2f sub(vec2f a, vec2f b){
        vec2f product = {};
        for (int i=0; i<2; i++){
            product[i] = a[i] - b[i];
        }
        return product;
    }

    vec3f negate(vec3f a){
        vec3f b = {0,0,0};
        vec3f product = sub(b,a);
        return product;
    }

    mat4f orthographic(){
        mat4f ortho= {{{1, 0, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0},{0, 0, 0, 1}}};
        return ortho;
    }

    mat4f persproject(maths::vec3f eye){
        float zprp = eye[2]; float xprp = eye[0]; float yprp= eye[1];
        float zvp=-0.1;
        float dp = zprp - zvp;
        maths::mat4f persmatrix = {{{1,0,xprp/dp,-xprp*zvp/dp},
                                {0,1,yprp/dp,-yprp*zvp/dp},
                                {0,0,-zvp/dp,zvp*(zprp/dp)},
                                {0,0,-1/dp,zprp/dp}}};             
        
        return persmatrix;
    }

    mat4f perspective(float fov, float aspect){
        float zNear = 0.1f;
        float zFar = 1000.0f;
        float zRange = zNear- zFar;
        mat4f projection = {{
            {1/(aspect*tanf(fov/2)),0,0,0},
            {0,1/tanf(fov/2),0,0},
            {0,0,(zFar+zNear)/zRange,(zFar*zNear)/zRange},
            {0,0,-1,0}
            }};
        return projection;
    }


    mat4f x_rotation(float pitch){
        mat4f xrotation = {{
            {1, 0,           0,             0},
            {0, cosf(pitch), -sinf(pitch),    0},
            {0, sinf(pitch),  cosf(pitch),    0},
            {0, 0,           0,             1}
        }};
        return xrotation;
    }

    mat4f y_rotation(float yaw){
        mat4f yrotation = {{
            {cosf(yaw),  0,  sinf(yaw),   0},
            {0,         1,  0,          0},
            {-sinf(yaw), 0,  cosf(yaw),   0},
            {0,         0,  0,          1}
        }};
        return yrotation;
    }

    mat4f z_rotation(float roll){
        mat4f zrotation = {{
            {cosf(roll), -sinf(roll), 0, 0},
            {sinf(roll),  cosf(roll),  0, 0},
            {0,         1,          0, 0},
            {0,         0,          0, 1}
        }};
        return zrotation;
    }

    mat4f translate(float tx, float ty, float tz){
        mat4f translation = {{{1,0,0,tx},{0,1,0,ty},{0,0,1,tz},{0,0,0,1}}};
        return translation;
    }

    mat4f scale(float sx, float sy, float sz){
        mat4f scaling = {{{sx,0,0,0},{0,sy,0,0},{0,0,sz,0},{0,0,0,1}}};
        return scaling;
    }

    void printvec(vec3f a){
        std::cout << "\n";
        std::cout << a[0] << "\t" << a[1] << "\t"<< a[2] << "\t";
    }

    void printmat(mat4f a){
        std::cout << "\n";
        for (int i=0; i<4; i++){
            for (int j=0; j<4; j++){
                std::cout << a[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }

    float max(float a, float b){
        if (a>b){
            return a;
        }
        else{
            return b;
        }
    }

    vec3f getnormal(maths::vec3f point1, maths::vec3f point2, maths::vec3f point3){
        maths::vec3f ver1 = maths::sub(point1,point2);
        maths::vec3f ver2 = maths::sub(point1,point3);

        maths::vec3f normal = maths::normalize(maths::cross(ver1,ver2));
        return normal;
    }

    mat4f mattranspose(mat4f a){
        mat4f product = {0};
        for (int i=0;i<4;i++){
            for (int j=0;j<4;j++){
                product[i][j] = a[j][i];
            }
        }
        return product;
    }

    mat4f matidentity(){
        mat4f product = {0};
        product[0][0] = 1;
        product[1][1] = 1;
        product[2][2] = 1;
        product[3][3] = 1;

        return product;
    }

    vec3f barycentric(vec3f v1 ,vec3f v2,vec3f v3,vec3f vt){
        vec3f w = {0};
        w[0] = ( (v2[1] - v3[1])*( vt[0] - v3[0] ) + ( v3[0] - v2[0]) * (vt[1] - v3[1]) ) / 
			((v2[1] - v3[1]) * (v1[0] - v3[0]) + (v3[0] - v2[0]) * (v1[1] - v3[1]));
		w[1] = ((v3[1] - v1[1]) * (vt[0] - v3[0]) + (v1[0] - v3[0]) * (vt[1] - v3[1])) /
			((v2[1] - v3[1]) * (v1[0] - v3[0]) + (v3[0] - v2[0]) * (v1[1] - v3[1]));
		w[2] = 1 - w[0] - w[1];

        return w;
    }

    vec3f centroid(vec3f v1, vec3f v2, vec3f v3){
        
        maths::vec3f product;
        product[0] = (v1[0] + v2[0] + v3[0]) / 3; 
        product[1] = (v1[1] + v2[1] + v3[1]) / 3; 
        product[2] = (v1[2] + v2[2] + v3[2]) / 3;

        return product;
    }

    float getfps(){
        static float lastFrame = 0;
        float currentFrame = glutGet(GLUT_ELAPSED_TIME);
        static float deltaTime = (currentFrame - lastFrame)/1000;
        lastFrame = currentFrame;
        float fps = 1/deltaTime;
        return fps;
    }
}