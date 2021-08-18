#include <iostream>

#include "library/Window2D/Window2D.h"
#include "library/Pixel/Pixel.h"
#include "library/Point2D/Point2D.h"

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <bits/stdc++.h>
#include <vector>

std::vector< int > collatzConjecture (int n) {
    std::vector< int > values = {};

    while (n > 1) {
        values.push_back(n);
        
        if (n % 2 == 1) { 
            n = 3 * n + 1; 
        }
        else {
            n /= 2;
        }
    }

    values.push_back(1);

    return values;
}

std::vector< float > sinus () {
    std::vector< float > values = {};

    for (float i = 0; i <= 2 * M_PI; i += 0.1) {
        values.push_back(std::sin(i));
    }

    return values;
}

int main() {
    srand(time(NULL));

    std::cout << "Type canvas size (x): ";
    int canvas_x;
    std::cin >> canvas_x;

    std::cout << "Type canvas size (y): ";
    int canvas_y;
    std::cin >> canvas_y;

    std::cout << "Type value to calculate Collatz Conjecture: ";
    int collatz_conjecture_to_test;
    std::cin >> collatz_conjecture_to_test;

    std::vector< int > collatz_conjecture_values = collatzConjecture(collatz_conjecture_to_test);
    std::vector< float > sinus_values = sinus();

    Pixel collatz_color = Pixel(0.2,0.9,0.4);
    Pixel sinus_color = Pixel(0.9,0.4,0.2);
    Pixel background_color = Pixel(0.1,0.1,0.1);

    Window2D window2D = Window2D(canvas_x, canvas_y);
    window2D.clearColor(background_color);

    float start_horizontal = -0.9;
    float step_horizontal = 1.8 / (collatz_conjecture_values.size() - 1);

    float vertical_scale = *max_element(std::begin(collatz_conjecture_values), std::end(collatz_conjecture_values));

    for (std::vector<int>::size_type i = 0; i + 1 != collatz_conjecture_values.size(); i++) {
        Point2D p1 = Point2D(start_horizontal + (step_horizontal * i), 0.95 * (((2.0 * collatz_conjecture_values[i]) / vertical_scale) - 1.0));
        Point2D p2 = Point2D(start_horizontal + (step_horizontal * (i + 1)), 0.95 * (((2.0 * collatz_conjecture_values[i+1]) / vertical_scale) - 1.0));
        
        window2D.addLineSegment(p1, p2, 0.01, collatz_color); 
    }

    step_horizontal = 1.8 / (sinus_values.size() - 1);

    for (std::vector<int>::size_type i = 0; i + 1 != sinus_values.size(); i++) {
        Point2D p1 = Point2D(start_horizontal + (step_horizontal * i), sinus_values[i]);
        Point2D p2 = Point2D(start_horizontal + (step_horizontal * (i + 1)), sinus_values[i+1]);
        
        window2D.addLineSegment(p1, p2, 0.01, sinus_color); 
    }

    window2D.print();
}