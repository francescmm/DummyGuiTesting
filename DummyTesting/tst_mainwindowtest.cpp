#include <QtTest>
#include <QSignalSpy>
#include <QCoreApplication>

// add necessary includes here
#include <QtWidgets/QMainWindow>
#include "MainWindow.h"
#include "ui_MainWindow.h"

class MainWindowTest : public QObject
{
    Q_OBJECT

    public:
        MainWindowTest();
        ~MainWindowTest();

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void test_case1();

    private:
        MainWindow mainWindow;
};

MainWindowTest::MainWindowTest()
{

}

MainWindowTest::~MainWindowTest()
{

}

void MainWindowTest::initTestCase()
{

}

void MainWindowTest::cleanupTestCase()
{

}

void MainWindowTest::test_case1()
{
    QSignalSpy spy(&mainWindow, &MainWindow::signalIsLogged);
    QSignalSpy spy2(&mainWindow, &MainWindow::signalLogginFailed);

    QTest::keyClicks(mainWindow.ui->leUsername, "admin");
    QTest::keyClicks(mainWindow.ui->lePassword, "admin");

    QTest::mouseClick(mainWindow.ui->pbLogin, Qt::LeftButton);

    //QCOMPARE(mainWindow.ui->leUsername->text(), QString("hello world"));
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy.count(), 1);
}

QTEST_MAIN(MainWindowTest)

#include "tst_mainwindowtest.moc"
