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

void Window2D::addTriangleMesh(Point2D p1, Point2D p2, Point2D p3, float thickness, Pixel color) {
    this->addLineSegment(p1, p2, thickness, color);
    this->addLineSegment(p2, p3, thickness, color);
    this->addLineSegment(p1, p3, thickness, color);
}

void Window2D::addTriangle(Point2D p1, Point2D p2, Point2D p3, Pixel color) {
    for (int i = 0; i < this->canvas_x; ++i) {
        for (int j = 0; j < this->canvas_y; ++j) {
            Point2D uv = this->generateUV(i, j);

            if (PointInTriangle(uv, p1, p2, p3)) {
                this->canvas[j][i] = new Pixel(color);
            }
        }
    }
}

void Window2D::addTriangleMeshMultipleColors(Point2D p1, Point2D p2, Point2D p3, float thickness, Pixel color1, Pixel color2, Pixel color3, bool voronoi_diagram) {
    this->addLineSegmentMultipleColors(p1, p2, thickness, color1, color2, voronoi_diagram);
    this->addLineSegmentMultipleColors(p2, p3, thickness, color2, color3, voronoi_diagram);
    this->addLineSegmentMultipleColors(p1, p3, thickness, color1, color3, voronoi_diagram);
}

void Window2D::addTriangleMultipleColors(Point2D p1, Point2D p2, Point2D p3, Pixel color1, Pixel color2, Pixel color3, bool voronoi_diagram) {
    for (int i = 0; i < this->canvas_x; ++i) {
        for (int j = 0; j < this->canvas_y; ++j) {
            Point2D uv = this->generateUV(i, j);

            if (PointInTriangle(uv, p1, p2, p3)) {
                if (voronoi_diagram) {
                    float dist_1 = uv.distance(p1);
                    float dist_2 = uv.distance(p2);
                    float dist_3 = uv.distance(p3);

                    float minimum = std::min(std::min(dist_1, dist_2), dist_3);

                    if (dist_1 == minimum) {
                        this->canvas[j][i] = new Pixel(color1);
                    } 
                    if (dist_2 == minimum) {
                        this->canvas[j][i] = new Pixel(color2);
                    }
                    if (dist_3 == minimum) {
                        this->canvas[j][i] = new Pixel(color3);
                    }
                }
                else {
                    float dist_1 = uv.distance(p1);
                    float dist_2 = uv.distance(p2);
                    float dist_3 = uv.distance(p3);
                    float dist_sum = dist_1 + dist_2 + dist_3;

                    Pixel tmp1 = color1 * (1.0 - (dist_1 / dist_sum));
                    Pixel tmp2 = color2 * (1.0 - (dist_2 / dist_sum));
                    Pixel tmp3 = color3 * (1.0 - (dist_3 / dist_sum));
                    
                    this->canvas[j][i] = new Pixel(tmp1 + tmp2 + tmp3);
                }
            }
        }
    }
}

void Window2D::addTriangleMeshWithDepth(Point2D p1, Point2D p2, Point2D p3, float thickness, Pixel color, float resize1, float resize2, float resize3, bool dim_color) {
    this->addLineSegmentWithDepth(p1, p2, thickness, color, resize1, resize2, dim_color);
    this->addLineSegmentWithDepth(p2, p3, thickness, color, resize2, resize3, dim_color);
    this->addLineSegmentWithDepth(p1, p3, thickness, color, resize1, resize3, dim_color);
}

void Window2D::addTriangleMeshMultipleColorsWithDepth(Point2D p1, Point2D p2, Point2D p3, float thickness, Pixel color1, Pixel color2, Pixel color3, float resize1, float resize2, float resize3, bool dim_color, bool voronoi_diagram) {
    this->addLineSegmentMultipleColorsWithDepth(p1, p2, thickness, color1, color2, resize1, resize2, dim_color, voronoi_diagram);
    this->addLineSegmentMultipleColorsWithDepth(p2, p3, thickness, color2, color3, resize2, resize3, dim_color, voronoi_diagram);
    this->addLineSegmentMultipleColorsWithDepth(p1, p3, thickness, color1, color3, resize1, resize3, dim_color, voronoi_diagram);
}