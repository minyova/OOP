#ifndef FIELD_H
#define FIELD_H

#include "ball.h"

class Field
{
public:
    Field(int width, int height);

    bool checkCollision(const Ball& ball);

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }
private:
    int width, height;
};

#endif // FIELD_H
