//
//  Camera.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/7/18.
//  Copyright © 2018 none. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera()
    : m_fowRad(glm::radians(60.0f)),
    m_eye(glm::vec3(0, 0, -10.0f)),
    m_center(glm::vec3(0.0f)),
    m_up(glm::vec3(0, 1.0f, 0))
{
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float fov)
    : m_fowRad(fov),
    m_eye(eye),
    m_center(center),
    m_up(up)
{
}

Ray Camera::GetRay(const int x, const int y, const int w, const int h) const
{
    CoordinateFrame frame = GetCoordinateFrame();
    float alpha = tanf(m_fowRad/2.0f) * GetAspect(w, h) * (x - w/2.0f) / (w/2.0f);
    float beta  = tanf(m_fowRad/2.0f) * (h/2.0f - y) / (h/2.0f);
    
    glm::vec3 dir = glm::normalize(frame.front + frame.right*alpha + frame.up*beta);
    Ray answer = {
        m_eye,
        dir
    };
    return answer;
}

CoordinateFrame Camera::GetCoordinateFrame() const
{
    CoordinateFrame frame;
    frame.front = glm::normalize(m_center - m_eye);
    frame.right = glm::normalize(glm::cross(m_up, frame.front));
    frame.up = glm::cross(frame.front, frame.right);
    return frame;
}

float Camera::GetAspect(const int w, const int h) const
{
    return static_cast<float>(w) / static_cast<float>(h);
}
