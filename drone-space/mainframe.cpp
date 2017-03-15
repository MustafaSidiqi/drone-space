#include "mainframe.h"
#include "ui_mainframe.h"

MainFrame::MainFrame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);   

    ui->stackedWidget->setCurrentIndex(0);

}

MainFrame::~MainFrame()
{
    delete ui;
}

void MainFrame::on_inputUsername_returnPressed()
{


    username = ui->inputUsername->text();

    ui->stackedWidget->setCurrentIndex(1);

}

void MainFrame::on_inputPassword_returnPressed()
{
    password = ui->inputPassword->text();

    if(username == "niklas" && password == "1234") {
        ui->stackedWidget->setCurrentIndex(2);
        ui->statusBar->showMessage("Access Granted!",5000);
    } else {
        ui->stackedWidget->setCurrentIndex(0);
        ui->statusBar->showMessage("Access Denied!",5000);
    }
}
