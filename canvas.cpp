#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include "canvas.h"

using namespace std;

Canvas::Canvas(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box);
    setMouseTracking(true);

    type = NONE;
    interactionMode = CREATE;
    dragging = false;

    // TODO; more init

    scene = new Scene();

    backgroundColor = Qt::white;
    color = Qt::black;
    fillMode = true;
    clickCount = 0;

    lineType = Qt::SolidLine;
    lineSize = 2;
}

Canvas::~Canvas()
{
    delete scene;
}

QSize Canvas::minimumSizeHint() const
{
    return QSize(200, 200);
}

QSize Canvas::sizeHint() const
{
    return QSize(640, 480);
}

void Canvas::clearCanvas(void)
{
    scene->removeAll();
    update();
}

void Canvas::setPrimitiveMode(int mode)
{
    type = (Canvas::PrimitiveMode)mode;
    clickCount = 0;
    vertices.clear();
}

void Canvas::setObjColor(const QColor &col)
{
    color = col;
}

void Canvas::setFillMode(bool filled)
{
    fillMode = filled;
}

void Canvas::setInteractionMode(int mode)
{
    interactionMode = (Canvas::InteractionMode)mode;
}

void Canvas::setBackgroundColor(const QColor &col)
{
    backgroundColor = col;
    update();
}

void Canvas::setLineType(int type)
{
    lineType = type;
    update();
}

void Canvas::setLineSize(int size)
{
    lineSize = size;
    update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);  // parent class draws border

    QPainter painter(this);

    // white background (inside parent's border)
    painter.fillRect(QRect(1, 1, width() - 2, height() - 2), backgroundColor);

    // TODO; implement drawing functionality for all the primitives!
    // The following is just a basic example and to be removed...
    /*
    painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
    painter.drawLine(QPoint(2, height()/2), QPoint(width()-2, height()/2));
    painter.drawLine(QPoint(width()/2, 2), QPoint(width()/2, height()-2));
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::darkGreen);
    painter.drawEllipse(QPoint(width()/2, height()/2), 8, 8);
    */



    scene->display(&painter);
    if (dragging)
    {
        painter.setPen(QPen(color, lineSize, static_cast<Qt::PenStyle>(lineType)));
        if(fillMode){
            painter.setBrush(QBrush(color, Qt::SolidPattern));
        }else{
            painter.setBrush(QBrush(Qt::NoBrush));
        }

        switch (type)
        {
        case LINE:
        {
            painter.drawLine(startPnt, endPnt);
            break;
        }
        case CIRCLE:
        {
            int radius = hypot(endPnt.x() - startPnt.x(), endPnt.y() - startPnt.y()); // ((x2-x1)^2 + (y2-y1)^2))^(1/2)
            painter.drawEllipse(startPnt, radius, radius);
            break;
        }
        case RECTANGLE:
        {
            painter.drawRect(QRect(startPnt, endPnt));
            break;
        }
        case FREE_HAND:
        {
            for (int i = 1; i < pnts.size(); ++i)
            {
                painter.drawLine(pnts.at(i - 1), pnts.at(i));
            }
            break;

        }
        case TRIANGLE:
        {
            if(vertices.size() == 2){
                painter.drawLine(vertices.at(0), vertices.at(1));
                painter.drawLine(vertices.at(1), endPnt);
                painter.drawLine(endPnt, vertices.at(0));
            }
            else if (vertices.size() == 1)
            {
                painter.drawLine(vertices.at(0), endPnt);
            }

            break;
        }
        case POLYGON:
        {
            if (vertices.size() > 1)
            {
                for (int i = 1; i < vertices.size(); ++i)
                {
                    painter.drawLine(vertices.at(i - 1), vertices.at(i));
                }
                painter.drawLine(vertices.last(), endPnt);
            }
            else if (vertices.size() == 1)
            {
                painter.drawLine(vertices.at(0), endPnt);
            }
            break;
        }
        default:
            break;
        }
    }

}

