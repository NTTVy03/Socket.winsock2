#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QLabel"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

//void MainWindow::TrucVy() {
//    QLabel *label = new QLabel(this);
//    label->setText("Truc Vy");
//    label->setGeometry(100, 100, 100, 100);

//    int t = 0;
//    while (t < 100) {
//        t+=1;
//        label->setGeometry(100+t, 100+t, 100, 100);
//        Sleep(1000);
//    }
//}

MainWindow::~MainWindow()
{
    delete ui;
}

