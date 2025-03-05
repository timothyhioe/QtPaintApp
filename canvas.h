#ifndef CANVAS_H
#define CANVAS_H
#include "scene.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "freeform.h"
#include "triangle.h"
#include "polygon.h"


#include <QFrame>
#include <QVector>

class Canvas : public QFrame
{
	Q_OBJECT

public:
    enum InteractionMode {
        CREATE, DEL, COL, TRAFO
    };
	enum PrimitiveMode {
        NONE, LINE, FREE_HAND, CIRCLE, RECTANGLE, TRIANGLE, POLYGON
	};

    Canvas(QWidget *parent = 0);
	~Canvas();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void clearCanvas(void);
	void setPrimitiveMode(int mode);
    void setObjColor(const QColor &col);
    void setFillMode(bool filled);
    void setInteractionMode(int mode);

    void setBackgroundColor(const QColor& col);

    void setLineType(int type);
    void setLineSize(int size);

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);


private:
	bool dragging;
	PrimitiveMode type;
    Scene* scene;
    InteractionMode interactionMode;

    void handleCreateMode(QMouseEvent *event);
    void handleDeleteMode(QMouseEvent *event);
    void handleColorMode(QMouseEvent *event);
    void handleTransformMode(QMouseEvent *event);

    QColor color;
    bool fillMode;

    QPoint startPnt;
    QPoint endPnt;
    QVector<QPoint> pnts;

    int clickCount;
    QVector<QPoint> vertices;

    bool snap(const QPoint p1, const QPoint p2);

    //for move methode
    QPoint lastPos;
    bool objectSelected;
    GraphObj* selectedObj;


    //background color new feature
    QColor backgroundColor;

    //line type and size
    int lineType;
    int lineSize;
};

#endif // CANVAS_H
