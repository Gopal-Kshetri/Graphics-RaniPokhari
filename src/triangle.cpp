#include "triangle.h"
#include <algorithm>
#include <limits>
#include <ctime>

Triangle::Triangle(Canvas* canvas){
    m_canvas = canvas;
    color = {255, 253, 208};
    vertices = {{
        {0,0,0},
        {0,0,0},
        {0,0,0}
    }};
    intensities = {1,1,1};
    populateVertices();
}

Triangle::Triangle(Canvas* canvas, maths::vec3f a, maths::vec3f b, maths::vec3f c){
    m_canvas = canvas;
    color = {240,220,200};
    vertices = {a,b,c};
    intensities = {1,1,1};
    populateVertices();
}

void Triangle::setVertex(maths::vec3f a, maths::vec3f b, maths::vec3f c){
    vertices = {a,b,c};
    populateVertices();
}

void Triangle::setNormals(maths::vec3f na, maths::vec3f nb, maths::vec3f nc){
    normals = {na,nb,nc};
    populateVertices();
}

void Triangle::setTexCoords(maths::vec2f uv1,maths::vec2f uv2,maths::vec2f uv3){
    texCoords = {uv1,uv2,uv3};
    populateVertices();
}

void Triangle::setColor(maths::vec3f col){
    color = col;
    populateVertices();
}

void Triangle::setIntensity(maths::vec3f intense){
    intensities = intense;
    populateVertices();
}
void Triangle::setImageTex(Image* img){
    image = img;
}
void Triangle::setMaterial(Material* mattmp){
    material = mattmp;
    if (material->isTex)
        isTex = true;
}

void Triangle::populateVertices(){
    for (int i=0; i<3; i++){
        vertex[i].intensity = intensities[i];
        vertex[i].color = maths::mul(color,intensities[i]);
        vertex[i].position = vertices[i];
        vertex[i].normal = normals[i];
        vertex[i].texCoords = texCoords[i];
    }
}

void Triangle::rasterize(){

    populateVertices();

    auto v1 = vertex[0];
    auto v2 = vertex[1];
    auto v3 = vertex[2];

    if(v1.position[1] > v2.position[1]) {std::swap(v2, v1);}
    if(v1.position[1] > v3.position[1]) {std::swap(v3, v1);}
    if(v2.position[1] > v3.position[1]) {std::swap(v3, v2);}

    if(v2.position[1] == v3.position[1]){
        if (v2.position[0]>v3.position[0])
            std::swap(v2,v3);
        fillBottomFlat(v1, v2, v3);
    }
    else if(v1.position[1] == v2.position[1]){
        if (v2.position[0]<v1.position[0])
            std::swap(v1,v2);
        fillTopFlat(v1, v2, v3);
    }
    else
    {   
        float split = (v2.position[1] - v1.position[1]) / (v3.position[1] - v1.position[1]);
        Vertex v4 = v1 + (v3-v1)*split;

        if (v2.position[0]<v4.position[0]){
            fillBottomFlat(v1, v2, v4);
            fillTopFlat(v2, v4, v3);
        }
        else{
            fillBottomFlat(v1, v4, v2);
            fillTopFlat(v4, v2, v3);
        }
    }
}


void Triangle::fillBottomFlat(Vertex& v1, Vertex& v2, Vertex& v3)
{   
    float delta = v3.position[1] - v1.position[1]; //v3.y = v2.y so anything can be used
    
    auto dt1 = (v2 - v1) / delta; 
    auto dt2 = (v3 - v1) / delta;
    
    auto e1 = v1;
    auto e2 = v1;

    fillFlatTriangle(v1,v2,v3,dt1,dt2,e1,e2); //common triangle draw
}

void Triangle::fillTopFlat(Vertex& v1, Vertex& v2, Vertex& v3)
{
    float delta = v3.position[1] - v1.position[1]; //v1.y = v2.y so anything can be used
    
    auto dt1 = (v3 - v1) / delta; 
    auto dt2 = (v3 - v2) / delta;
    
    auto e1 = v1;
    auto e2 = v2;

    fillFlatTriangle(v1,v2,v3,dt1,dt2,e1, e2);
    
}

void Triangle::fillFlatTriangle(Vertex& v1, Vertex& v2, Vertex&v3, Vertex& d1, Vertex& d2, Vertex e1, Vertex e2){

    const int start_y = (int)ceil(v1.position[1] - 0.5f);
    const int end_y = (int)ceil(v3.position[1] -   0.5f);
    // e1 += d1 * (float(start_y) + 0.5f - v1.position[1]);
    // e2 += d2 * (float(start_y) + 0.5f - v1.position[1]);

    for (int y = start_y; y < end_y; y++, e1 += d1, e2 += d2)
    {
        const int start_x = (int)ceil(e1.position[0]-0.5f);
        const int end_x = (int)ceil(e2.position[0]-0.5f);
        
        auto line = e1;
        const float dx = e2.position[0] - e1.position[0];
        const auto dline = (e2 - line) / dx;
        line += dline * (float(start_x)+0.5f- e1.position[0]);

        for (int x = start_x; x < end_x; x++, line += dline)
        {
            // recover z
            const float z = 1.0f/line.position[2];
            float intens = line.intensity;
            maths::vec3f color;
            if (isTex && isDrawTex)  
                color = maths::mul(material->getpixel(line.texCoords[0],line.texCoords[1]),intens);
            else
                color = {line.color[0], line.color[1], line.color[2]};
            m_canvas->putpixel(x, y,z, color);
        }
    }
}

void Triangle::wireframe_draw(){
    
    populateVertices();
    
    auto v1 = vertex[0].position;
    auto v2 = vertex[1].position;
    auto v3 = vertex[2].position;

    m_canvas->drawline(v1[0],v1[1],v2[0],v2[1],color);
	m_canvas->drawline(v2[0],v2[1],v3[0],v3[1],color);
	m_canvas->drawline(v3[0],v3[1],v1[0],v1[1],color);
}
