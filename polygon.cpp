#include "polygon.h"
using namespace std;

Polygon::Polygon() {}

Polygon::Polygon(QColor color, bool filled, QVector<QPoint> pnts, int LineType, int LineSize):
    SolidObj(refPnt, color), pnts(pnts), filled(filled), LineType(LineType), LineSize(LineSize)
{}

void Polygon::display(QPainter* painter)
{
    if(pnts.size() < 4){
        return;
    }

    QPolygon polygon;

    for(unsigned int i = 0; i < pnts.size(); i++){
        polygon << pnts.at(i);
    }

    painter->setPen(QPen(color, LineSize, static_cast<Qt::PenStyle>(LineType)));

    if(filled){
        painter->setBrush(QBrush(color, Qt::SolidPattern));
        painter->drawPolygon(polygon);
    }
    else{
        painter->setBrush(Qt::NoBrush);
        painter->drawPolygon(polygon);
    }
}

bool Polygon::inside(const QPoint& point)  {
    int n = pnts.size();
    int count = 0; // counter, how many lines does the casting ray go through
    bool inside = false; // gerade -> false (0 = false), ungerade -> true
    for (int i = 0, j = n - 1; i < n; j = i++) { // first loop -> check first and last point, since it's a polygon meaning the first and last point connects together
        if ((pnts[i].y() > point.y()) != (pnts[j].y() > point.y()) && // make sure the point is in between the 2 checked lines vertically
            (point.x() < (pnts[j].x() - pnts[i].x()) * (point.y() - pnts[i].y()) / (pnts[j].y() - pnts[i].y()) + pnts[i].x())) { // horizontal check (if the point is to the left of the lines)
            count++;
        }
    }

    if(count % 2 == 0){
        inside = false;
    }
    else{
        inside = true;
    }

    return inside;
}

void Polygon::move(const QPoint &delta)
{
    for(QPoint &point : pnts){
        point += delta;
    }
}

