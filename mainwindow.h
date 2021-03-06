#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void clickNumber();
    void on_btnDot_clicked();
    void operations();
    void on_btnClear_clicked();
    void on_btnEqual_clicked();
    void arithmeticOperations();
    double doOperations();
};

#endif // MAINWINDOW_H
