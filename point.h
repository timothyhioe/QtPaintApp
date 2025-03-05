#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    Point(int xAxis, int yAxis);
    int getXAxis() const;
    int getYAxis() const;

private:
    int xAxis;
    int yAxis;
};

#endif // POINT_H
