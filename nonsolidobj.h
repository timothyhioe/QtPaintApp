#ifndef NONSOLIDOBJ_H
#define NONSOLIDOBJ_H
#include "graphobj.h"

class NonSolidObj:public GraphObj
{
public:
    NonSolidObj();
    NonSolidObj(QPoint refPnt, QColor color);
    virtual void display(QPainter* painter) = 0;
    virtual bool inside(const QPoint& point) = 0;
    virtual void move(const QPoint& delta) = 0;



};

#endif // NONSOLIDOBJ_H
