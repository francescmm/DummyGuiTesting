#include <QCoreApplication>
#include <QSignalSpy>
#include <QtTest>
#include <QLineEdit>

// Additional includes
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtWidgets/QMainWindow>

class MainWindowTest : public QObject
{
    Q_OBJECT

  public:
    MainWindowTest ()  = default;
    ~MainWindowTest () = default;

  private slots:
    void initTestCase ();
    void cleanupTestCase ();
    void init () { }
    void cleanup ();

    void testAddUser_data();
    void testAddUser ();

    void testWithWarnings ();
    void testSkipedWithMessage ();
    void testWithExpectedFailures ();
    void testFailsOnWindows ();
    void testCompareAndVerify ();
    void testBenchamrkedLoop1 ();
    void testBenchamrkedLoop2 ();
    void testBenchmarkedLoop3 ();
    void testSelectCellInTable ();
    void testEditCellInTable();

  private:
    MainWindow *mainWindow = nullptr;
};

void MainWindowTest::initTestCase ()
{
    mainWindow = new MainWindow ();
    mainWindow->show ();

    QVERIFY (mainWindow->isVisible ());
}

void MainWindowTest::cleanupTestCase ()
{
    mainWindow->close ();

    QVERIFY (!mainWindow->isVisible ());

    delete mainWindow;
    mainWindow = nullptr;
}

void MainWindowTest::cleanup ()
{
    for (auto row = mainWindow->ui->tableWidget->rowCount() - 1; row >= 0; --row)
    {
        for (auto col = 0; col < mainWindow->ui->tableWidget->columnCount(); ++col)
            delete mainWindow->ui->tableWidget->cellWidget(row, col);

        mainWindow->ui->tableWidget->removeRow(row);
    }

    mainWindow->ui->tableWidget->clearContents();

    for (auto row = mainWindow->ui->listWidget->count() - 1; row >= 0; --row)
    {
        auto item = mainWindow->ui->listWidget->item(row);
        delete mainWindow->ui->listWidget->itemWidget(item);

        delete item;
    }
}

void MainWindowTest::testWithWarnings ()
{
    QWARN ("Test is empty. Fill it with something!");
}

void MainWindowTest::testSkipedWithMessage ()
{
    QSKIP ("Test skiped voluntary.");

    // The following content won't be executed
    QCOMPARE (0.0, 1.0);
}

void MainWindowTest::testWithExpectedFailures ()
{
    QEXPECT_FAIL ("", "First QVERIFY or QCOMPARE of the test won't fail the test. We can choose Continue or Abort.", TestFailMode::Continue);

    auto i = 0;
    QCOMPARE (i, 42);

    // If we add more QCOMPARE or QVERIFY they must be true tu pass the test
    i = 42;
    QCOMPARE (i, 42);
}

void MainWindowTest::testFailsOnWindows ()
{
#ifdef Q_OS_WIN
    QFAIL ("Test not ported to Windows.");
#else
    QCOMPARE (0, 0);
#endif
}

void MainWindowTest::testCompareAndVerify ()
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

    QCOMPARE ("hello", QString ("HELLO").toLower ());

    /* QVERIFY only shows the condition and says that is false. No more explanations
     *
     * QVERIFY("hello" == "HELLO");
     *
     * QVERIFY2 shows a custom message if the comparision is false. For the expression:
     *
     * QVERIFY2 (4.2 == 4, "Remember that the first value is a float. Be careful with the precison.");
     *
     * It shows:
     * FAIL!  : MainWindowTest::testCompareAndVerify() '4.2 == 4' returned FALSE. (Remember that the first value is a float. Be careful with the
     * precison.)
     */

    auto num1 = 4.0f;
    auto num2 = 4u;

    QVERIFY2 (num1 == num2, "Remember that the first value is a float. Be careful with the precison.");
}

void MainWindowTest::testAddUser_data()
{
    QTest::addColumn<QString>("user");
    QTest::addColumn<QString>("pass");

    QTest::newRow("user_valid") << QString("admin%1").arg(QString::number(mainWindow->ui->tableWidget->rowCount())) << "1234";
}

