#pragma once

#include "container.h"
#include "shape.h"
#include <random>

using namespace std;

Shape* factory(const string type)
{
    static std::random_device rd;
    std::uniform_int_distribution<int> rand_coord(0, 1000), rand_radius(1, 100), rand_num(0, 3);

    if (type == "Point")
        return new Point(rand_coord(rd), rand_coord(rd));
    else if (type == "Circle")
        return new Circle(Point(rand_coord(rd), rand_coord(rd)), rand_radius(rd));
    else if (type == "Rect"){
        int x1 = rand_coord(rd), x2 = rand_coord(rd), y1 = rand_coord(rd), y2 = rand_coord(rd);
        while (x1 == x2)
            x2 = rand_coord(rd);
        while (y1 == y2)
            y2 = rand_coord(rd);
        return new Rect(Point(x1, y1), Point(x2, y2));
    }
    else if (type == "Square"){
        int x1 = rand_coord(rd), x2 = rand_coord(rd), y1 = rand_coord(rd), y2 = rand_coord(rd);
        while (x1 == x2)
            x2 = rand_coord(rd);
        while (y1 == y2)
            y2 = rand_coord(rd);
        return new Square(Point(x1, y1), Point(x2, y2));
    }
    else if (type == "Polyline"){
        Container<Point>* points = new Container<Point>();
        int n = rand_num(rd);
        for (int i = 0; i <= n; ++i)
            points->addFirstElement(Point(rand_coord(rd), rand_coord(rd)));
        return new Polyline(*points);
    }
    else if (type == "Polygone"){
        Container<Point>* points = new Container<Point>();
        int n = rand_num(rd);
        for (int i = 0; i <= n; ++i)
            points->addFirstElement(Point(rand_coord(rd), rand_coord(rd)));
        return new Polygone(*points);
    }
    else return NULL;
}

