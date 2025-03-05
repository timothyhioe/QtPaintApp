#include "freeform.h"
using namespace std;

Freeform::Freeform() {}

Freeform::Freeform(QPoint refPnt, QColor color, QVector<QPoint> pnts, int lineType, int lineSize):
    NonSolidObj(refPnt, color), pnts(pnts), lineType(lineType), lineSize(lineSize)
{}

void Freeform::display(QPainter* painter)
{

    painter->setPen(QPen(color, lineSize, static_cast<Qt::PenStyle>(lineType)));
    for (int i = 1; i < pnts.size(); ++i)
    {
        painter->drawLine(pnts.at(i - 1), pnts.at(i));
    }
}

bool Freeform::inside(const QPoint &point)
{

    for(unsigned int i = 1; i < pnts.size(); i++){
        if(isCloseEnough(point, pnts.at(i - 1), pnts.at(i))){
            return true;
        }
    }
    return false;
}

bool Freeform::isCloseEnough(const QPoint &point, const QPoint &p1, const QPoint &p2)
{

    double numerator = std::abs((p2.y() - p1.y()) * point.x() - (p2.x() - p1.x()) * point.y() + p2.x() * p1.y() - p2.y() * p1.x());
    double denominator = std::sqrt(std::pow(p2.y() - p1.y(), 2) + std::pow(p2.x() - p1.x(), 2));
    double distance = numerator / denominator;

    return distance < 2;  // tolerance for "near" the line

}

void Freeform::move(const QPoint &delta)
{
    for(QPoint& point : pnts){
        point += delta;
    }
}
