#include <iostream>
#include <cmath>    

#ifndef POINT2D_H
#define POINT2D_H

class Point2D {
    public:
        float x, y;
        Point2D(float x, float y);

        Point2D operator+(const Point2D& p2);
        Point2D operator*(const Point2D& p2);
        float dot(Point2D& p2);
        float distance(Point2D& p2);
};

#endif