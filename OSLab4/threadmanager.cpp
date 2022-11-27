#include "threadmanager.h"

ThreadManager::ThreadManager(QObject *parent) : QObject(parent)
{
    _pIdCount = 0;
    _pNoInfo = true;
}

ThreadManager::~ThreadManager()
{
    for(ThreadEntity* thread : _pThreadEntities)
      delete thread;

    _pThreadEntities.clear();
    _pNoInfo = true;
}

int ThreadManager::createThread()
{
    qDebug() << "createThread: ";
    _pIdCount++;
    _pThreadEntities.push_back(new ThreadEntity(_pIdCount, &_pAccumulator));

    for(ThreadEntity* thread : _pThreadEntities)
        qDebug() << thread;

    _pNoInfo = false;
    return _pIdCount;
}

void ThreadManager::increaseThreadPriority(int threadId)
{
    auto it = findThread(threadId);

    if(it != _pThreadEntities.end())
        (*it)->increasePriority();
}

void ThreadManager::decreaseThreadPriority(int threadId)
{
    auto it = findThread(threadId);

    if(it != _pThreadEntities.end())
        (*it)->decreasePriority();
}

void ThreadManager::pauseThread(int threadId)
{
    auto it = findThread(threadId);

    if(it != _pThreadEntities.end())
        (*it)->pause();
}

void ThreadManager::resumeThread(int threadId)
{
    auto it = findThread(threadId);

    if(it != _pThreadEntities.end())
        (*it)->resume();
}

void ThreadManager::deleteThread(int threadId)
{
    qDebug() << "ThreadManager::deleteThread";
    auto it = findThread(threadId);

    qDebug() << "it = " << it;

    qDebug() << "_pThreadEntities:";
    qDebug() << "before delete: ";
    for(ThreadEntity* thread : _pThreadEntities)
        qDebug() << thread;

    if(it != _pThreadEntities.end())
    {
        delete (*it);
        _pThreadEntities.erase(it);
    }

    qDebug() << "after delete: ";
    for(ThreadEntity* thread : _pThreadEntities)
        qDebug() << thread;
}

QString ThreadManager::updateStatus()
{
//    qDebug() << "threadManager updateStatus";
    if(_pNoInfo)
        return "π не вычислено\r\nЗапущенных потоков нет";

//    qDebug() << "_pInfo = true";
    const QString line = "\r\n";
    QString result = "π = " + QString::number(_pAccumulator.getPiValue()) + line;
//    qDebug() << "result: " << result;

    for(ThreadEntity* thread : _pThreadEntities)
    {
//        qDebug() << "_pThreadEntities:";
//        qDebug() << thread->getId();
//        qDebug() << thread->getStatus();
        result += "Поток " + QString::number(thread->getId()) + " " + thread->getStatus() + line;
    }
//    qDebug() << "result: " << result;

    return result;
}

QVector<ThreadEntity*>::iterator ThreadManager::findThread(int threadId)
{
    return std::find_if(_pThreadEntities.begin(), _pThreadEntities.end(), [threadId](const ThreadEntity* thread)
    {
        return thread->getId() == threadId;
    });
}




