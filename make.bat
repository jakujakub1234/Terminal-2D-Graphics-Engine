g++ -c -o library/Pixel/Pixel.o library/Pixel/Pixel.cpp
g++ -c -o library/Point2D/Point2D.o library/Point2D/Point2D.cpp
g++ -c -o library/Window2D/Window2D.o library/Window2D/Window2D.cpp 
g++ -c -o library/Window2D/Window2D_points.o library/Window2D/Window2D_points.cpp 
g++ -c -o library/Window2D/Window2D_lines.o library/Window2D/Window2D_lines.cpp
g++ -c -o library/Window2D/Window2D_triangles.o library/Window2D/Window2D_triangles.cpp
g++ -c -o library/Window2D/Window2D_polygons.o library/Window2D/Window2D_polygons.cpp

ar ru library/Ascii2D.a library/Pixel/Pixel.o^
 library/Point2D/Point2D.o^
 library/Window2D/Window2D.o^
 library/Window2D/Window2D_points.o^
 library/Window2D/Window2D_lines.o^
 library/Window2D/Window2D_triangles.o^
 library/Window2D/Window2D_polygons.o

ranlib library/Ascii2D.a

:blank

g++ -o triangle_animation triangle_animation.cpp library/Ascii2D.a
g++ -o polygon_animation polygon_animation.cpp library/Ascii2D.a
g++ -o plot_function plot_function.cpp library/Ascii2D.a
g++ -o pong pong.cpp library/Ascii2D.a
