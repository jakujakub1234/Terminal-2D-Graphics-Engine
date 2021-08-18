#include "../Pixel/Pixel.h"
#include "../Point2D/Point2D.h"
#include "Window2D.h"
#include <cmath>
#include <vector>
#include <numeric>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <utility>

void Window2D::addPolygonMesh(std::vector< Point2D > points, float thickness, Pixel color ) {
    int size = points.size();
    std::vector< Point2D > points_arr{points};

    std::vector< std::vector< Point2D > > triangulated_polygon = triangulatePolygon(points);

    for (auto &triangle : triangulated_polygon) {  
        this->addTriangleMesh(triangle[0], triangle[1], triangle[2], thickness, color);
    }
}

void Window2D::addPolygon(std::vector< Point2D > points, Pixel color ) {
    int size = points.size();
    std::vector< Point2D > points_arr{points};

    std::vector< std::vector< Point2D > > triangulated_polygon = triangulatePolygon(points);

    for (auto &triangle : triangulated_polygon) {  
        this->addTriangle(triangle[0], triangle[1], triangle[2], color);
    }
}

void Window2D::addPolygonMeshMultipleColors(std::vector<Point2D> points, float thickness, std::vector<Pixel> colors, bool voronoi_diagram) {
    int size = points.size();
    
    std::vector< Point2D > points_arr{points};
    std::vector< Pixel > pixels_arr{colors};

    std::vector< std::pair< std::vector< Point2D > , std::vector< Pixel > > > triangulated_polygon = triangulatePolygonWithColors(points, colors);

    for (auto &pair : triangulated_polygon) {  
        this->addTriangleMeshMultipleColors(pair.first[0], pair.first[1], pair.first[2],
            thickness,
            pair.second[0], pair.second[1], pair.second[2], voronoi_diagram);
    }
}

void Window2D::addPolygonMultipleColors(std::vector<Point2D> points, std::vector<Pixel> colors, bool voronoi_diagram) {
    int size = points.size();
    
    std::vector< Point2D > points_arr{points};
    std::vector< Pixel > pixels_arr{colors};

    std::vector< std::pair< std::vector< Point2D > , std::vector< Pixel > > > triangulated_polygon = triangulatePolygonWithColors(points, colors);

    for (auto &pair : triangulated_polygon) {  
        this->addTriangleMultipleColors(pair.first[0], pair.first[1], pair.first[2],
            pair.second[0], pair.second[1], pair.second[2], voronoi_diagram);
    }
}