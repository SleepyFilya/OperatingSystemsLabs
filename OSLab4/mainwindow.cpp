#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mathMethod = new MathMethod();

    setConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mathMethod;
}

void MainWindow::setConnections()
{
    connect(mathMethod, &MathMethod::sendResult, this, &MainWindow::printResult);
}

void MainWindow::on_startProcessBtn_clicked()
{
    mathMethod->monteCarloMethod();
}

void MainWindow::printResult(double pi)
{
    ui->controlValue->setText(QString::number(pi));
}

