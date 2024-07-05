#include "ball.h"

Ball::Ball(int radius, int speed, int angle, int fieldWidth, int fieldHeight)
    : radius(radius), speed(speed), angle(qDegreesToRadians(angle)),
    fieldWidth(fieldWidth), fieldHeight(fieldHeight)
{
    x = fieldWidth / 2;
    y = fieldHeight / 2;
    vx = speed * qCos(qDegreesToRadians(angle));
    vy = -speed * qSin(qDegreesToRadians(angle));
}

void Ball::move()
{
    x += vx;
    y += vy;
}

void Ball::handleCollision()
{
    if (x - radius < 0 || x + radius > fieldWidth) {
        vx = -vx;
    }
    if (y - radius < 0 || y + radius > fieldHeight) {
        vy = -vy;
    }
}

void Ball::resetToCenter(int speed, int angle)
{
    x = fieldWidth / 2;
    y = fieldHeight / 2;
    this->speed = speed;
    this->angle = angle;
    vx = speed * qCos(qDegreesToRadians(angle));
    vy = -speed * qSin(qDegreesToRadians(angle));
}
