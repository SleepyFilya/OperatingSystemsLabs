#pragma once
//#ifndef THREADENTITY_H
//#define THREADENTITY_H

//#include <QThread>
#include <thread>

#include "threadmanager.h"
#include "mathmethod.h"

class ThreadEntity/* : public QThread*/
{
//    Q_OBJECT
public:
    ThreadEntity(/*ThreadId*/ int id, AccumulatorPi* pAccumulator);
    ~ThreadEntity();

//    bool isRunning;

    void pause();
    void resume();

    void increasePriority();
    void decreasePriority();

    QString getStatus();

    /*ThreadId*/ int getId() const { return _pId; }

signals:

public slots:

private:
    /*ThreadId*/ int _pId;
    MathMethod _pMathMetod;
    AccumulatorPi* _pAccumulator;
    std::thread* _pThread;
    int _pPriority;
    std::atomic_bool _pNeedTerminate;
    std::atomic_int _pCalcsCount;
    int _pLastCalcs;
    bool _pPaused;

    void threadProc();
};

//#endif // THREADENTITY_H
