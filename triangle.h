#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "solidobj.h"
#include <QPainter>
#include "math.h"

class Triangle: public SolidObj
{
public:
    Triangle();
    Triangle(QPoint refPnt, QPoint p2, QPoint p3, QColor color, bool filled, int LineType, int LineSize);
    void display(QPainter *painter) override;
    bool inside(const QPoint& point) override;
    void move(const QPoint& delta) override;


private:
    QPoint p2;
    QPoint p3;
    bool filled;
    int LineType;
    int LineSize;
};

#endif // TRIANGLE_H
