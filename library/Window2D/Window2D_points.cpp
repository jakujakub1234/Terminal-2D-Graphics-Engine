#include "../Pixel/Pixel.h"
#include "../Point2D/Point2D.h"
#include "Window2D.h"
#include <cmath>
#include <initializer_list>
#include <numeric>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <utility>

void Window2D::addPoint(Point2D p, float thickness, Pixel color) {
    for (int i = 0; i < this->canvas_x; ++i) {
        for (int j = 0; j < this->canvas_y; ++j) {
            Point2D uv = this->generateUV(i, j);

            if (uv.distance(p) <= thickness) {
                this->canvas[j][i] = new Pixel(color);
            }
        }
    }
}

void Window2D::addPoints(std::initializer_list<Point2D> points, float thickness, Pixel color ) {
    int size = points.size();

    std::vector<Point2D> points_arr{points};

    for (int i = 0; i < size; ++i) {
        this->addPoint(points_arr[i], thickness, color);
    }
}

void Window2D::addCircle(Point2D p, float radius, float thickness, Pixel color) {
    for (int i = 0; i < this->canvas_x; ++i) {
        for (int j = 0; j < this->canvas_y; ++j) {
            Point2D uv = this->generateUV(i, j);

            if (uv.distance(p) <= radius + thickness && uv.distance(p) >= radius - thickness) {
                this->canvas[j][i] = new Pixel(color);
            }
        }
    }
}

