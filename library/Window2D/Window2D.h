#include <iostream>
#include <cmath>
#include "../Pixel/Pixel.h"
#include "../Point2D/Point2D.h"
#include <initializer_list>
#include <numeric>
#include <vector>

#ifndef WINDOW2D_H
#define WINDOW2D_H

class Window2D {
    private:
        Pixel*** canvas;
        int canvas_x;
        int canvas_y;

        bool square_proportions;

        float sign (Point2D p1, Point2D p2, Point2D p3);
        bool PointInTriangle (Point2D pt, Point2D v1, Point2D v2, Point2D v3);

        float getAngle(Point2D p1, Point2D p2, Point2D p3);
        std::vector< std::vector< Point2D > > triangulatePolygon(std::vector< Point2D > points);
        std::vector< std::pair< std::vector< Point2D > , std::vector< Pixel > > > triangulatePolygonWithColors(std::vector< Point2D > points, std::vector< Pixel > colors);
        bool isCounterClockwise(Point2D a, Point2D b, Point2D c);

    public:
        Window2D (int canvas_x, int canvas_y, bool square_proportions = false);
        Point2D generateUV(int i, int j);

        void print();
        
        void clearColor(Pixel color);
        
        void addPoint(Point2D p, float thickness, Pixel color);
        void addPoints(std::initializer_list<Point2D> points, float thickness, Pixel color );
        void addCircle(Point2D p, float radius, float thickness, Pixel color);

        void addLineSegment(Point2D p1, Point2D p2, float thickness, Pixel color);
        void addLineSegmentMultipleColors(Point2D p1, Point2D p2, float thickness, Pixel color1, Pixel color2, bool voronoi_diagram = false);
        void addLineSegmentWithDepth(Point2D p1, Point2D p2, float thickness, Pixel color, float resize1, float resize2, bool dim_color = true);
        void addLineSegmentMultipleColorsWithDepth(Point2D p1, Point2D p2, float thickness, Pixel color1, Pixel color2, float resize1, float resize2, bool dim_color = true, bool voronoi_diagram = false);
        
        void addTriangleMesh(Point2D p1, Point2D p2, Point2D p3, float thickness, Pixel color);
        void addTriangle(Point2D p1, Point2D p2, Point2D p3, Pixel color);
        void addTriangleMeshMultipleColors(Point2D p1, Point2D p2, Point2D p3, float thickness, Pixel color1, Pixel color2, Pixel color3, bool voronoi_diagram = false);
        void addTriangleMultipleColors(Point2D p1, Point2D p2, Point2D p3, Pixel color1, Pixel color2, Pixel color3, bool voronoi_diagram = false);
        
        void addTriangleMeshWithDepth(Point2D p1, Point2D p2, Point2D p3, float thickness, Pixel color, float resize1, float resize2, float resize3, bool dim_color = true);
        void addTriangleMeshMultipleColorsWithDepth(Point2D p1, Point2D p2, Point2D p3, float thickness, Pixel color1, Pixel color2, Pixel color3, float resize1, float resize2, float resize3, bool dim_color = true, bool voronoi_diagram = false);

        void addPolygonMesh(std::vector<Point2D> points, float thickness, Pixel color );  // vertexes in counter-clockwise order
        void addPolygon(std::vector<Point2D> points, Pixel color );  // vertexes in counter-clockwise order
        void addPolygonMeshMultipleColors(std::vector<Point2D> points, float thickness, std::vector<Pixel> colors, bool voronoi_diagram = false); // vertexes in counter-clockwise order
        void addPolygonMultipleColors(std::vector<Point2D> points, std::vector<Pixel> colors, bool voronoi_diagram = false); // vertexes in counter-clockwise order
};

#endif