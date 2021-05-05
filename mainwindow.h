#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <alu.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSUMA_released();

    void on_pushButtonRESET_released();

    void on_pushButtonSALIR_released();

    void on_pushButtonPRODUCTO_released();

    void resetResultado();

    void setHexaResultado();

    void setHexaConversion();

    void setConversion(numero,numero);

private:
    Ui::MainWindow *ui;
    alu alU;

};
#endif // MAINWINDOW_H
