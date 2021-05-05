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

        float numA = ui->lineEditNum1->text().toFloat();
        float numB = ui->lineEditNum2->text().toFloat();

        alU = alu();

        numero numeroSuma;
        numeroSuma = alU.sumaIEE(numA,numB);

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

    alU = alu();

    numero numeroProducto;
    numeroProducto = alU.productoIEE(numA,numB);

    /*if(numeroProducto.getIndeterminado()==true){
        ui->lineEditResDec->setText("indeterminado");
        ui->lineEditRESIEEEEXP->setText("-----");
        ui->lineEditRESIEEESIG->setText("-------------");
        ui->lineEditRESIEEEMAN->setText("--------------");
        ui->lineEditResHEX->setText("");

    }*/
    if(numeroProducto.getInfinito() == true){
        if(numeroProducto.getSing()==0){
            ui->lineEditResDec->setText("infinito");
        }else{
            ui->lineEditResDec->setText("-infinito");
        }
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

