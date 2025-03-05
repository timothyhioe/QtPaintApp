#ifndef GRAPHOBJ_H
#define GRAPHOBJ_H

#include <Qpoint>
#include <QColor>


class QPainter;

class GraphObj
{
public:
    GraphObj(){}
    GraphObj(QPoint refPnt, QColor color, bool filled);

    //copy constructor and assignment operator
    GraphObj(const GraphObj&) = delete;
    GraphObj& operator=(const GraphObj&) = delete;


    //destruktor
    virtual ~GraphObj() = default;


    //move konstruktor
    GraphObj(GraphObj&& other);

    //move assignment operator
    GraphObj& operator=(GraphObj&& other);

    void setRefPnt(const QPoint&);
    QPoint getRefPnt() const;
    float distance(GraphObj*);
    virtual void display(QPainter* painter) = 0;
    virtual bool inside(const QPoint& point) = 0;
    virtual void move(const QPoint& delta) = 0;

    void setColor(const QColor& newColor);


protected:
    QPoint refPnt;
    QColor color;
    bool filled;
};

#endif // GRAPHOBJ_H
