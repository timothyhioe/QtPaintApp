#ifndef SOLIDOBJ_H
#define SOLIDOBJ_H
#include "graphobj.h"

class SolidObj: public GraphObj
{
public:
    SolidObj();
    SolidObj(QPoint refPnt, QColor color, bool filled = true);
    virtual void display(QPainter* painter) = 0;
    virtual bool inside(const QPoint& point) = 0;
    virtual void move(const QPoint& delta) = 0;
};

#endif // SOLIDOBJ_H
