#ifndef POLYGON_H
#define POLYGON_H
#include "solidobj.h"
#include <QVector>
#include <QPainter>

class Polygon:public SolidObj
{
public:
    Polygon();
    Polygon(QColor color, bool filled,QVector<QPoint> pnts, int LineType, int LineSize);
    void display(QPainter* painter) override;
    bool inside(const QPoint& point) override;
    void move(const QPoint& delta) override;


private:
    QVector<QPoint> pnts;
    bool filled;
    int LineType;
    int LineSize;
};

#endif // POLYGON_H
