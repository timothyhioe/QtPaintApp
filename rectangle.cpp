#include "rectangle.h"
using namespace std;

Rectangle::Rectangle() {}

Rectangle::Rectangle(QPoint refPnt, QColor color, QPoint endPnt, bool filled, int LineType, int LineSize) :
    SolidObj(refPnt, color), endPnt(endPnt), filled(filled), LineType(LineType), LineSize(LineSize)
{}

void Rectangle::display(QPainter *painter)
{
    //find bottom left
    int x1 = min(refPnt.x(), endPnt.x());
    int y1 = min(refPnt.y(), endPnt.y());

    //determine width and height
    int width = abs(refPnt.x() - endPnt.x()); //absolute
    int length = abs(refPnt.y() - endPnt.y());

    painter->setPen(QPen(color, LineSize, static_cast<Qt::PenStyle>(LineType)));
    if(filled){
        painter->setBrush(QBrush(color, Qt::SolidPattern));
    }else{
        painter->setBrush(QBrush(Qt::NoBrush));
    }
    painter->drawRect(x1, y1, width, length);
}

bool Rectangle::inside(const QPoint &point)
{
    int x = point.x();
    int y = point.y();

    //find bottom left
    int x1 = min(refPnt.x(), endPnt.x());
    int y1 = min(refPnt.y(), endPnt.y());
    QPoint topLeft(x1,y1);


    //find top right
    int x2 = max(refPnt.x(), endPnt.x());
    int y2 = max(refPnt.y(), endPnt.y());
    QPoint bottomRight(x2,y2);

    return x >= topLeft.x() && x <= bottomRight.x() &&
           y >= topLeft.y() && y <= bottomRight.y();
}

void Rectangle::move(const QPoint &delta)
{
    refPnt += delta;
    endPnt += delta;
}

