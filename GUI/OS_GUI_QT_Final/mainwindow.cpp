#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "open.h"
#include <iostream>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int Num_of_Basket = ui->lineEdit->text().toInt();
    int Num_of_Bathroom = ui->lineEdit_2->text().toInt();
    double Arriving_Rate = ui->lineEdit_3->text().toDouble();

    Open(Num_of_Basket, Num_of_Bathroom, Arriving_Rate);
}
