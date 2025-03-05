#ifndef FREEFORM_H
#define FREEFORM_H
#include "nonsolidobj.h"
#include <QVector>
#include <Qpainter>

class Freeform:public NonSolidObj
{
public:
    Freeform();
    Freeform(QPoint refPnt, QColor color, QVector<QPoint> pnts, int lineType, int lineSize);
    void display(QPainter* painter) override;
    bool inside(const QPoint& point) override;
    bool isCloseEnough(const QPoint& point, const QPoint &p1, const QPoint& p2);
    void move(const QPoint& delta) override;

private:
    QVector<QPoint> pnts;
    int lineType;
    int lineSize;
};

#endif // FREEFORM_H
