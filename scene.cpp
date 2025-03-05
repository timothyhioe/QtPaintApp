#include "scene.h"

using namespace std;

Scene::Scene(int width, int height, const std::vector<GraphObj *> &objBag) : objBag(objBag), width(width), height(height)
{}

Scene::~Scene(){
    for (auto obj : objBag) {
        delete obj;
    }
}

Scene::Scene(Scene &&other)
{
    // move 'this' value to 'other' value
    this->objBag = std::move(other.objBag);
    this->width = other.width;
    this->height = other.height;

    // the moved value will be set to null for the destructor
    other.width = 0;
    other.height = 0;
}

Scene &Scene::operator=(Scene &&other)
{
    if (this != &other) {
        objBag.clear();

        width = other.width;
        height = other.height;
        objBag = std::move(other.objBag);

        other.width = 0;
        other.height = 0;
    }
    return *this;
}

GraphObj *Scene::at(int index)
{
    if(index >= 0 && index < objBag.size()){
        return objBag.at(index);
    }
    return nullptr;
}

void Scene::insert(GraphObj * obj)
{
    objBag.push_back(obj);
}

void Scene::remove(GraphObj * obj)
{
    for(unsigned int i = 0; i < objBag.size(); i++){
        if(objBag.at(i) == obj){
            delete objBag.at(i);
            objBag.erase(objBag.begin() + i); // Remove the object from the vector
            break;
        }
    }
}

void Scene::removeAll()
{
    qDeleteAll(objBag);
    objBag.clear();
}

void Scene::display(QPainter* painter)
{
    for(unsigned int i = 0; i < objBag.size(); i++){
        objBag.at(i)->display(painter);
    }
}

void Scene::removeObjectAt(const QPoint& point) {
    for (auto it = objBag.begin(); it != objBag.end(); ++it) {
        if ((*it)->inside(point)) {
            delete *it;
            objBag.erase(it);
            return;
        }
    }
}

void Scene::changeColorAt(const QPoint &point, const QColor &color)
{
    for(auto& obj : objBag){
        if(obj->inside(point)){
            obj->setColor(color);
            return;
        }
    }
}

GraphObj *Scene::getObjAt(const QPoint &point)
{
    for(auto& obj : objBag){
        if(obj->inside(point)){
            return obj;
        }
    }
    return nullptr;
}

std::vector<GraphObj *> Scene::getObjBag()
{
    return objBag;
}






