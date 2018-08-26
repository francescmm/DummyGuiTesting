#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTimer>
#include <QCheckBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent), ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   ui->cbLogin->addItems ({"Item 1", "Item 2", "Item 3"});
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::slotLogin()
{
   if (ui->lePassword->text() == "1234" and ui->leUsername->text() == "admin")
   {
      ui->pbAddUser->setDisabled(true);

      ui->statusBar->showMessage("Requested add user...");

      QTimer::singleShot(3000, this, &MainWindow::onLoginSuccess);
   }
   else
      emit signalLogginFailed();
}

void MainWindow::onLoginSuccess()
{
   ui->statusBar->showMessage("Login added successfully!");

   auto userAdded = ui->leUsername->text();

   ui->pbAddUser->setEnabled(true);

   ui->leUsername->setText("");
   ui->lePassword->setText("");

   auto rowToInsert = ui->listWidget->count ();
   auto item = new QListWidgetItem(userAdded);
   ui->listWidget->insertItem (ui->listWidget->count (), item);

   /*
   auto checkBox = new QCheckBox();
   auto label = new QLabel(userAdded);

   auto itemLayout = new QHBoxLayout();
   itemLayout->addWidget (checkBox);
   itemLayout->addWidget (label);

   auto itemWidget = new QWidget();
   itemWidget->setLayout (itemLayout);

   ui->listWidget->setItemWidget (item, itemWidget);
   */

   emit signalIsLogged(userAdded);
}
