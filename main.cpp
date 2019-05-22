#include <iostream>
#include "shape.h"
#include "container.h"
#include "factory.h"
#include <random>

using namespace std;

int main()
{
    Container<Shape*> shapes;
    static std::random_device rd;
    std::uniform_int_distribution<int> rand_type(0, 5);
    for (int i = 0; i < 25; ++i){
//        int type = rand_type(rd);
        int type = 5;
        switch (type) {
        case 0:
            shapes.addLastElement(factory("Point"));
            break;
        case 1:
            shapes.addLastElement(factory("Circle"));
            break;
        case 2:
            shapes.addLastElement(factory("Rect"));
            break;
        case 3:
            shapes.addLastElement(factory("Square"));
            break;
        case 4:
            shapes.addLastElement(factory("Polyline"));
            break;
        case 5:
            shapes.addLastElement(factory("Polygone"));
            break;
            }
    }
//    MyElement<Point*> e = MyElement<Point*>(new Point(1,2), NULL);
    cout << "ShapeCount = " << Shape::getCount() << endl;
//    shapes.clearContainer();
    MyElement<Shape*>* i = shapes.startIterate();
    while(i != shapes.finishIterate()){
        MyElement<Shape*>* temp = i->m_next;
        delete i->m_element;
        i = temp;
    }
    delete i->m_element;
    cout << "ShapeCount = " << Shape::getCount() << endl;
    return 0;
}
