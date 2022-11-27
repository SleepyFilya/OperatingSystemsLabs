#include "threadentity.h"

DWORD WINAPI threadProccc(void *some)
{
    ThreadEntity* entity = (ThreadEntity*) some;
    entity->threadProc();

    return 0;
}

ThreadEntity::ThreadEntity(int id, AccumulatorPi *pAccumulator) : _pId(id), _pAccumulator(pAccumulator)/* : QThread()*/
{
    _pNeedTerminate = false;
    _pThread =  CreateThread(NULL, 0, threadProccc, this, 0, NULL);
    _pPaused = false;

    _pPriority = THREAD_PRIORITY_NORMAL;
    SetThreadPriority(_pThread, _pPriority);
    SetThreadPriorityBoost(_pThread, FALSE);

    _pLastCalcs = 0;
    _pCalcsCount = 0;
}

ThreadEntity::~ThreadEntity()
{
    if(_pPaused)
        resume();

    _pNeedTerminate = true;
}

void ThreadEntity::pause()
{
    if(!_pPaused)
    {
        SuspendThread(_pThread);
        _pPaused = true;
    }
}

void ThreadEntity::resume()
{
    if(_pPaused)
    {
        ResumeThread(_pThread);
        _pPaused = false;
    }
}

void ThreadEntity::increasePriority()
{
    if(_pPriority < THREAD_PRIORITY_TIME_CRITICAL)
        _pPriority++;

    SetThreadPriority(_pThread, _pPriority);
}

void ThreadEntity::decreasePriority()
{
    if(_pPriority > THREAD_PRIORITY_IDLE)
        _pPriority--;

    SetThreadPriority(_pThread, _pPriority);

    qDebug() << GetThreadPriority(_pThread);
}

QString ThreadEntity::getStatus()
{
    if(_pPaused)
        return "на паузе";

    int speed = _pCalcsCount - _pLastCalcs;
    _pLastCalcs = _pCalcsCount;

    QString text = "запущен с приоритетом: " + QString::number(_pPriority)
            + "\n\tнашел π " + QString::number(_pCalcsCount)
            + " раз, скорость: " + QString::number(speed) + " знач/сек";

    return text;
}

void ThreadEntity::threadProc()
{
    while(!_pNeedTerminate)
    {
        _pCalcsCount++;
        _pAccumulator->addPi(_pMathMetod.monteCarloMethod());
    }
}
