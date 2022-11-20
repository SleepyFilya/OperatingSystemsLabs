#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"
#include "mathmethod.h"

#include <QMainWindow>
#include <QDebug>
#include <QObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void printResult(double pi);

private slots:
    void on_startProcessBtn_clicked();

private:
    Ui::MainWindow* ui;

    MathMethod* mathMethod;

    void setConnections();

};

#endif // MAINWINDOW_H
