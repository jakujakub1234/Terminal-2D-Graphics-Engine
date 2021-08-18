#include <iostream>
#include <cmath>

// color:
// RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA
// 8        8        8        8  

#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
    public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        Pixel (float r, float g, float b);
        Pixel (float r, float g, float b, float a); // a = 1.0 - fully opaque
        Pixel (float r, float g, float b, int a);
        Pixel (int r, int g, int b, int a);

        Pixel operator+(Pixel& p2);
        Pixel operator-(Pixel& p2);
        Pixel operator*(Pixel& p2);
        Pixel operator/(Pixel& p2);

        Pixel operator+(float x);
        Pixel operator-(float x);
        Pixel operator*(float x);
        Pixel operator/(float x);
}; 

#endif