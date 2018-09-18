#include <QApplication>
#include <QTest>
#include <MainWindowTest.cpp>

int main (int argc, char *argv[])
{
    QApplication app (argc, argv);
    app.setAttribute (Qt::AA_Use96Dpi, true);

    MainWindowTest test;

    QTest::qExec (&test, argc, argv);

    return 0;
}
