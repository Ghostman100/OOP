#pragma once

#define PI 3.14f

#include "base.h"
#include <iostream>
#include <sstream>
#include "container.h"
#include "math.h"

using namespace std;

class Shape : public Printable {
public:
    static int getCount()
    {
        return sm_amount;
    }
    Shape()
    {
        sm_amount++;
    }
    virtual ~Shape()
    {
        sm_amount--;
    }
    virtual std::string getInfo() = 0;
private:
    static int sm_amount;
};

int Shape::sm_amount = 0;

class Point : public Shape, Named
{
public:
    Point(float x, float y): Named("Point"), m_x(x), m_y(y)
    {

    }

    ~Point(){

    }

    float getX() const
    {
        return m_x;
    }

    float getY() const
    {
        return m_y;
    }

    virtual string getInfo(){
        stringstream ss;
        ss << "Name: Point" << endl << "Coordinates: (" << m_x << ", " << m_y << ")" << endl;
        return ss.str();
    }

    friend ostream& operator << (ostream &s,  Point &obj)
    {
        return s << obj.getInfo();
    }

private:
    float m_x;
    float m_y;
};

float getLength(Point const& a, Point const& b) {
    return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX())+(a.getY() - b.getY()) * (a.getY() - b.getY()));
}

class Circle : public Shape, Named
{
public:
    Circle(Point const& center, float radius): Named("Circle"), m_center(center), m_radius(radius)
    {
        if (radius <= 0)
                throw std::logic_error("wrong radius for circle");
    }

    friend ostream& operator << (ostream &s,  Circle &obj)
    {
        return s << obj.getInfo();
    }

    Point getCenter() const {
        return m_center;
    }

    float getRadius() const {
        return m_radius;
    }

    virtual string getInfo()
    {
        stringstream ss;
        ss << "Name: Circle" << endl
           << "Center coordinates: (" << m_center.getX() << ", " << m_center.getY() << ")" << endl
           << "R=" << m_radius << endl
           << "P=" << 2 * PI * m_radius << endl
           << "S=" << PI * m_radius * m_radius << endl;
        return ss.str();
    }

private:
    Point m_center;
    float m_radius;
};

class Rect : public Shape, Named
{
public:
    Rect(Point const& a, Point const& b): Named("Rect"), m_a(a), m_b(b)
    {
        if(m_a.getX() == m_b.getX() || m_a.getY() == m_b.getY())
            throw std::logic_error("wrong parametrs for rect");
    }

    friend ostream& operator << (ostream &s,  Rect &obj)
    {
        return s << obj.getInfo();
    }

    virtual string getInfo()
    {
        stringstream ss;
        ss << "Name: Rect" << endl
           << "Coordinates s: a=(" << m_a.getX() << ", " << m_a.getY() << "), c=(" << m_b.getX() << ", " << m_b.getY() << ")" << endl
           << "L=" << 2 * fabs(m_a.getX() - m_b.getX()) + 2 * fabs(m_a.getY() - m_b.getY()) << endl
           << "S=" << fabs((m_a.getX() - m_b.getX())*(m_a.getY() - m_b.getY())) << endl;
        return ss.str();
    }

private:
  Point m_a, m_b;
};

class Square: public Shape, Named
{
public:
    Square(Point const& a, Point const& b): Named("Square"), m_a(a), m_b(b)
    {
        if(m_a.getX() == m_b.getX() || m_a.getY() == m_b.getY())
            throw std::logic_error("wrong parametrs for rect");
    }

    friend ostream& operator << (ostream &s,  Square &obj)
    {
        return s << obj.getInfo();
    }

    virtual string getInfo()
    {
        stringstream ss;
        ss << "Name: Square" << endl
           << "Coordinates s: a=(" << m_a.getX() << ", " << m_a.getY() << "), c=(" << m_b.getX() << ", " << m_b.getY()<< ")" << endl
           << "L=" << 2 * fabs(m_a.getX() - m_b.getX()) + 2 * fabs(m_a.getY() - m_b.getY()) << endl
           << "S=" << fabs((m_a.getX() - m_b.getX())*(m_a.getY() - m_b.getY())) << endl;
        return ss.str();
    }

private:
    Point m_a, m_b;
};

class Polyline: public Shape, Named
{
public:

    Polyline(Container<Point> const &points): Named("Polyline"), m_points(points)
    {

    }

    virtual string getInfo(){
        stringstream ss;
        ss << "Name: Polyline" << endl;
        if(m_points.isEmpty())
        {
            ss  << "Empty" << endl <<"L=0" << endl;
        }
        else if(m_points.getSize() ==1)
        {
            ss  << "Point:" << endl
                << "(" << m_points.getFirst().getX() << ',' << m_points.getFirst().getY()<< ')' << endl
                << "L=0" << endl;
        }
        else
        {
            ss  << "Points:" << endl;
            double len = 0;
            for(MyElement<Point>* i = m_points.startIterate(); i != NULL; i = i->m_next){
                ss << '(' << i->m_element.getX() << ',' << i->m_element.getY() << ')' << endl;
                if (i->m_next != NULL){
                    MyElement<Point>* j = i->m_next;
                    len += getLength(i->m_element, j->m_element);
                }
            }
            ss << "L=" << len << endl;
        }
        return ss.str();
    }

    friend ostream& operator << (ostream &s,  Polyline &obj)
    {
        return s << obj.getInfo();
    }

private:
    Container<Point> m_points;
};

class Polygone: public Shape, Named {
public:
    Polygone(Container<Point> const &points): Named("Polygon"), m_points(points)
    {

    }

    virtual string getInfo(){
        stringstream ss;
        ss << "Name: Polyline" << endl;
        if(m_points.isEmpty())
        {
            ss  << "Empty" << endl <<"L=0" << endl;
        }
        else if(m_points.getSize() ==1)
        {
            ss  << "Point:" << endl
                << "(" << m_points.getFirst().getX() << ',' << m_points.getFirst().getY()<< ')' << endl
                << "L=0" << endl;
        }
        else
        {
            ss  << "Points:" << endl;
            double len = 0;
            for(MyElement<Point>* i = m_points.startIterate(); i != NULL; i = i->m_next){
                ss << '(' << i->m_element.getX() << ',' << i->m_element.getY() << ')' << endl;
                if (i->m_next != NULL){
                    MyElement<Point>* j = i->m_next;
                    len += getLength(i->m_element, j->m_element);
                }
            }
            len += getLength(m_points.startIterate()->m_element, m_points.finishIterate()->m_element);
            ss << "L=" << len << endl;
        }
        return ss.str();
    }

    friend ostream& operator << (ostream &s,  Polygone &obj)
    {
        return s << obj.getInfo();
    }

private:
     Container<Point> m_points;
};
