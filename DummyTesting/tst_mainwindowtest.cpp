#include <QCoreApplication>
#include <QSignalSpy>
#include <QtTest>

// add necessary includes here
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtWidgets/QMainWindow>

class MainWindowTest : public QObject
{
    Q_OBJECT

public:
    MainWindowTest ();
    ~MainWindowTest ();

private slots:
    void initTestCase ();
    void cleanupTestCase ();
    void testCorrectLogin ();
    void testWithWarnings ();
    void testSkipedWithMessage ();
    void testWithExpectedFailures ();
    void testFailsOnWindows ();
    void testCompareAndVerify ();

private:
    MainWindow mainWindow;
};

MainWindowTest::MainWindowTest () {}

MainWindowTest::~MainWindowTest () {}

void MainWindowTest::initTestCase () {}

void MainWindowTest::cleanupTestCase () {}

void MainWindowTest::testWithWarnings ()
{
    QWARN("Test is empty. Fill it with something!");
}

void MainWindowTest::testSkipedWithMessage ()
{
    QSKIP ("Test skiped voluntary.");

    // The following content won't be executed
    QCOMPARE(0.0, 1.0);
}

void MainWindowTest::testWithExpectedFailures ()
{
    QEXPECT_FAIL("", "First QVERIFY or QCOMPARE of the test won't fail the test. We can choose Continue or Abort.", TestFailMode::Continue);

    auto i = 0;
    QCOMPARE(i, 42);

    // If we add more QCOMPARE or QVERIFY they must be true tu pass the test
    i = 42;
    QCOMPARE(i, 42);
}

void MainWindowTest::testFailsOnWindows ()
{
    #ifdef Q_OS_WIN
    QFAIL("Test not ported to Windows.")
    #else
    QCOMPARE(0,0);
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

    QCOMPARE("hello", QString("HELLO").toLower());

    // QVERIFY only shows the condition and says that is false. No more explanations
    // QVERIFY("hello" == "HELLO");

    /* QVERIFY2 shows a custom message if the comparision is false. For the expression:
     *
     * QVERIFY2 (4.2 == 4, "Remember that the first value is a float. Be careful with the precison.");
     *
     * It shows:
     * FAIL!  : MainWindowTest::testCompareAndVerify() '4.2 == 4' returned FALSE. (Remember that the first value is a float. Be careful with the precison.)
     */

    auto num1 = 4.0f;
    auto num2 = 4u;

    QVERIFY2 (num1 == num2, "Remember that the first value is a float. Be careful with the precison.");
}

void MainWindowTest::testCorrectLogin ()
{
    const char *user = "admin";

    QSignalSpy spy (&mainWindow, &MainWindow::signalIsLogged);
    QSignalSpy spy2 (&mainWindow, &MainWindow::signalLogginFailed);

    QTest::keyClicks (mainWindow.ui->leUsername, user);
    QTest::keyClicks (mainWindow.ui->lePassword, "1234");

    QTest::mouseClick (mainWindow.ui->pbLogin, Qt::LeftButton);

    // QCOMPARE(mainWindow.ui->leUsername->text(), QString("hello world"));
    QCOMPARE (spy2.count (), 0);
    QCOMPARE (spy.count (), 1);

    const auto firstArgFromTheSignal = spy.takeFirst();

    QVERIFY2 (!firstArgFromTheSignal.isEmpty(), "The signal should have at least 1 param!");

    const auto signalParam = firstArgFromTheSignal.constFirst();

    QCOMPARE (signalParam, user);
}

QTEST_MAIN (MainWindowTest)

#include "tst_mainwindowtest.moc"
