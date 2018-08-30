#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    signals:
        void signalIsLogged(const QString &userName);
        void signalLogginFailed();

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

    private slots:
        void slotLogin();
        void onLoginSuccess();
        void addEntryToList();

    friend class MainWindowTest;
};

#endif // MAINWINDOW_H
