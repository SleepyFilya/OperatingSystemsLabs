#ifndef MATHMETHOD_H
#define MATHMETHOD_H

#include "defines.h"
#include "math.h"

#include <QVariant>
#include <QDebug>

class MathMethod : public QObject
{
    Q_OBJECT

public:
    explicit MathMethod(QObject *parent = nullptr);
    ~MathMethod();

    double monteCarloMethod();

signals:
    void sendResult(double pi);

private:
    float pi = 0;
};

#endif // MATHMETHOD_H
