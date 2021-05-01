#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QInputDialog>
#include <QMessageBox>
#include "numero.h"
#include "alu.h"
#include <sstream>
#include<string>
#include <bitset>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButtonCONVERSOR_released()
{

    //alU = alu(ui->lineEditNum1->text(),ui->lineEditNum2->text());
       float numA = ui->lineEditNum1->text().toFloat();
       float numB = ui->lineEditNum2->text().toFloat();

       alU = alu(numA,numB);

       ui->lineEditNum1IEEESIG->setText(alU.returnNum1('s'));
       ui->lineEditNum1IEEEEXP->setText(alU.returnNum1('e'));
       ui->lineEditNum1IEEEMAN->setText(alU.returnNum1('f'));

       ui->lineEditNum2IEEESIG->setText(alU.returnNum2('s'));
       ui->lineEditNum2IEEEEXP->setText(alU.returnNum2('e'));
       ui->lineEditNum2IEEEMAN->setText(alU.returnNum2('f'));
}



void MainWindow::on_pushButtonSUMA_released()
{
    float numA = ui->lineEditNum1->text().toFloat();
        float numB = ui->lineEditNum2->text().toFloat();

        alU = alu(numA,numB);

        alU.sumaIEE();
}

void MainWindow::on_pushButtonRESET_released()
{
    ui->lineEditNum1->setText("");
    ui->lineEditNum2->setText("");
    ui->lineEditNum1IEEESIG->setText("");
    ui->lineEditNum1IEEEEXP->setText("");
    ui->lineEditNum1IEEEMAN->setText("");
    ui->lineEditNum2IEEESIG->setText("");
    ui->lineEditNum2IEEEEXP->setText("");
    ui->lineEditNum2IEEEMAN->setText("");
    ui->lineEditNum1HEX->setText("");
    ui->lineEditNum2HEX->setText("");
    ui->lineEditRESIEEESIG->setText("");
    ui->lineEditRESIEEEEXP->setText("");
    ui->lineEditRESIEEEMAN->setText("");
    ui->lineEditResHEX->setText("");
    ui->lineEditResDec->setText("");
}

void MainWindow::on_pushButtonSALIR_released()
{
     ui->pushButtonSALIR->connect(ui->pushButtonSALIR, &QPushButton::clicked, qApp, &QApplication::quit);
}
