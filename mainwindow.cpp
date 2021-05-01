#include "mainwindow.h"
#include "ui_mainwindow.h"

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
