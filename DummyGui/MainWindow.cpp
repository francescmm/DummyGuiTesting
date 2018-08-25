#include "MainWindow.h"
#include "ui_MainWindow.h"

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

void MainWindow::slotLogin()
{
    if (ui->lePassword->text() == "admin" and ui->leUsername->text() == "admin")
        emit signalIsLogged();
    else
        emit signalLogginFailed();
}
