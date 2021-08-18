#include <iostream>

#include "library/Window2D/Window2D.h"
#include "library/Pixel/Pixel.h"
#include "library/Point2D/Point2D.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <initializer_list>

#include <chrono>

int main() {
    srand(time(NULL));

    std::cout << "Type canvas size (x): ";
    int canvas_x;
    std::cin >> canvas_x;

    std::cout << "Type canvas size (y): ";
    int canvas_y;
    std::cin >> canvas_y;

    std::cout << "Type fps limit (0 for unlimited): ";
    int fps_limit;
    std::cin >> fps_limit;

    Window2D window2D = Window2D(canvas_x, canvas_y);

    float x1 = 0.0;
    float y1 = 1.0;

    float x2 = -1.0;
    float y2 = 0.0;

    float x3 = 0.5;
    float y3 = -0.5;

    std::vector < Pixel > colors;

    for (int i = 0; i < 7; ++i) {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        colors.push_back(Pixel(r, g, b));
    }

    if (fps_limit == 0) { fps_limit = -1; }

    int time_per_frame = 1000 / fps_limit;

    while (true) {
        auto start = std::chrono::high_resolution_clock::now();

        Point2D t1 = Point2D(std::abs(cos(x1 + 1.2)), sin(y1));
        Point2D t2 = Point2D(cos(x2 * 0.5), std::abs(sin(y2 * 1.2)));
        Point2D t3 = Point2D(cos(x3), sin(y3 + 0.2));
        Point2D t4 = Point2D(std::abs(cos(x2)), sin(y1));
        Point2D t5 = Point2D(std::abs(sin(x3 * 1.2)), sin(y1));
        Point2D t6 = Point2D(std::abs(sin(x1)), sin(y3 * 1.5));
        Point2D t7 = Point2D(std::abs(cos(x2 * 1.2)), sin(y3 * 1.35));
        Point2D t8 = Point2D(std::abs(sin(x3 * 1.82)), sin(y1 * 1.5));
        Point2D t9 = Point2D(std::abs(sin(x1 * 1.12)), cos(y1 * 0.25));
        Point2D t10 = Point2D(std::abs(cos(x3 * 1.211)), cos(y2 * 1.5));

        x1 += 0.2;
        y1 += 0.2;
        x2 += 0.2;
        y2 += 0.2;
        x3 += 0.2;
        y3 += 0.2;

        window2D.clearColor(Pixel(0, 0, 0.21));
        window2D.addPolygonMultipleColors({t1,t2,t3,t4,t5,t6, t7, t8, t9, t10}, 
        colors);
        window2D.print();

        auto finish = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = finish - start;

        while (elapsed < std::chrono::milliseconds(time_per_frame) && (fps_limit > 0)) {
            finish = std::chrono::high_resolution_clock::now();

            elapsed = finish - start;
        }
    }

}