void MainWindowTest::testAddUser ()
{
    QSignalSpy spy (mainWindow, &MainWindow::signalIsLogged);
    QSignalSpy spy2 (mainWindow, &MainWindow::signalLogginFailed);

    QFETCH(QString, user);
    QFETCH(QString, pass);

    QTest::keyClicks (mainWindow->ui->leUsername, user);
    QTest::keyClicks (mainWindow->ui->lePassword, pass);

    QTest::mouseClick (mainWindow->ui->pbAddUser, Qt::LeftButton);

    QCOMPARE (spy2.count (), 0);

    spy.wait (3500);

    QCOMPARE (spy.count (), 1);

    const auto firstArgFromTheSignal = spy.takeFirst ();

    QVERIFY2 (!firstArgFromTheSignal.isEmpty (), "The signal should have at least 1 param!");

    const auto signalParam = firstArgFromTheSignal.constFirst ();

    QCOMPARE (signalParam, user);
}

void MainWindowTest::testBenchamrkedLoop1 ()
{
    QBENCHMARK
    {
        for (auto i = 0; i < 1000000; ++i)
        {
            QString *s = new QString ("hola");
            delete s;
        }
    }
}

void MainWindowTest::testBenchamrkedLoop2 ()
{
    QBENCHMARK
    {
        for (auto i = 0; i < 1000000; ++i)
            QScopedPointer<QString> s (new QString ("hola"));
    }
}

void MainWindowTest::testBenchmarkedLoop3 ()
{
    QBENCHMARK
    {
        for (auto i = 0; i < 1000000; ++i)
            auto s = QSharedPointer<QString>::create ("hola");
    }
}

void MainWindowTest::testSelectCellInTable()
{
    testAddUser();

    QSignalSpy spy2 (mainWindow->ui->tableWidget, &QTableWidget::cellClicked);

    auto selectedRow = 0;
    auto selectedColumn = 1;

    int x = mainWindow->ui->tableWidget->columnViewportPosition(selectedColumn);
    int y = mainWindow->ui->tableWidget->rowViewportPosition(selectedRow);

    QTest::mouseClick(mainWindow->ui->tableWidget->viewport(), Qt::LeftButton, nullptr, QPoint(x, y));

    spy2.wait(500);

    QCOMPARE(spy2.count(), 1);

    auto signalsSent = spy2.takeFirst ();

    QVERIFY2 (!signalsSent.isEmpty (), "The signal should have at least 1 param!");

    const auto expectedRow = signalsSent.takeFirst();
    const auto expectedColumn = signalsSent.takeFirst();

    QCOMPARE(expectedRow, selectedRow);
    QCOMPARE(expectedColumn, selectedColumn);
}

void MainWindowTest::testEditCellInTable()
{
    QTest::mouseClick (mainWindow->ui->pbAddToList, Qt::LeftButton);

    auto testWidget = mainWindow->ui->listWidget;
    auto selectedRow = 0;
    auto item = testWidget->item(selectedRow);

    QVERIFY2(item, "An item must exist");

    auto rect = testWidget->visualItemRect(item);

    QTest::mouseClick(testWidget->viewport(), Qt::LeftButton, nullptr, rect.center());
    QTest::mouseDClick(testWidget->viewport(), Qt::LeftButton, nullptr, rect.center());
    QTest::qWait(100);

    QList<QObject *> children = testWidget->viewport()->children();

    for (int i = 0; i < children.size(); ++i)
    {
        if (children.at(i)->inherits("QExpandingLineEdit"))
        {
            auto lineEdit = qobject_cast<QLineEdit*>(children.at(i));

            QCOMPARE(lineEdit->text(), "newUser0");

            lineEdit->setText("newAdmin");

            QTest::qWait(100);

            lineEdit->close();

            QTest::keyClick(lineEdit, Qt::Key_End);
        }
    }

    QTest::qWait(1000);

    QCOMPARE(mainWindow->ui->listWidget->itemAt(rect.center())->text(), "newAdmin");
}

QTEST_MAIN (MainWindowTest)

#include "tst_mainwindowtest.moc"
