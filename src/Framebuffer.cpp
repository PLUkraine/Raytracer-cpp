//
//  Framebuffer.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/4/18.
//  Copyright © 2018 none. All rights reserved.
//

#include "Framebuffer.hpp"
#include <string.h>


Framebuffer::Framebuffer(int width, int height, int channels)
{
    this->m_width = width;
    this->m_height = height;
    this->m_channels = channels;
    this->m_pixels = new BYTE[width*height*channels];
    
    FillWithDefault();
}
Framebuffer::~Framebuffer()
{
    delete[] this->m_pixels;
}

int Framebuffer::height() const
{
    return m_height;
}
int Framebuffer::width() const
{
    return m_width;
}

void Framebuffer::Clear()
{
    memset(this->m_pixels, 0x00, GetSizeInBytes());
}
void Framebuffer::FillWithDefault()
{
    for (int y=0; y<this->m_height; ++y) {
        for (int x=0; x<this->m_width; ++x) {
            bool isBlack = IsDefaultPixelBlack(x, y);
            SetPixelRGB(x, y,
                        isBlack ? 0x00 : 0xFF,
                        0x00,
                        isBlack ? 0x00 : 0xFF);
        }
    }
}

void Framebuffer::SaveImage(const char *filename)
{
    FIBITMAP *img = FreeImage_ConvertFromRawBits(m_pixels, m_width, m_height, m_width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
    FreeImage_Save(FIF_PNG, img, filename, 0);
}

int Framebuffer::GetSizeInBytes() const
{
    return sizeof(BYTE)*m_width*m_height*m_channels;
}

void Framebuffer::SetPixelRGB(int x, int y, BYTE r, BYTE g, BYTE b)
{
    // write pixels in reverse
    BYTE *p_pixel = &this->m_pixels[(m_height-1-y)*m_width*m_channels + (m_width-1-x)*m_channels];
    *(p_pixel) = b;
    *(p_pixel+1) = g;
    *(p_pixel+2) = r;
}

bool Framebuffer::IsDefaultPixelBlack(int x, int y) const
{
    return (x < m_width/2 && y >= m_height/2) || (x >= m_width/2 && y < m_height/2);
}


