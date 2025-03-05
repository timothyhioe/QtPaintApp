#ifndef CIRCLE_H
#define CIRCLE_H
#include "solidobj.h"
#include <Qpainter>


class Circle:public SolidObj
{
public:
    Circle();
    Circle(QPoint refPnt, QColor color, int radius, bool filled, int LineType, int LineSize);
    void display(QPainter *painter) override;
    int getRadius();
    bool inside(const QPoint& point) override;
    void move(const QPoint& delta) override;

private:
    int radius;
    bool filled;
    int LineType;
    int LineSize;
};

#endif // CIRCLE_H
