#ifndef SCENE_H
#define SCENE_H
#include "graphobj.h"
#include <vector>

class Scene
{
public:
    Scene() {}
    Scene(int width, int height, const std::vector<GraphObj *> &objBag);

    //destruktor
    virtual ~Scene();

    // Delete copy constructor and copy assignment operator
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    //move konstruktor
    Scene(Scene&& other);

    //move asignment operator
    Scene& operator=(Scene&& other);

    GraphObj* at(int);
    void insert(GraphObj*);
    void remove(GraphObj*);
    void removeAll();
    void display(QPainter*);
    void removeObjectAt(const QPoint& point);
    void changeColorAt(const QPoint& point, const QColor& color);
    GraphObj* getObjAt(const QPoint& point);

    std::vector<GraphObj*> getObjBag();
private:
    std::vector<GraphObj*> objBag;
    int width;
    int height;


};

#endif // SCENE_H
