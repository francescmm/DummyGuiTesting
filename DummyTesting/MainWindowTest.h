#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include "BaseTest.h"

class MainWindow;

class MainWindowTest : public BaseTest
{
   Q_OBJECT
   public:
   MainWindowTest();
   MainWindowTest(const MainWindowTest &mw);
   MainWindowTest &operator=(const MainWindowTest &mv);
   ~MainWindowTest() override = default;

   private slots:
   void initTestCase() override;
   void cleanupTestCase() override;
   void init() override {}
   void cleanup() override;

   void testAddUser_data();
   void testAddUser();

   void testValid();
   void testValid_data();

   void testWithWarnings();
   void testSkipedWithMessage();
   void testWithExpectedFailures();
   void testCompareAndVerify();
   void testBenchamrkedLoop1();
   void testBenchamrkedLoop2();
   void testBenchmarkedLoop3();

   void testSelectCellInTable_data();
   void testSelectCellInTable();

   void testEditCellInTable();

   private:
   MainWindow *mainWindow = nullptr;
};

#endif // MAINWINDOWTEST_H
