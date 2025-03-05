#include "line.h"
using namespace std;

Line::Line() {}

Line::Line(QPoint refPnt, QPoint endPnt, QColor color, int LineType, int LineSize):
    NonSolidObj(refPnt, color), endPnt(endPnt), LineType(LineType), LineSize(LineSize)
{}

void Line::display(QPainter* painter)
{
    painter->setPen(QPen(color, LineSize, static_cast<Qt::PenStyle>(LineType)));
    painter->drawLine(refPnt, endPnt);
}


QPoint Line::getEndPnt() const
{
    return endPnt;
}

bool Line::inside(const QPoint &point)
{
    QPoint p1 = refPnt;
    QPoint p2 = endPnt;
    QPoint p = point;

    double d = std::abs((p2.y() - p1.y()) * p.x() - (p2.x() - p1.x()) * p.y() + p2.x() * p1.y() - p2.y() * p1.x())
               / std::sqrt(std::pow(p2.y() - p1.y(), 2) + std::pow(p2.x() - p1.x(), 2));

    //numerator = |(y2-y1)x0 - (x2-x1)y0 + x2y1 - y2x1|
    //denumerator = ((y2-y1)^2 + (x2-x1)^2)^1/2
    //distance = numerator / denumerator

    return d < 2;  // tolerance for "near" the line
}

void Line::move(const QPoint &delta)
{
    refPnt += delta;
    endPnt += delta;
}
