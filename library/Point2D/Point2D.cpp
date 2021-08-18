#include <iostream>
#include <cmath>

#include "../Window2D/Window2D.h"
#include "../Pixel/Pixel.h"
#include "Point2D.h"

Point2D::Point2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Point2D Point2D::operator+(const Point2D& p2) {
    Point2D point2D = Point2D(0,0);
    point2D.x = this->x + p2.x;
    point2D.y = this->y + p2.y;

    return point2D;
}

Point2D Point2D::operator*(const Point2D& p2) {
    Point2D point2D = Point2D(0,0);
    point2D.x = this->x * p2.x;
    point2D.y = this->y * p2.y;

    return point2D;
}

float Point2D::dot(Point2D& p2) {
    return this->x * p2.x + this->y * p2.y;
}

float Point2D::distance(Point2D& p2) {
    float dist = 0.0;

    dist += pow((this->x - p2.x), 2);
    dist += pow((this->y - p2.y), 2);

    return sqrt(dist);
}      
