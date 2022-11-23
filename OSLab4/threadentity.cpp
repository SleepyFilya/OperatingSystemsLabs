#include "threadentity.h"

ThreadEntity::ThreadEntity(/*ThreadId*/ int id, AccumulatorPi *pAccumulator) : _pId(id), _pAccumulator(pAccumulator)/* : QThread()*/
{
    _pNeedTerminate = false;
    _pThread = new std::thread(&ThreadEntity::threadProc, this);
    _pPaused = false;

    _pPriority = THREAD_PRIORITY_NORMAL;
    SetThreadPriority(HANDLE(_pThread->native_handle()), _pPriority);
    SetThreadPriorityBoost(HANDLE(_pThread->native_handle()), FALSE);

    _pLastCalcs = 0;
    _pCalcsCount = 0;
}

ThreadEntity::~ThreadEntity()
{
    if(_pPaused)
        resume();

    _pNeedTerminate = true;
    _pThread->join();
    delete _pThread;
}

void ThreadEntity::pause()
{
    if(!_pPaused)
    {
        SuspendThread(HANDLE(_pThread->native_handle()));
        _pPaused = true;
    }
}

void ThreadEntity::resume()
{
    if(_pPaused)
    {
        ResumeThread(HANDLE(_pThread->native_handle()));
        _pPaused = false;
    }
}

void ThreadEntity::increasePriority()
{
    if(_pPriority < THREAD_PRIORITY_TIME_CRITICAL)
        _pPriority++;

    SetThreadPriority(HANDLE(_pThread->native_handle()), _pPriority);
}

void ThreadEntity::decreasePriority()
{
    if(_pPriority > THREAD_PRIORITY_IDLE)
        _pPriority--;

    SetThreadPriority(HANDLE(_pThread->native_handle()), _pPriority);
}

QString ThreadEntity::getStatus()
{
    if(_pPaused)
        return "на паузе";

    int speed = _pCalcsCount - _pLastCalcs;
    QString text = "запущен с приоритетом: " + QString::number(_pPriority)
            + ", нашел значение π " + QString::number(_pCalcsCount)
            + "раз, скорость: " + QString::number(speed) + "значений/сек";
}

void ThreadEntity::threadProc()
{
    while(!_pNeedTerminate)
    {
        _pCalcsCount++;
        _pAccumulator->addPi(_pMathMetod.monteCarloMethod());
    }
}
