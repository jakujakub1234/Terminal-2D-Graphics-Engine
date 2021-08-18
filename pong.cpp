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
#include <cmath>

#include <Windows.h>

# define PI         3.14159265358979323846
# define EPSILON    0.00001

void hitWall(Point2D ball, float& angle) {
    if (ball.y >= 0.95) {
        if (angle < EPSILON || angle > 2 * PI - EPSILON) {
            angle = PI * 0.75;

            return;
        }

        if (angle < PI * 0.75) {
            angle += PI - angle * 2.0;
        }
        else {
            angle -= angle * 2.0 - 3.0 * PI;
        }       
    }

    if (ball.y <= -0.95) {
        if (abs(angle - PI) < EPSILON) {
            angle = PI * 1.75;

            return;
        }

        if (angle < PI * 1.75 && angle > PI) {
            angle += 3.0 * PI - angle * 2.0;
        }
        else {
            angle -= angle * 2.0 - PI;
        }
    }
}

void hitRacket(Point2D ball, Point2D left_racket_top, Point2D left_racket_bottom,
                             Point2D right_racket_top, Point2D right_racket_bottom, float& angle, float ball_speed) {

    if (ball.x <= -0.8 && ball.x >= -0.82 - ball_speed) {
        
        if (ball.y <= left_racket_top.y + EPSILON && ball.y >= left_racket_bottom.y - EPSILON) {
            
            float dist_from_top = (left_racket_top.y - ball.y) / (left_racket_top.y - left_racket_bottom.y);

            angle = 0.1 * PI + (0.8 * PI * dist_from_top);
        }
    }

    if (ball.x >= 0.8 && ball.x <= 0.82 + ball_speed) {
        
        if (ball.y <= right_racket_top.y + EPSILON && ball.y >= right_racket_bottom.y - EPSILON) {
            
            float dist_from_top = (right_racket_top.y - ball.y) / (right_racket_top.y - right_racket_bottom.y);

            angle = 1.9 * PI - (0.8 * PI * dist_from_top);
        }
    }
}

bool isEnd(Point2D ball) {
    return (ball.x < -1.0 || ball.x > 1.0);
}


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
    
    Point2D racket_1_top = Point2D(-0.8, 0.2);
    Point2D racket_1_bottom = Point2D(-0.8, -0.2);

    Point2D racket_2_top = Point2D(0.8, 0.2);
    Point2D racket_2_bottom = Point2D(0.8, -0.2);

    Point2D ball = Point2D(0.0, 0.0);

    if (fps_limit == 0) { fps_limit = -1; }

    int time_per_frame = 1000 / fps_limit;

    bool start = false;
    
    float ball_speed = 0.07;
    float racket_speed = 0.05;

    float act_angle = PI * 1.1;

    window2D.clearColor(Pixel(0, 0, 0.21));

    while (true) {
        if (isEnd(ball)) {
            start = false;

            ball_speed = 0.07;
            racket_speed = 0.05;

            ball = Point2D(0.0, 0.0);
            window2D.clearColor(Pixel(0, 0, 0.21));
        }

        if(GetKeyState('W') & 0x8000)
        {
            if (racket_1_bottom.y < 0.9) {
                racket_1_top.y += racket_speed;
                racket_1_bottom.y += racket_speed;
            }
            
            start = true;
        }

        if(GetKeyState('S') & 0x8000)
        {
            if (racket_1_top.y > -0.9) {
                racket_1_top.y -= racket_speed;
                racket_1_bottom.y -= racket_speed;
            }

            start = true;
        }
        
        if (GetAsyncKeyState(VK_UP) < 0) {
            if (racket_2_bottom.y < 0.9) {
                racket_2_top.y += racket_speed;
                racket_2_bottom.y += racket_speed;
            }

            start = true;
        }

        if (GetAsyncKeyState(VK_DOWN) < 0) {
            if (racket_2_top.y > -0.9) {
                racket_2_top.y -= racket_speed;
                racket_2_bottom.y -= racket_speed;
            }

            start = true;
        }

        if (start) {
            ball.x += std::sin(act_angle) * ball_speed;
            ball.y += std::cos(act_angle) * ball_speed;

            hitWall(ball, act_angle);

            //ball_speed += 0.0001;
            //racket_speed += 0.0001;
        }

        hitRacket(ball, racket_1_top, racket_1_bottom, racket_2_top, racket_2_bottom, act_angle, ball_speed);

        auto start_time = std::chrono::high_resolution_clock::now();

        //window2D.clearColor(Pixel(0, 0, 0.21));

        window2D.addLineSegment(Point2D(-0.8, -0.9), Point2D(-0.8, 0.9), 0.02, Pixel(0, 0, 0.21));
        window2D.addLineSegment(Point2D(0.8, -0.9), Point2D(0.8, 0.9), 0.02, Pixel(0, 0, 0.21));

        window2D.addLineSegment(racket_1_top, racket_1_bottom, 0.02, Pixel(1,1,1));
        window2D.addLineSegment(racket_2_top, racket_2_bottom, 0.02, Pixel(1,1,1));

        window2D.addLineSegment(Point2D(-1, -1), Point2D(1,-1), 0.02, Pixel(1,1,1));
        window2D.addLineSegment(Point2D(1, 1), Point2D(1,-1), 0.02, Pixel(1,1,1));
        window2D.addLineSegment(Point2D(-1, -1), Point2D(-1,1), 0.02, Pixel(1,1,1));
        window2D.addLineSegment(Point2D(1, 1), Point2D(-1,1), 0.02, Pixel(1,1,1));

        window2D.addPoint(ball,0.05, Pixel(0,1,0));
        window2D.print();

        auto finish = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = finish - start_time;

        while (elapsed < std::chrono::milliseconds(time_per_frame) && (fps_limit > 0)) {
            finish = std::chrono::high_resolution_clock::now();

            elapsed = finish - start_time;
        }

    }

}