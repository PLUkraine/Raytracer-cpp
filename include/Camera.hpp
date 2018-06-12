//
//  Camera.hpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/7/18.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include "ColliderObject.hpp"

struct CoordinateFrame
{
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
};

class Camera
{
private:
    float m_fowRad;
    glm::vec3 m_eye;
    glm::vec3 m_center;
    glm::vec3 m_up;
    
public:
    Camera();
    Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float fow);
    Ray GetRay(const int x, const int y, const int w, const int h) const;
    
private:
    CoordinateFrame GetCoordinateFrame() const;
    float GetAspect(const int w, const int h) const;
};

#endif /* Camera_hpp */
