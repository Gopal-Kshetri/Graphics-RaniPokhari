#include <GL/glut.h>
#include "camera.h"

Camera::Camera()
{
    m_pos         = {1.0f, 1.6f, 10.0f};
    m_front       = {0.0f, 0.0f, -1.0f};
    m_up          = {0.0f, 1.0f, 0.0f};
    m_right       = maths::normalize(maths::cross(m_front,m_up));
    zoom = 45.0f;
    m_speed = 1.0f;

}

void Camera::processKeyboard(unsigned char key,float dt)
{
    float m_velocity = m_speed*dt;
    switch (key) {  

        case 's':
            m_pos = maths::add(m_pos,maths::mul(m_up,m_velocity));
            break;

        case 'w':
            m_pos = maths::sub(m_pos,maths::mul(m_up,m_velocity));
            break;

        case 'a':
            m_pos = maths::add(m_pos,maths::mul(m_right,m_velocity));
            break;

        case 'd':
            m_pos = maths::sub(m_pos,maths::mul(m_right,m_velocity));
            break;

        case 'r':
            m_pos = maths::add(m_pos,maths::mul(m_front,m_velocity));
            break;

        case 'f':
            m_pos = maths::sub(m_pos,maths::mul(m_front,m_velocity));
            break;

        case 'x':
            zoom = zoom > 200.0f ? 200.0f : zoom+5*dt;
            break;

        case 'z':
            zoom = zoom < 0.05 ? 0.05 : zoom-5*dt;
            break;

        case 'q':
            exit(0);

    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    yaw -= xoffset;
    pitch -= yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    maths::vec3f front;
    float val = cos(maths::radians(yaw));
    // std::cout<<val;
    front[0] = cos(maths::radians(yaw)) * cos(maths::radians(pitch));
    front[1] = sin(maths::radians(pitch));
    front[2] = sin(maths::radians(yaw)) * cos(maths::radians(pitch));

    m_front = maths::normalize(front);

    m_right = maths::normalize(maths::cross(m_front,m_up));
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up = maths::normalize(maths::cross(m_right,m_front));
}

maths::mat4f Camera::getViewMatrix()
{
    //Look At Matrix
    maths::vec3f eye = m_pos;
    maths::vec3f target = maths::add(m_pos,m_front);

    maths::vec3f forward = maths::normalize(maths::sub(eye,target));
    maths::vec3f right = maths::normalize(maths::cross(m_up,forward));
    maths::vec3f up = maths::normalize(maths::cross(forward,right));

    maths::mat4f view ={{
        {right[0],right[1],right[2],-maths::dot(right,eye)},
        {up[0],up[1],up[2],-maths::dot(up,eye)},
        {forward[0],forward[1],forward[2],-maths::dot(forward,eye)},
        {0,0,0,1}
    }};
    
    return view;
}
