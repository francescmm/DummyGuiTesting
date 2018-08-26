#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotLogin()
{
    ui->pbLogin->setDisabled(true);

    if (ui->lePassword->text() == "1234" and ui->leUsername->text() == "admin")
    {
        ui->statusBar->showMessage("Login requested...");

        QTimer::singleShot(3000, this, &MainWindow::onLoginSuccess);
    }
    else
        emit signalLogginFailed();
}

void MainWindow::onLoginSuccess()
{
    ui->statusBar->showMessage("Login successful!");

    emit signalIsLogged(ui->leUsername->text());

    ui->pbLogin->setEnabled(true);

    ui->leUsername->setText("");
    ui->lePassword->setText("");
}
