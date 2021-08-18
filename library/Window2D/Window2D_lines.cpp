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

void Window2D::addLineSegment(Point2D p1, Point2D p2, float thickness, Pixel color) {
    for (int i = 0; i < this->canvas_x; ++i) {
        for (int j = 0; j < this->canvas_y; ++j) {
            Point2D uv = this->generateUV(i, j);

            float dist = 0;

            float l2 = pow(p1.distance(p2), 2);
            if (l2 == 0) {
                dist = p1.distance(uv);
            }
            else {
                Point2D p1_to_uv = Point2D(uv.x - p1.x, uv.y - p1.y);
                Point2D p1_to_p2 = Point2D(p2.x - p1.x, p2.y - p1.y);

                double t = p1_to_uv.dot(p1_to_p2) / l2;
                t = std::max(0.0, std::min(1.0, t));

                Point2D p3 = Point2D(p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y));

                dist = uv.distance(p3);
            }

            if (dist <= thickness) {
                this->canvas[j][i] = new Pixel(color);
            }
        }
    } 
}

void Window2D::addLineSegmentMultipleColors(Point2D p1, Point2D p2, float thickness, Pixel color1, Pixel color2, bool voronoi_diagram) {
    for (int i = 0; i < this->canvas_x; ++i) {
        for (int j = 0; j < this->canvas_y; ++j) {
            Point2D uv = this->generateUV(i, j);

            float dist = 0;

            float l2 = pow(p1.distance(p2), 2);
            if (l2 == 0) {
                dist = p1.distance(uv);
            }
            else {
                Point2D p1_to_uv = Point2D(uv.x - p1.x, uv.y - p1.y);
                Point2D p1_to_p2 = Point2D(p2.x - p1.x, p2.y - p1.y);

                double t = p1_to_uv.dot(p1_to_p2) / l2;
                t = std::max(0.0, std::min(1.0, t));

                Point2D p3 = Point2D(p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y));

                dist = uv.distance(p3);
            }

            if (dist <= thickness) {
                if (voronoi_diagram) {
                    float dist_1 = uv.distance(p1);
                    float dist_2 = uv.distance(p2);

                    if (dist_1 < dist_2) {
                        this->canvas[j][i] = new Pixel(color1);
                    } 
                    else {
                        this->canvas[j][i] = new Pixel(color2);
                    }
                }
                else {
                    float dist_1 = uv.distance(p1);
                    float dist_2 = uv.distance(p2);
                    float dist_3 = p1.distance(p2);

                    Pixel tmp1 = color1 * (1.0 - (dist_1 / dist_3));
                    Pixel tmp2 = color2 * (1.0 - (dist_2 / dist_3));
                    
                    this->canvas[j][i] = new Pixel(tmp1 + tmp2);
                }
            }
        }
    } 
}

void Window2D::addLineSegmentWithDepth(Point2D p1, Point2D p2, float thickness, Pixel color, float resize1, float resize2, bool dim_color) {
    for (int i = 0; i < this->canvas_x; ++i) {
        for (int j = 0; j < this->canvas_y; ++j) {
            Point2D uv = this->generateUV(i, j);
            Point2D p3 = Point2D(0,0);

            float dist = 0;

            float l2 = pow(p1.distance(p2), 2);
            if (l2 == 0) {
                dist = p1.distance(uv);
            }
            else {
                Point2D p1_to_uv = Point2D(uv.x - p1.x, uv.y - p1.y);
                Point2D p1_to_p2 = Point2D(p2.x - p1.x, p2.y - p1.y);

                double t = p1_to_uv.dot(p1_to_p2) / l2;
                t = std::max(0.0, std::min(1.0, t));

                p3 = Point2D(p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y));

                dist = uv.distance(p3);
            }

            float t1 = p2.distance(p3);
            float t2 = p1.distance(p2);

            float t = t1 / t2;
            float resize_scale = resize2 + ((resize1 - resize2) * t);

            dist /= resize_scale;

            if (!dim_color) {
                resize_scale = 1.0;
            }

            if (dist <= thickness) {
                this->canvas[j][i] = new Pixel(color * resize_scale);
            }
        }
    } 
}

void Window2D::addLineSegmentMultipleColorsWithDepth(Point2D p1, Point2D p2, float thickness, Pixel color1, Pixel color2, float resize1, float resize2, bool dim_color, bool voronoi_diagram) {
    for (int i = 0; i < this->canvas_x; ++i) {
        for (int j = 0; j < this->canvas_y; ++j) {
            Point2D uv = this->generateUV(i, j);
            Point2D p3 = Point2D(0,0);

            float dist = 0;

            float l2 = pow(p1.distance(p2), 2);
            if (l2 == 0) {
                dist = p1.distance(uv);
            }
            else {
                Point2D p1_to_uv = Point2D(uv.x - p1.x, uv.y - p1.y);
                Point2D p1_to_p2 = Point2D(p2.x - p1.x, p2.y - p1.y);

                double t = p1_to_uv.dot(p1_to_p2) / l2;
                t = std::max(0.0, std::min(1.0, t));

                p3 = Point2D(p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y));

                dist = uv.distance(p3);
            }

            float t1 = p2.distance(p3);
            float t2 = p1.distance(p2);

            float t = t1 / t2;
            float resize_scale = resize2 + ((resize1 - resize2) * t);

            dist /= resize_scale;  

            if (!dim_color) {
                resize_scale = 1.0;
            }

            if (dist <= thickness) {
                if (voronoi_diagram) {
                    float dist_1 = uv.distance(p1);
                    float dist_2 = uv.distance(p2);

                    if (dist_1 < dist_2) {
                        this->canvas[j][i] = new Pixel(color1 * resize_scale);
                    } 
                    else {
                        this->canvas[j][i] = new Pixel(color2 * resize_scale);
                    }
                }
                else {
                    float dist_1 = uv.distance(p1);
                    float dist_2 = uv.distance(p2);
                    float dist_3 = p1.distance(p2);

                    Pixel tmp1 = (color1 * (1.0 - (dist_1 / dist_3))) * resize_scale;
                    Pixel tmp2 = (color2 * (1.0 - (dist_2 / dist_3))) * resize_scale;
                    
                    this->canvas[j][i] = new Pixel(tmp1 + tmp2);
                }
            }
        }
    } 
}
