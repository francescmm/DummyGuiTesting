#include <QApplication>
#include <QTest>
#include <MainWindowTest.cpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    QString outputFile{ "testOutput.txt" };

    QStringList arguments;
    for (auto i = 0; i < argc; i++)
    {
        arguments << argv[i];
    }
    arguments << "-o" << QString{ outputFile + ",txt" } << "-v2";

    MainWindowTest test;

    QStringList failedTests;

    if (QTest::qExec(&test, arguments))
        failedTests << test.objectName();

    if (!failedTests.isEmpty())
    {
        qWarning() << "#######################################";
        qWarning() << "TEST FAILURES DETECTED:";

        for (auto f : failedTests)
            qWarning() << "  - " << f;

        qWarning() << "Results written to: " << outputFile;
        qWarning() << "#######################################";
    }

    return failedTests.count();
}
