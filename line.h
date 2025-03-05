#ifndef LINE_H
#define LINE_H
#include "nonsolidobj.h"
#include <QPainter>
class Line:public NonSolidObj
{
public:
    Line();
    Line(QPoint refPnt , QPoint endPnt, QColor color, int LineType, int LineSize);
    void display(QPainter* painter) override;
    QPoint getEndPnt() const;

    bool inside(const QPoint& point) override;
    void move(const QPoint& delta) override;


private:
    QPoint endPnt;
    int LineType;
    int LineSize;
};

#endif // LINE_H
