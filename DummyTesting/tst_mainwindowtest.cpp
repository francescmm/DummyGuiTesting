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
    void testSkipedWithMessage ();

  private:
    MainWindow mainWindow;
};

MainWindowTest::MainWindowTest () {}

MainWindowTest::~MainWindowTest () {}

void MainWindowTest::initTestCase () {}

void MainWindowTest::cleanupTestCase () {}

void MainWindowTest::testCorrectLogin ()
{
    QSignalSpy spy (&mainWindow, &MainWindow::signalIsLogged);
    QSignalSpy spy2 (&mainWindow, &MainWindow::signalLogginFailed);

    QTest::keyClicks (mainWindow.ui->leUsername, "admin");
    QTest::keyClicks (mainWindow.ui->lePassword, "admin");

    QTest::mouseClick (mainWindow.ui->pbLogin, Qt::LeftButton);

    // QCOMPARE(mainWindow.ui->leUsername->text(), QString("hello world"));
    QCOMPARE (spy2.count (), 0);
    QCOMPARE (spy.count (), 1);
}

void MainWindowTest::testSkipedWithMessage ()
{
    QSKIP ("Test skiped voluntary.");

    // The following content won't be executed
}

QTEST_MAIN (MainWindowTest)

#include "tst_mainwindowtest.moc"
