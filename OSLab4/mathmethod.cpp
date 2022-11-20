#include "mathmethod.h"


MathMethod::MathMethod(QObject* parent) : QObject (parent)
{

}

MathMethod::~MathMethod()
{

}

void MathMethod::monteCarloMethod()
{
    const int pointsNumb = 1000;

    float x = 0;
    float y = 0;

    int totalPoints = 0;
    int circlePoints = 0;

    const float step = 1 / (float)pointsNumb;

    while(y < 1)
    {
        while(x < 1)
        {
            totalPoints++;

            if(isCircle(x, y))
                circlePoints++;

            x += step;
        }

        x = 0;
        y += step;
    }

    pi = 4 * circlePoints / (float)totalPoints;

    emit sendResult(pi);
}

double MathMethod::circle(double x, double radius)
{
    double y = radius * radius - x * x;
    return y;
}

bool MathMethod::isCircle(float x, float y)
{
    return x*x + y*y < 1;
}
