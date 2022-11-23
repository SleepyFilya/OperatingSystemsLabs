#include "mathmethod.h"


MathMethod::MathMethod(QObject* parent) : QObject (parent)
{

}

MathMethod::~MathMethod()
{

}

static int rrand(int range_min, int range_max)
{
    return rand() % (range_max - range_min + 1) + range_min;
}

double MathMethod::monteCarloMethod()
{
    const unsigned pointsNumb = 100000;
    unsigned count = 0;
    unsigned side = 1000;
    unsigned qSide = side * side;

    for(int i = 0; i < pointsNumb; i++)
    {
        unsigned x = rrand(0, side);
        unsigned y = rrand(0, side);

        if((x*x + y*y) < qSide) ++count;
    }

    pi = double(count * 4) / pointsNumb;

    return pi;
}
