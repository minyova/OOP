#ifndef BALL_H
#define BALL_H

#include <QtMath>

class Ball
{
public:
    Ball(int radius, int speed, int angle, int fieldWidth, int fieldHeight);

    void move();
    void handleCollision();
    void resetToCenter(int speed, int angle);

    int getX() const { return x; }
    int getY() const { return y; }
    int getRadius() const { return radius; }
    int getSpeed() const { return speed; }
    int getAngle() const { return angle; }

private:
    int x, y;
    int radius;
    int speed;
    int angle;
    int vx, vy;
    int fieldWidth, fieldHeight;
};

#endif // BALL_H
