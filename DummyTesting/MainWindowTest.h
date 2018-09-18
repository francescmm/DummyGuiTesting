#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QObject>

class MainWindow;

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

    void testValid();
    void testValid_data();

    void testWithWarnings ();
    void testSkipedWithMessage ();
    void testWithExpectedFailures ();
    void testFailsOnWindows ();
    void testCompareAndVerify ();
    void testBenchamrkedLoop1 ();
    void testBenchamrkedLoop2 ();
    void testBenchmarkedLoop3 ();

    void testSelectCellInTable_data();
    void testSelectCellInTable ();

    void testEditCellInTable();

  private:
    MainWindow *mainWindow = nullptr;
};

#endif // MAINWINDOWTEST_H
