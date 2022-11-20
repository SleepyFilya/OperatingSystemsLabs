#ifndef THREADENTITY_H
#define THREADENTITY_H

#include <QThread>

class ThreadEntity : public QThread
{
    Q_OBJECT
public:
    ThreadEntity();
    ~ThreadEntity();

    bool isRunning;

signals:

public slots:
};

#endif // THREADENTITY_H
