#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mathmethod.h"
#include "threadmanager.h"

#include <QMainWindow>
#include <QDebug>
#include <QObject>
#include <QTimer>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void printResult();

private slots:
    void on_startProcessBtn_clicked();

    void on_createThreadBtn_clicked();

    void on_deleteThreadBtn_clicked();

    void on_pauseProcessBtn_clicked();

    void on_priorityUpBtn_clicked();

    void on_priorityDownBtn_clicked();

private:
    Ui::MainWindow* ui;

    QTimer* _pPrintResultTimer;
    ThreadManager* threadManager;

    int threadCount = 0;
};

#endif // MAINWINDOW_H
