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

Window2D::Window2D(int canvas_x, int canvas_y, bool square_proportions) {
    system("CLS");

    this->canvas_x = canvas_x;
    this->canvas_y = canvas_y;

    this->square_proportions = square_proportions;

    this->canvas = new Pixel**[canvas_y];

    for (int h = 0; h < canvas_y; h++) {
        this->canvas[h] = new Pixel*[canvas_x];

        for (int w = 0; w < canvas_x; w++) {
            this->canvas[h][w] = new Pixel(0,0,0,1);
        }
    }

    system("chcp 65001");
}

Point2D Window2D::generateUV(int i, int j) {
    Point2D res = Point2D(0, 0);
    
    if (this->square_proportions) {
        res.x = (2.0 * static_cast< float >(i) + 1 - static_cast< float >(this->canvas_x)) / static_cast< float >(this->canvas_y);
    }
    else {
        res.x = (2.0 * static_cast< float >(i) + 1 - static_cast< float >(this->canvas_x)) / static_cast< float >(this->canvas_x);
    }

    res.y = -(2.0 * static_cast< float >(j) + 1 - static_cast< float >(this->canvas_y)) / static_cast< float >(this->canvas_y);

    return res;
}

void Window2D::print() {
    std::ios_base::sync_with_stdio(false);

    for (int h = 0; h < canvas_y; h++) {
        printf("\033[A");
    }

    for (int h = 0; h < canvas_y; h++) {
        char buf[canvas_x*35];
        char* const last = buf+sizeof(buf);
        char* out = buf;

        for (int w = 0; w < this->canvas_x; w++) {
            Pixel* data = this->canvas[h][w];

            out += snprintf(out, last-out, "\033[38;2;%d;%d;%dm\u2588\033[0m", data->r, data->g, data->b);
        }
        *out = '\0';
        printf("%s\n", buf);

    }
}

void Window2D::clearColor(Pixel color) {
    for (int i = 0; i < this->canvas_x; ++i) {
        for (int j = 0; j < this->canvas_y; ++j) {
            this->canvas[j][i] = new Pixel(color);
        }
    }
}

float Window2D::sign (Point2D p1, Point2D p2, Point2D p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool Window2D::PointInTriangle (Point2D pt, Point2D v1, Point2D v2, Point2D v3)
{
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

float Window2D::getAngle(Point2D c, Point2D b, Point2D a) {
    Point2D ab = Point2D(0,0);
    Point2D ac = Point2D(0,0);

    ab.x = b.x - a.x;
    ab.y = b.y - a.y;

    ac.x = b.x - c.x;
    ac.y = b.y - c.y;

    float dotabac = (ab.x * ac.x + ab.y * ac.y);

    float lenab = sqrt(ab.x * ab.x + ab.y * ab.y);
    float lenac = sqrt(ac.x * ac.x + ac.y * ac.y);

    float dacos = dotabac / lenab / lenac;

    return std::acos(dacos);
}

bool Window2D::isCounterClockwise(Point2D a, Point2D b, Point2D c) {
    float crossp = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

    return crossp >= 0;
}

std::vector< std::vector< Point2D > > Window2D::triangulatePolygon(std::vector< Point2D > points) {
    std::vector< std::vector< Point2D > > result;

    int amount = points.size();

    int p1_index = 0;
    int p2_index = 0;
    int p3_index = 0;
    
    while (amount > 3) {        
        float min_angle = 100;
        int min_index = 0;

        for (int i = 0; i < points.size(); i++) {
            p1_index = i;
            p2_index = (i+1) % amount;
            p3_index = (i+2) % amount;

            bool testInTriangle = true;

            if (isCounterClockwise(points[p1_index], points[p2_index], points[p3_index])) {
                for (int j = 0; j < points.size(); j++) {
                    if (j == p1_index || j == p2_index || j == p3_index) {
                        continue;
                    }

                    if (PointInTriangle(points[j], points[p1_index], points[p2_index], points[p3_index])) {
                        testInTriangle = false;
                        break;
                    }
                }

                if (testInTriangle) {
                    min_index = p1_index;
                    break;
                }
            }   
        }

        std::vector<Point2D> act_ear{ points[min_index], points[(min_index+1) % amount], points[(min_index+2) % amount]};
        result.push_back(act_ear);

        points.erase(points.begin() + ((min_index+1) % amount));

        --amount;
    }

    std::vector<Point2D> act_ear{ points[0], points[1], points[2] };
    result.push_back(act_ear);

    return result;
}

std::vector< std::pair< std::vector< Point2D > , std::vector< Pixel > > > Window2D::triangulatePolygonWithColors(std::vector< Point2D > points, std::vector< Pixel > colors) {
    std::vector< std::pair< std::vector< Point2D > , std::vector< Pixel > > > result;

    int amount = points.size();

    int p1_index = 0;
    int p2_index = 0;
    int p3_index = 0;
    
    while (amount > 3) {        
        float min_angle = 100;
        int min_index = 0;

        for (int i = 0; i < points.size(); i++) {
            p1_index = i;
            p2_index = (i+1) % amount;
            p3_index = (i+2) % amount;

            bool testInTriangle = true;

            if (isCounterClockwise(points[p1_index], points[p2_index], points[p3_index])) {
                for (int j = 0; j < points.size(); j++) {
                    if (j == p1_index || j == p2_index || j == p3_index) {
                        continue;
                    }

                    if (PointInTriangle(points[j], points[p1_index], points[p2_index], points[p3_index])) {
                        testInTriangle = false;
                        break;
                    }
                }

                if (testInTriangle) {
                    min_index = p1_index;
                    break;
                }
            }   
        }

        std::vector<Point2D> act_ear{ points[min_index], points[(min_index+1) % amount], points[(min_index+2) % amount]};
        std::vector<Pixel> act_color{ colors[min_index], colors[(min_index+1) % amount], colors[(min_index+2) % amount]};
        
        std::pair< std::vector< Point2D > , std::vector< Pixel > > pair (act_ear, act_color);
        result.push_back(pair);

        points.erase(points.begin() + ((min_index+1) % amount));
        colors.erase(colors.begin() + ((min_index+1) % amount));

        --amount;
    }

    std::vector<Point2D> act_ear{ points[0], points[1], points[2] };
    std::vector<Pixel> act_color{ colors[0], colors[1], colors[2] };
    
    std::pair< std::vector< Point2D > , std::vector< Pixel > > pair (act_ear, act_color);
    result.push_back(pair);

    return result;
}