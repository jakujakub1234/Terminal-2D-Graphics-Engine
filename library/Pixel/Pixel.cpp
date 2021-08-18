#include <iostream>
#include <cmath>

#include "../Window2D/Window2D.h"
#include "Pixel.h"
#include "Pixel.h"

Pixel::Pixel(int r, int g, int b, int a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Pixel::Pixel(float r, float g, float b, int a) {
    int red = std::max(0, std::min(255, (int)(r * 255)));
    int green = std::max(0, std::min(255, (int)(g * 255)));
    int blue = std::max(0, std::min(255, (int)(b * 255)));

    this->r = red;
    this->g = green;
    this->b = blue;
    this->a = a;
}

Pixel::Pixel(float r, float g, float b, float a) {
    int red = std::max(0, std::min(255, (int)(r * 255)));
    int green = std::max(0, std::min(255, (int)(g * 255)));
    int blue = std::max(0, std::min(255, (int)(b * 255)));
    int alpha = std::max(0, std::min(255, (int)(a * 255)));

    this->r = red;
    this->g = green;
    this->b = blue;
    this->a = alpha;
}

Pixel::Pixel(float r, float g, float b) {
    int red = std::max(0, std::min(255, (int)(r * 255)));
    int green = std::max(0, std::min(255, (int)(g * 255)));
    int blue = std::max(0, std::min(255, (int)(b * 255)));
    int alpha = 255;

    this->r = red;
    this->g = green;
    this->b = blue;
    this->a = alpha;
}

Pixel Pixel::operator+(Pixel& p2) {
    int r = std::min(255, this->r + p2.r);
    int g = std::min(255, this->g + p2.g);
    int b = std::min(255, this->b + p2.b);
    int a = std::min(255, this->a + p2.a);

    return Pixel(r,g,b,a);
}

Pixel Pixel::operator*(Pixel& p2) {
    int r = std::min(255, this->r * p2.r);
    int g = std::min(255, this->g * p2.g);
    int b = std::min(255, this->b * p2.b);
    int a = std::min(255, this->a + p2.a);

    return Pixel(r,g,b,a);
}

Pixel Pixel::operator/(Pixel& p2) {
    int r = std::min(255, this->r / p2.r);
    int g = std::min(255, this->g / p2.g);
    int b = std::min(255, this->b / p2.b);
    int a = std::min(255, this->a + p2.a);

    return Pixel(r,g,b,a);
}

Pixel Pixel::operator-(Pixel& p2) {
    int r = std::min(255, this->r - p2.r);
    int g = std::min(255, this->g - p2.g);
    int b = std::min(255, this->b - p2.b);
    int a = std::min(255, this->a + p2.a);

    return Pixel(r,g,b,a);
}

Pixel Pixel::operator+(float var) {
    int x = std::max(0, std::min(255, (int)(var * 255)));

    int r = std::min(255, this->r + x);
    int g = std::min(255, this->g + x);
    int b = std::min(255, this->b + x);

    return Pixel(r,g,b, this->a);
}

Pixel Pixel::operator*(float x) {    
    float r = ((float)this->r * x) / 255.0;
    float g = ((float)this->g * x) / 255.0;
    float b = ((float)this->b * x) / 255.0;

    return Pixel(r,g,b, this->a);
}

Pixel Pixel::operator/(float x) {
    float r = ((float)this->r / x) / 255.0;
    float g = ((float)this->g / x) / 255.0;
    float b = ((float)this->b / x) / 255.0;

    return Pixel(r,g,b, this->a);
}

Pixel Pixel::operator-(float var) {
    int x = std::max(0, std::min(255, (int)(var * 255)));

    int r = std::min(255, this->r - x);
    int g = std::min(255, this->g - x);
    int b = std::min(255, this->b - x);

    return Pixel(r,g,b, this->a);
}
