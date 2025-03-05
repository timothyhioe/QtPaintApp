#include "triangle.h"
using namespace std;

Triangle::Triangle() {}

Triangle::Triangle(QPoint refPnt, QPoint p2, QPoint p3, QColor color, bool filled, int LineType, int LineSize):
    SolidObj(refPnt, color), p2(p2), p3(p3), filled(filled), LineType(LineType), LineSize(LineSize)
{}

void Triangle::display(QPainter *painter)
{
    painter->setPen(QPen(color, LineSize, static_cast<Qt::PenStyle>(LineType)));

    if(filled){
        painter->setBrush(color);
    }else{
        painter->setBrush(Qt::NoBrush);
    }

    QPolygon triangle;
    triangle << refPnt << p2 << p3;

    painter->drawPolygon(triangle);
}

bool Triangle::inside(const QPoint &point)
{
    int x1 = min(refPnt.x(), p2.x());
    int xmin = min(x1, p3.x());
    int y1 = min(refPnt.y(), p2.y());
    int ymin = min(y1, p3.y());

    int x2 = max(refPnt.x(), p2.x());
    int xmax = max(x2, p3.x());
    int y2 = max(refPnt.y(), p2.y());
    int ymax = max(y2, p3.y());

    return xmin <= point.x() && ymin <= point.y() &&
           point.x() <= xmax && point.y() <= ymax;
}

void Triangle::move(const QPoint &delta)
{
    refPnt += delta;
    p2 += delta;
    p3 += delta;
}
