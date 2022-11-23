//#ifndef ACCUMULATORPI_H
//#define ACCUMULATORPI_H
#pragma once
#include <mutex>


class AccumulatorPi
{
public:
    AccumulatorPi() : _pSum(0), _pCount(0) {}

    void addPi(double pi)
    {
        std::unique_lock<std::mutex> lock(_pMtx);
        _pSum += pi;
        _pCount++;
    }

    double getPiValue()
    {
        std::unique_lock<std::mutex>(m_Mtx);
        return _pSum / _pCount;
    }

private:
    double _pSum;
    int _pCount;

    std::mutex _pMtx;
};

//#endif // ACCUMULATORPI_H
