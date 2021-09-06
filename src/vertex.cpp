#include "vertex.h"

Vertex::Vertex(const maths::vec3f &pos, const maths::vec3f &normal, const maths::vec3f &c)
        : color(c),
          normal(normal),
          position(pos)
{    
}

Vertex& Vertex::operator+=(const Vertex &rhs)
{
    position = maths::add(position,rhs.position);
    color = maths::add(color,rhs.color);
    intensity += rhs.intensity;
    texCoords = maths::add(texCoords,rhs.texCoords);
    return *this;
}
Vertex Vertex::operator+(const Vertex &rhs) const
{
    return Vertex(*this) += rhs;
}
Vertex & Vertex::operator-=(const Vertex &rhs)
{
    position = maths::sub(position,rhs.position);
    color = maths::sub(color,rhs.color);
    intensity -= rhs.intensity;
    texCoords = maths::sub(texCoords,rhs.texCoords);
    return *this;
}
Vertex Vertex::operator-(const Vertex &rhs) const
{
    return Vertex(*this) -= rhs;
}
Vertex & Vertex::operator*=(float rhs)
{
    position = maths::mul(position,rhs);
    color = maths::mul(color,rhs);
    intensity *= rhs;
    texCoords = maths::mul(texCoords,rhs);

    return *this;
}
Vertex Vertex::operator*(float rhs) const
{
    return Vertex(*this) *= rhs;
}
Vertex& Vertex::operator/=(float rhs)
{
    position = maths::mul(position,1/rhs);
    color = maths::mul(color,1/rhs);
    intensity = intensity/rhs;
    texCoords = maths::mul(texCoords,1/rhs);
    return *this;
}
Vertex Vertex::operator/(float rhs) const
{
    return Vertex(*this) /= rhs;
}