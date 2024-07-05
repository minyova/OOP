#include "field.h"

Field::Field(int width, int height)
    : width(width), height(height)
{
}

bool Field::checkCollision(const Ball& ball)
{
    int ballX = ball.getX();
    int ballY = ball.getY();
    int ballRadius = ball.getRadius();

    return (ballX - ballRadius < 0 || ballX + ballRadius > width ||
            ballY - ballRadius < 0 || ballY + ballRadius > height);
}
