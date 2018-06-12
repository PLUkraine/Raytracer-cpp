//
//  Framebuffer.hpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/4/18.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Framebuffer_hpp
#define Framebuffer_hpp

// IMAGING
#include <FreeImage.h>


class Framebuffer
{
private:
    BYTE *m_pixels;
    int m_width;
    int m_height;
    int m_channels;
    
public:
    Framebuffer(int width, int height, int channels=3);
    ~Framebuffer();
    
    int height() const;
    int width() const;
    void Clear();
    void FillWithDefault();
    void SaveImage(const char *filename);
    void SetPixelRGB(int x, int y, BYTE r, BYTE g, BYTE b);
private:
    int GetSizeInBytes() const;
    bool IsDefaultPixelBlack(int x, int y) const;
};


#endif /* Framebuffer_hpp */
