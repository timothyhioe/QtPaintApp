#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "solidobj.h"
#include <QPainter>
#include "math.h"

class Rectangle:public SolidObj
{
public:
    Rectangle();
    Rectangle(QPoint refPnt, QColor color, QPoint endPnt, bool filled, int LineType, int LineSize);
    void display(QPainter *painter) override;

    int getWidth();
    int getHeight();

    bool inside(const QPoint& point) override;
    void move(const QPoint& delta) override;

private:
    QPoint endPnt;
    bool filled;
    int LineType;
    int LineSize;
};

#endif // RECTANGLE_H
