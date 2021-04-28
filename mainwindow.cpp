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


void MainWindow::on_pushButton_released()
{

    Alu a = Alu((ui->num1->text()).toFloat(),2.3);
    ui->signo->setText(a.getSigno());
    ui->exponente->setText(a.getExp());
    ui->pFrac->setText(a.getPFrac());

}
