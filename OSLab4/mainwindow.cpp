#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threadManager = new ThreadManager();

    _pPrintResultTimer = new QTimer();
    _pPrintResultTimer->setInterval(1000);
    connect(_pPrintResultTimer, &QTimer::timeout, this, &MainWindow::printResult);
    _pPrintResultTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;

    _pPrintResultTimer->stop();
    delete _pPrintResultTimer;
    delete threadManager;
}

void MainWindow::printResult()
{
    qDebug() << "update pi";
    ui->controlValue->setText(threadManager->updateStatus());
}

void MainWindow::on_createThreadBtn_clicked()
{
    qDebug() << "1";
    int itemId = threadManager->createThread();
    qDebug() << "2: itemId = " << itemId;
    QString name = /*"Поток " + */QString::number(itemId);
    qDebug() << "3: name = " << name;

    ui->threadList->addItem(name);
    threadCount++;
    qDebug() << "Thread count: " << threadCount;
}

void MainWindow::on_deleteThreadBtn_clicked()
{
    qDebug() << "delet thread: " << ui->threadList->currentItem()->text().toInt();
    threadManager->deleteThread(ui->threadList->currentItem()->text().toInt());

    qDebug() << "delet row: " << ui->threadList->currentItem()->text().toInt();
    delete ui->threadList->takeItem(ui->threadList->currentRow());
    threadCount--;

    qDebug() << "Thread count: " << threadCount;
}

void MainWindow::on_startProcessBtn_clicked()
{
    threadManager->resumeThread(ui->threadList->currentItem()->text().toInt());
}

void MainWindow::on_pauseProcessBtn_clicked()
{
    threadManager->pauseThread(ui->threadList->currentItem()->text().toInt());
}

void MainWindow::on_priorityUpBtn_clicked()
{
    threadManager->increaseThreadPriority(ui->threadList->currentItem()->text().toInt());
}

void MainWindow::on_priorityDownBtn_clicked()
{
    threadManager->decreaseThreadPriority(ui->threadList->currentItem()->text().toInt());
}

