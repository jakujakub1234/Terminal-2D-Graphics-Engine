#include <iostream>

#include "library/Window2D/Window2D.h"
#include "library/Pixel/Pixel.h"
#include "library/Point2D/Point2D.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <initializer_list>
#include <chrono>  // for high_resolution_clock


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
    
    float resize1 = 0.1;
    float resize2 = 3.0;
    float resize3 = 1.5;

    float x1 = 0.0;
    float y1 = 1.0;

    float x2 = -1.0;
    float y2 = 0.0;

    float x3 = 0.5;
    float y3 = -0.5;

    float step = 0.2;
    float step2 = 0.5;

    if (fps_limit == 0) { fps_limit = -1; }

    int time_per_frame = 1000 / fps_limit;

    while (true) {
        auto start = std::chrono::high_resolution_clock::now();

        resize1 += step;
        resize2 -= step;
        if (resize1 > 3.0 || resize1 < 0.1) {
            step = -step;
            resize1 += step;
            resize2 -= step;
        }

        resize3 += step2;
        if (resize3 > 3.0 || resize3 < 0.1) {
            step2 = -step2;
            resize3 += step2;
        }

        Point2D t1 = Point2D(std::abs(cos(x1)), sin(y1));
        Point2D t2 = Point2D(cos(x2), std::abs(sin(y2)));
        Point2D t3 = Point2D(cos(x3), sin(y3));

        x1 += 0.2;
        y1 += 0.2;
        x2 += 0.2;
        y2 += 0.2;
        x3 += 0.2;
        y3 += 0.2;

        if (x1 > 314) {
            x1 = 0.0;
            y1 = 1.0;

            x2 = -1.0;
            y2 = 0.0;

            x3 = 0.5;
            y3 = -0.5;

            step = 0.2;
            step2 = 0.5;
        }

        window2D.clearColor(Pixel(0, 0, 0.21));
        window2D.addTriangleMeshMultipleColorsWithDepth(t1, t2, t3, 0.03, Pixel(0.9, 0.1, 0.7), Pixel(0.1, 0.9, 0.7), Pixel(0.7, 0.9, 0.1), resize1, resize2, resize3);
        window2D.print();

        auto finish = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = finish - start;

        while (elapsed < std::chrono::milliseconds(time_per_frame) && (fps_limit > 0)) {
            finish = std::chrono::high_resolution_clock::now();

            elapsed = finish - start;
        }

    }

}