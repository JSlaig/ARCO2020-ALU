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

       std::string prefijo = "0x";
       std::string prefijo2;
       prefijo2 = prefijo;
       alU = alu(numA,numB);

       /*Conversion FloatToIEE*/
       ui->lineEditNum1IEEESIG->setText(alU.returnNum1('s'));
       ui->lineEditNum1IEEEEXP->setText(alU.returnNum1('e'));
       ui->lineEditNum1IEEEMAN->setText(alU.returnNum1('f'));

       ui->lineEditNum2IEEESIG->setText(alU.returnNum2('s'));
       ui->lineEditNum2IEEEEXP->setText(alU.returnNum2('e'));
       ui->lineEditNum2IEEEMAN->setText(alU.returnNum2('f'));

       setHexaConversion();
       setHexaResultado();

}

void MainWindow::resetResultado()
{
        ui->lineEditRESIEEESIG->setText("");
        ui->lineEditRESIEEEEXP->setText("");
        ui->lineEditRESIEEEMAN->setText("");
        ui->lineEditResHEX->setText("");
        ui->lineEditResDec->setText("");
}

void MainWindow::on_pushButtonSUMA_released()
{
        resetResultado();
        MainWindow::on_pushButtonCONVERSOR_released();

        float numA = ui->lineEditNum1->text().toFloat();
        float numB = ui->lineEditNum2->text().toFloat();

        alU = alu(numA,numB);

        numero numeroSuma;
        numeroSuma = alU.sumaIEE();

        ui->lineEditResDec->setText(QString::number(numeroSuma.getNum()));
        ui->lineEditRESIEEEEXP->setText(QString::fromStdString(numeroSuma.getExpoBit().to_string()));
        ui->lineEditRESIEEESIG->setText(QString::number(numeroSuma.getSing()));
        ui->lineEditRESIEEEMAN->setText(QString::fromStdString(numeroSuma.getPartFracBit().to_string()));

        setHexaConversion();
        setHexaResultado();
}

void MainWindow::on_pushButtonRESET_released()
{



    ui->lineEditNum1->setText("");
    ui->lineEditNum2->setText("");
    ui->lineEditNum1IEEESIG->setText("");
    ui->lineEditNum1IEEEEXP->setText("");
    ui->lineEditNum2IEEEEXP->setText("");
    ui->lineEditNum2IEEEMAN->setText("");
    ui->lineEditNum1HEX->setText("");
    ui->lineEditNum2HEX->setText("");
    ui->lineEditRESIEEESIG->setText("");
    ui->lineEditNum1IEEEMAN->setText("");
    ui->lineEditNum2IEEESIG->setText("");
    ui->lineEditRESIEEEEXP->setText("");
    ui->lineEditRESIEEEMAN->setText("");
    ui->lineEditResHEX->setText("");
    ui->lineEditResDec->setText("");
}

void MainWindow::on_pushButtonSALIR_released()
{
     ui->pushButtonSALIR->connect(ui->pushButtonSALIR, &QPushButton::clicked, qApp, &QApplication::quit);
}

void MainWindow::on_pushButtonPRODUCTO_released()
{

    resetResultado();
    float numA = ui->lineEditNum1->text().toFloat();
    float numB = ui->lineEditNum2->text().toFloat();
    alU = alu(numA,numB);
     MainWindow::on_pushButtonCONVERSOR_released();
    numero numeroProducto;
    numeroProducto = alU.productoIEE();
    /*if(numeroProducto.getIndeterminado()==true){
        ui->lineEditResDec->setText("indeterminado");
        ui->lineEditRESIEEEEXP->setText("-----");
        ui->lineEditRESIEEESIG->setText("-------------");
        ui->lineEditRESIEEEMAN->setText("--------------");
        ui->lineEditResHEX->setText("");

    }*/
    if(numeroProducto.getInfinito() == true){
         ui->lineEditResDec->setText("infinito");
         ui->lineEditRESIEEEEXP->setText("-----");
         ui->lineEditRESIEEESIG->setText("-------------");
         ui->lineEditRESIEEEMAN->setText("--------------");
         ui->lineEditResHEX->setText("");
         return;
    }else{
        if (!numeroProducto.getNan() && !numeroProducto.getInfinito()&& !numeroProducto.getIndeterminado()){


        ui->lineEditResDec->setText(QString::number(numeroProducto.getNum()));
        std::cout<<numeroProducto.getNum()<<std::endl;
        ui->lineEditRESIEEEEXP->setText(QString::fromStdString(numeroProducto.getExpoBit().to_string()));
        ui->lineEditRESIEEESIG->setText(QString::number(numeroProducto.getSing()));
        ui->lineEditRESIEEEMAN->setText(QString::fromStdString(numeroProducto.getPartFracBit().to_string()));
        }else{
        ui->lineEditResDec->setText("NaN");
        ui->lineEditRESIEEEEXP->setText("11111111");
        ui->lineEditRESIEEESIG->setText("1");
        ui->lineEditRESIEEEMAN->setText("11111111111111111111111");
        }
        return;
    }
    setHexaConversion();
    setHexaResultado();


}
void MainWindow::setHexaConversion(){


    /*Datos*/

        std::string prefijo = "0x";
        std::string prefijo2;
        prefijo2 = prefijo;

    /*Conversion a Hexadecimal*/

          std::string signo1= ui->lineEditNum1IEEESIG->text().toUtf8().constData();
          std::string exponente1= ui->lineEditNum1IEEEEXP->text().toUtf8().constData();
          std::string mantisa1= ui->lineEditNum1IEEEMAN->text().toUtf8().constData();
          std::string resultado1 = alU.cadenaConcatenadaBinaria(signo1,exponente1,mantisa1);
          std:: string cad_Hexadecimal = alU.conversorBinarioHexadecimal(resultado1);
          std::string resultadoHexadecimal = prefijo.append(cad_Hexadecimal);
          QString res1 = QString::fromUtf8(resultadoHexadecimal.c_str());
          ui->lineEditNum1HEX->setText(res1);

          std::string signo2= ui->lineEditNum2IEEESIG->text().toUtf8().constData();
          std::string exponente2= ui->lineEditNum2IEEEEXP->text().toUtf8().constData();
          std::string mantisa2= ui->lineEditNum2IEEEMAN->text().toUtf8().constData();
          std::string resultado2 = alU.cadenaConcatenadaBinaria(signo2,exponente2,mantisa2);
          std:: string cad_Hexadecimal2 = alU.conversorBinarioHexadecimal(resultado2);
          std::string resultadoHexadecimal2 = prefijo2.append(cad_Hexadecimal2);
          QString res2 = QString::fromUtf8(resultadoHexadecimal2.c_str());
          ui->lineEditNum2HEX->setText(res2);


}
void MainWindow::setHexaResultado(){

    /*Datos*/
    std::string prefijo = "0x";
    std::string prefijo2;
    prefijo2 = prefijo;

    /*Conversion a Hexadecimal*/
    std::string signo1= ui->lineEditRESIEEESIG->text().toUtf8().constData();
    std::string exponente1= ui->lineEditRESIEEEEXP->text().toUtf8().constData();
    std::string mantisa1= ui->lineEditRESIEEEMAN->text().toUtf8().constData();
    std::string resultado1 = alU.cadenaConcatenadaBinaria(signo1,exponente1,mantisa1);
    std:: string cad_Hexadecimal = alU.conversorBinarioHexadecimal(resultado1);
    std::string resultadoHexadecimal = prefijo.append(cad_Hexadecimal);
    QString res1 = QString::fromUtf8(resultadoHexadecimal.c_str());

    ui->lineEditResHEX->setText(res1);

}

