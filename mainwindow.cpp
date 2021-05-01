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


void MainWindow::on_pushButtonSALIR_released()
{
    ui->pushButtonSALIR->connect(ui->pushButtonSALIR, &QPushButton::clicked, qApp, &QApplication::quit);

}

void MainWindow::on_pushButtonCONVERSOR_released()
{

    std::string numero1 = ui->lineEditNum1->text().toStdString();
    std::string numero2 = ui->lineEditNum2->text().toStdString();

    float num1Flotante = std::stof(numero1);
    float num2Flotante = std::stof(numero2);
    Numero num1;
    Numero num2;

    num1.setNumeroFlotante(num1Flotante);
    num1.floattoIEE(num1.getNumeroFlotante());

    num2.setNumeroFlotante(num2Flotante);
    num2.floattoIEE(num2.getNumeroFlotante());

    std::bitset<1> sig1(num1.getSigno());
    std::bitset<8> exp1(num1.getExpo());
    //complemento a 1 de un numero
    std::bitset<8> complemento1( ~num1.getExpo());

     // Aqui calculamos el complemento a 2 del exponente.
    std::bitset<8> complemento2((~num1.getExpo())+1);

    //complemento2 = complemento1 +uno;
    std::cout <<"complemento a 1 del exponente del primer numero: " << complemento1 <<std::endl;
    std::cout <<"complemento a 2 del exponente del primer numero: " << complemento2 <<std::endl;
   //std::bitset<24> parteMantisa1(num1.getMantisa());
    //parteMantisa1[23]= 1;
    std::bitset<23> parteFraccionaria1(num1.getMantisa()); // para hacer la traducccion
    //std::cout << "longitud de bitset: "<< parteMantisa1.size() << std::endl;

    std::string resultado1 = num1.cadenaConcatenadaBinaria(sig1.to_string(),exp1.to_string(),parteFraccionaria1.to_string());
    std:: string cad_Hexadecimal = num1.conversorBinarioHexadecimal(resultado1);
    std::string prefijo = "0X";
    std::string prefijo2 = prefijo;
    std::string resultadoHexadecimal = prefijo.append(cad_Hexadecimal);
    QString res1 = QString::fromUtf8(resultadoHexadecimal.c_str());


    std::bitset<1> sig2(num2.getSigno());
    std::bitset<8> exp2(num2.getExpo());

    //std::bitset<24> parteMantisa2(num2.getMantisa());
     //parteMantisa2[23]= 1;
    std::bitset<23> parteFraccionaria2(num2.getMantisa());



    std::string resultado2 = num2.cadenaConcatenadaBinaria(sig2.to_string(),exp2.to_string(),parteFraccionaria2.to_string());
    std:: string cad_Hexadecimal2 = num2.conversorBinarioHexadecimal(resultado2);
    //std::string prefijo2 = "0X";
    std::string resultadoHexadecimal2 = prefijo2.append(cad_Hexadecimal2);
    QString res2 = QString::fromUtf8(resultadoHexadecimal2.c_str());


    QString signo_1 = QString::fromLocal8Bit(sig1.to_string().c_str()); //para pasar de string  a qstring los bits
    QString partefraccionaria_1 = QString::fromLocal8Bit(parteFraccionaria1.to_string().c_str());
    QString exponente_1= QString::fromLocal8Bit(exp1.to_string().c_str());
    ui->lineEditNum1IEEESIG->setText(signo_1);
    ui->lineEditNum1IEEEEXP->setText(exponente_1);
    ui->lineEditNum1IEEEMAN->setText(partefraccionaria_1);

    QString signo_2 = QString::fromLocal8Bit(sig2.to_string().c_str()); //para pasar de string  a qstring los bits
    QString partefraccionaria_2 = QString::fromLocal8Bit(parteFraccionaria2.to_string().c_str());
    QString exponente_2= QString::fromLocal8Bit(exp2.to_string().c_str());
    ui->lineEditNum2IEEESIG->setText(signo_2);
    ui->lineEditNum2IEEEEXP->setText(exponente_2);
    ui->lineEditNum2IEEEMAN->setText(partefraccionaria_2);
    ui->lineEditNum1HEX->setText(res1);
    ui->lineEditNum2HEX->setText(res2);

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

void MainWindow::on_pushButtonSUMA_released()
{
    Numero num1;
    Numero num2;
    Numero resultado;
    Alu alu;
    std::string numero1 = ui->lineEditNum1->text().toStdString();
    std::string numero2 = ui->lineEditNum2->text().toStdString();

    float num1Flotante = std::stof(numero1);
    float num2Flotante = std::stof(numero2);

    num1.setNumeroFlotante(num1Flotante);
    num2.setNumeroFlotante(num2Flotante);
    resultado = alu.suma(num1,num2);
    std::bitset<1> sigResultado(resultado.getSigno());
    QString signo_resultado = QString::fromLocal8Bit(sigResultado.to_string().c_str());
    ui->lineEditRESIEEESIG->setText(signo_resultado);

    std::bitset<8> expResultado(resultado.getExpo());
    QString exp_resultado = QString::fromLocal8Bit(expResultado.to_string().c_str());
    ui->lineEditRESIEEEEXP->setText(exp_resultado);

    std::bitset<23> ParteFraccRes;
    for (int i = 0; i < 23; i++){
        ParteFraccRes[i] = resultado.getMantisaBinaria()[i];
    }

    QString ParteFracc_resultado = QString::fromLocal8Bit(ParteFraccRes.to_string().c_str());
    ui->lineEditRESIEEEMAN->setText(ParteFracc_resultado);
    std::string prefijo = "0X";
    std::string resultadoHexa = resultado.cadenaConcatenadaBinaria(sigResultado.to_string(),expResultado.to_string(),ParteFraccRes.to_string());
    std::string cadenaConvertida = resultado.conversorBinarioHexadecimal(resultadoHexa);
    std::string cadenaCompleta = prefijo.append(cadenaConvertida);
    QString cadBienFormada = QString::fromLocal8Bit(cadenaCompleta.c_str());
    ui->lineEditResHEX->setText(cadBienFormada);


    unsigned int mantisadecimal = resultado.getMantisaBinaria().to_ulong();
    unsigned int misigno = resultado.getSigno();
    unsigned int exponente = resultado.getExpo();
    float minumero = resultado.IEEtofloat(exponente,misigno,mantisadecimal);
    std::cout<<"mi numero en decimal es: "<<minumero<<::std::endl;
    QString resultadoDecimal = QString::number(minumero);
    ui->lineEditResDec->setText(resultadoDecimal);
}
