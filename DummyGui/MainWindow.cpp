#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTimer>
#include <QCheckBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent), ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
   ui->tableWidget->setShowGrid(false);
   ui->tableWidget->setColumnCount(2);
   ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
   ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
   ui->tableWidget->verticalHeader()->setVisible(false);

   ui->cbLogin->addItems ({"Item 1", "Item 2", "Item 3"});
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::slotLogin()
{
   if (ui->leUsername->text().contains("admin"))
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

   auto tableRowWhereInsert = ui->tableWidget->rowCount();

   ui->tableWidget->insertRow(tableRowWhereInsert);
   ui->tableWidget->setCellWidget(tableRowWhereInsert, 0, new QCheckBox(""));
   ui->tableWidget->setCellWidget(tableRowWhereInsert, 1, new QLabel(userAdded));

   emit signalIsLogged(userAdded);
}

void MainWindow::addEntryToList()
{
    ui->statusBar->showMessage("Added new entrey in the list!");

    auto item = new QListWidgetItem("newUser" + QString::number(ui->listWidget->count()));
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    ui->listWidget->addItem(item);
}
