#include "graphobj.h"
#include <iostream>
using namespace std;


GraphObj::GraphObj(QPoint refPnt, QColor color, bool filled) : refPnt(refPnt), color(color), filled(filled)
{}

GraphObj::GraphObj(GraphObj &&other)
{
    this->refPnt = std::move(other.refPnt);
    this->color = std::move(other.color);
    this->filled = other.filled;
}

GraphObj &GraphObj::operator=(GraphObj &&other)
{
    if (this != &other) {
        refPnt = std::move(other.refPnt);
        color = std::move(other.color);
        filled = other.filled;
    }
    return *this;
}


void GraphObj::setRefPnt(const QPoint &newPoint)
{
    refPnt = newPoint;
}

QPoint GraphObj::getRefPnt() const
{
    return refPnt;
}


float GraphObj::distance(GraphObj * obj)
{
    int p1x = refPnt.x();
    int p1y = refPnt.y();

    int p2x = obj->getRefPnt().x();
    int p2y = obj->getRefPnt().y();


    cout << "Distance zwischen Objekten: ";
    return sqrt(pow((p2x - p1x), 2) + pow((p2y - p1y), 2));



}

void GraphObj::setColor(const QColor &newColor)
{
    color = newColor;
}
