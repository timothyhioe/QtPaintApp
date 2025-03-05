#include "circle.h"
using namespace std;


Circle::Circle() {}

Circle::Circle(QPoint refPnt, QColor color, int radius, bool filled, int LineType, int LineSize):
    SolidObj(refPnt, color), radius(radius), filled(filled), LineType(LineType), LineSize(LineSize)
{}


void Circle::display(QPainter *painter)
{
    painter->setPen(QPen(color, LineSize, static_cast<Qt::PenStyle>(LineType)));
    if(filled){
        painter->setBrush(QBrush(color, Qt::SolidPattern));
    }else{
        painter->setBrush(QBrush(Qt::NoBrush));
    }
    painter->drawEllipse(refPnt, radius, radius);

}

int Circle::getRadius()
{
    return radius;
}

bool Circle::inside(const QPoint &point)
{
    int dx = point.x() - refPnt.x();  //x distance from center to point
    int dy = point.y() - refPnt.y(); // y distance from center to point
    return(dx * dx+ dy * dy) <= (radius * radius); // counting overal distance from cetner to point
}

void Circle::move(const QPoint &delta)
{
    refPnt += delta;
}
