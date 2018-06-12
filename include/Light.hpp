//
//  Light.hpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/8/18.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <glm/glm.hpp>

class Light
{
public:
    glm::vec4 dir;
    glm::vec4 color;
    
    Light();
    Light(glm::vec4 dir, glm::vec4 color);
    
    bool IsPoint() const;
    glm::vec3 GetPosition() const;
    glm::vec3 GetDirection() const;
};
#endif /* Light_hpp */