void Canvas::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos(); //initialize lastPos with current mouse position
    if (event->button() == Qt::LeftButton) {
        switch(interactionMode){
        case CREATE:
            handleCreateMode(event);
            break;
        case DEL:
            handleDeleteMode(event);
            break;
        case COL:
            handleColorMode(event);
            break;
        case TRAFO:
            handleTransformMode(event);
            break;
        default:
            break;
        }

    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && dragging && interactionMode == CREATE) {

        endPnt = event->pos();
        if(type == FREE_HAND){
            pnts.append(endPnt);
        }

        update();
    }
    else if((event->buttons() & Qt::LeftButton) && dragging && interactionMode == TRAFO && objectSelected){
        QPoint currPos = event->pos();
        QPoint delta = currPos - lastPos;

        if(selectedObj != nullptr){
            selectedObj->move(delta);
        }
        lastPos = currPos;
        update();
    }
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && dragging && interactionMode == CREATE)
    {
        dragging = false;


        //TODO
        endPnt = event->pos();
        GraphObj* obj = nullptr;

        switch (type)
        {
        case LINE:
            if ((abs(endPnt.x() - startPnt.x()) > 2 || abs(endPnt.y() - startPnt.y()) > 2)){
                obj = new Line(startPnt, endPnt, color, lineType, lineSize);
            }
            break;
        case CIRCLE:
        {
            int radius = hypot(endPnt.x() - startPnt.x(), endPnt.y() - startPnt.y());
            if (radius > 2){
                obj = new Circle(startPnt, color, radius, fillMode, lineType, lineSize);

            }
            break;
        }
        case RECTANGLE:
            if ((abs(endPnt.x() - startPnt.x()) > 2 || abs(endPnt.y() - startPnt.y()) > 2)){
                obj = new Rectangle(startPnt, color, endPnt, fillMode, lineType, lineSize);
            }
            break;
        case FREE_HAND:
            if (pnts.size() > 2){
                obj = new Freeform(startPnt, color, pnts, lineType, lineSize);
            }
            break;
        case TRIANGLE:
        {
            vertices.append(endPnt);
            clickCount++;
            if(clickCount == 3){
                obj = new Triangle(vertices.at(0), vertices.at(1), endPnt, color, fillMode, lineType, lineSize);
                vertices.clear();
                clickCount = 0;
            }
            break;
        }
        case POLYGON:
        {
            if(!vertices.isEmpty() && snap(vertices.first(), endPnt)){
                obj = new Polygon(color, fillMode, vertices, lineType, lineSize);
                vertices.clear();
                clickCount = 0;
            }
            else{
                vertices.append(endPnt);
                clickCount++;
            }
            break;
        }
        default:
            break;
        }

        if (obj)
        {
            scene->insert(obj);
        }
        update();
    }
}

void Canvas::handleCreateMode(QMouseEvent *event)
{
    dragging = true;
    startPnt = event->pos();
    pnts.clear();
    pnts.append(startPnt);
    update();
}

void Canvas::handleDeleteMode(QMouseEvent *event)
{
    QPoint clickPoint = event->pos();
    scene->removeObjectAt(clickPoint);
    update();
}

void Canvas::handleColorMode(QMouseEvent *event)
{
    QPoint clickPoint = event->pos();
    scene->changeColorAt(clickPoint, color);
    update();
}

void Canvas::handleTransformMode(QMouseEvent *event)
{
    QPoint clickPoint = event->pos();
    selectedObj = scene->getObjAt(clickPoint);
    objectSelected = (selectedObj != nullptr);
    dragging = objectSelected;
    update();
}



bool Canvas::snap(const QPoint p1, const QPoint p2)
{
    const int snapDistance = 10; // pixels
    int dx = p1.x() - p2.x();
    int dy = p1.y() - p2.y();
    return (dx * dx + dy * dy) <= (snapDistance * snapDistance); /*compare if distance between startpnt and endpnt is more or less than pixels
                                                                 (if <= return true, if >= return false) */
}

