#include <QCoreApplication>
#include <QLineEdit>
#include <QSignalSpy>
#include <QtTest>

// Additional includes
#include "MainWindow.h"
#include "MainWindowTest.h"
#include "TestManager.h"
#include "ui_MainWindow.h"
#include <QtWidgets/QMainWindow>

void MainWindowTest::testValid()
{
   QFETCH(int, year);
   QFETCH(int, month);
   QFETCH(int, day);

   QDate date(year, month, day);
   QTEST(date.isValid(), "valid");
}

void MainWindowTest::testValid_data()
{
   QTest::addColumn<int>("year");
   QTest::addColumn<int>("month");
   QTest::addColumn<int>("day");
   QTest::addColumn<bool>("valid");

   QTest::newRow("Valid, normal") << 1973 << 8 << 16 << true;
   QTest::newRow("Invalid, normal") << 1973 << 9 << 31 << false;
   QTest::newRow("Valid, leap-year") << 1980 << 2 << 29 << true;
   QTest::newRow("Invalid, leap-year") << 1981 << 2 << 29 << false;
}

MainWindowTest::MainWindowTest()
   : BaseTest()
{
}

void MainWindowTest::initTestCase()
{
   mainWindow = new MainWindow();
   mainWindow->show();

   QVERIFY(mainWindow->isVisible());
}

void MainWindowTest::cleanupTestCase()
{
   mainWindow->close();

   QVERIFY(!mainWindow->isVisible());

   delete mainWindow;
   mainWindow = nullptr;
}

void MainWindowTest::cleanup()
{
   const auto colCount = mainWindow->ui->tableWidget->columnCount();

   for (auto row = mainWindow->ui->tableWidget->rowCount() - 1; row >= 0; --row)
   {
      for (auto col = 0; col < colCount; ++col)
         delete mainWindow->ui->tableWidget->cellWidget(row, col);

      mainWindow->ui->tableWidget->removeRow(row);
   }

   mainWindow->ui->tableWidget->clearContents();

   for (auto row = mainWindow->ui->listWidget->count() - 1; row >= 0; --row)
   {
      const auto item = mainWindow->ui->listWidget->item(row);
      delete mainWindow->ui->listWidget->itemWidget(item);

      delete item;
   }

   mainWindow->repaint();
}

void MainWindowTest::testWithWarnings()
{
   QWARN("Test is empty. Fill it with something!");
}

void MainWindowTest::testSkipedWithMessage()
{
   QSKIP("Test skiped voluntary.");

   // The following content won't be executed
   QCOMPARE(0.0, 1.0);
}

void MainWindowTest::testWithExpectedFailures()
{
   QEXPECT_FAIL("", "First QVERIFY or QCOMPARE of the test won't fail the test. We can choose Continue or Abort.",
                TestFailMode::Continue);

   auto i = 0;
   QCOMPARE(i, 42);

   // If we add more QCOMPARE or QVERIFY they must be true tu pass the test
   i = 42;
   QCOMPARE(i, 42);
}

void MainWindowTest::testCompareAndVerify()
{
   /* QCOMPARE shows a message when the values are not equal. For expression:
    *
    * QCOMPARE(QString("hello"), QString("HELLO"));
    *
    * It shows:
    * FAIL!  : MainWindowTest::testCompareAndVerify() Compared values are not the same
    * Actual   (QString("hello")): "hello"
    * Expected (QString("HELLO")): "HELLO"
    */

   QCOMPARE(QString("hello"), QString("HELLO").toLower());

   /* QVERIFY only shows the condition and says that is false. No more explanations
    *
    * QVERIFY("hello" == "HELLO");
    *
    * QVERIFY2 shows a custom message if the comparision is false. For the expression:
    *
    * QVERIFY2 (4.2 == 4, "Remember that the first value is a float. Be careful with the precison.");
    *
    * It shows:
    * FAIL!  : MainWindowTest::testCompareAndVerify() '4.2 == 4' returned FALSE. (Remember that the first value is a
    * float. Be careful with the precison.)
    */

   auto num1 = 4.0f;
   auto num2 = 4u;

   QVERIFY2(num1 == num2, "Comparing floating point with == or != is unsafe.");
}

void MainWindowTest::testAddUser_data()
{
   QTest::addColumn<QString>("user");
   QTest::addColumn<QString>("pass");

   QTest::newRow("user_valid") << QString("admin1") << "1234";
   QTest::newRow("user_valid") << QString("admin2") << "1234";
}

void MainWindowTest::testAddUser()
{
   QSignalSpy spy(mainWindow, &MainWindow::signalIsLogged);
   QSignalSpy spy2(mainWindow, &MainWindow::signalLogginFailed);

   QFETCH(QString, user);
   QFETCH(QString, pass);

   QTest::keyClicks(mainWindow->ui->leUsername, user);
   QTest::keyClicks(mainWindow->ui->lePassword, pass);

   QTest::mouseClick(mainWindow->ui->pbAddUser, Qt::LeftButton);

   QCOMPARE(spy2.count(), 0);

   spy.wait(3500);

   QCOMPARE(spy.count(), 1);

   const auto firstArgFromTheSignal = spy.takeFirst();

   QVERIFY2(!firstArgFromTheSignal.isEmpty(), "The signal should have at least 1 param!");

   const auto signalParam = firstArgFromTheSignal.constFirst();

   QCOMPARE(signalParam.toString(), user);
}

void MainWindowTest::testBenchamrkedLoop1()
{
   QBENCHMARK
   {
      for (auto i = 0; i < 1000000; ++i)
      {
         auto s = new QString("hola");
         delete s;
      }
   }
}

void MainWindowTest::testBenchamrkedLoop2()
{
   QBENCHMARK
   {
      for (auto i = 0; i < 1000000; ++i)
         QScopedPointer<QString> s(new QString("hola"));
   }
}

void MainWindowTest::testBenchmarkedLoop3()
{
   QBENCHMARK
   {
      for (auto i = 0; i < 1000000; ++i)
         auto s = QSharedPointer<QString>::create("hola");
   }
}

void MainWindowTest::testSelectCellInTable_data()
{
   QTest::addColumn<QString>("user");
   QTest::addColumn<QString>("pass");
   QTest::addColumn<bool>("isValid");

   QTest::newRow("user_valid") << QString("admin1") << "1234" << true;
   QTest::newRow("user_valid") << QString("admin2") << "1234" << true;
}

void MainWindowTest::testSelectCellInTable()
{
   QSignalSpy spy(mainWindow, &MainWindow::signalIsLogged);
   QSignalSpy spy2(mainWindow, &MainWindow::signalLogginFailed);

   QFETCH(QString, user);
   QFETCH(QString, pass);
   QFETCH(bool, isValid);

   QTest::keyClicks(mainWindow->ui->leUsername, user);
   QTest::keyClicks(mainWindow->ui->lePassword, pass);

   QTest::mouseClick(mainWindow->ui->pbAddUser, Qt::LeftButton);

   if (isValid)
   {
      spy.wait(3500);

      QCOMPARE(spy.count(), 1);
      QCOMPARE(spy2.count(), 0);

      const auto firstArgFromTheSignal = spy.takeFirst();

      QVERIFY2(!firstArgFromTheSignal.isEmpty(), "The signal should have at least 1 param!");

      const auto signalParam = firstArgFromTheSignal.constFirst();

      QCOMPARE(signalParam.toString(), user);

      QSignalSpy spy3(mainWindow->ui->tableWidget, &QTableWidget::cellClicked);

      const auto selectedRow = 0;
      const auto selectedColumn = 1;
      const auto x = mainWindow->ui->tableWidget->columnViewportPosition(selectedColumn);
      const auto y = mainWindow->ui->tableWidget->rowViewportPosition(selectedRow);

      QTest::mouseClick(mainWindow->ui->tableWidget->viewport(), Qt::LeftButton, nullptr, QPoint(x, y));

      spy3.wait(500);

      QCOMPARE(spy3.count(), 1);

      auto signalsSent = spy3.takeFirst();

      QVERIFY2(!signalsSent.isEmpty(), "The signal should have at least 1 param!");

      const auto expectedRow = signalsSent.takeFirst();
      const auto expectedColumn = signalsSent.takeFirst();

      QCOMPARE(expectedRow.toInt(), selectedRow);
      QCOMPARE(expectedColumn.toInt(), selectedColumn);
   }
   else
   {
      spy.wait(3500);

      QCOMPARE(spy.count(), 0);
      QCOMPARE(spy2.count(), 1);
   }
}

void MainWindowTest::testEditCellInTable()
{
   QTest::mouseClick(mainWindow->ui->pbAddToList, Qt::LeftButton);

   const auto testWidget = mainWindow->ui->listWidget;
   const auto selectedRow = 0;
   const auto item = testWidget->item(selectedRow);

   QVERIFY2(item, "An item must exist");

   const auto rect = testWidget->visualItemRect(item);

   QTest::mouseClick(testWidget->viewport(), Qt::LeftButton, nullptr, rect.center());
   QTest::mouseDClick(testWidget->viewport(), Qt::LeftButton, nullptr, rect.center());

   QTest::qWait(200);

   QList<QObject *> children = testWidget->viewport()->children();

   for (int i = 0; i < children.size(); ++i)
   {
      if (children.at(i)->inherits("QExpandingLineEdit"))
      {
         const auto lineEdit = qobject_cast<QLineEdit *>(children.at(i));

         QCOMPARE(lineEdit->text(), QString("newUser0"));

         lineEdit->setText("newAdmin");

         QTest::qWait(100);

         lineEdit->close();

         QTest::keyClick(lineEdit, Qt::Key_End);
      }
   }

   QTest::qWait(1000);

   QCOMPARE(testWidget->itemAt(rect.center())->text(), QString("newAdmin"));
}

const static MainWindowTest mainWindowTest;
