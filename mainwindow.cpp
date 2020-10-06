#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QString>
#include <Qt>

// Saving results as globally
double globalNumber;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Binding click operation to buttons
    // Buttons from 0 to 9
    connect(ui->btn0, SIGNAL(clicked()), this, SLOT(clickNumber()));
    connect(ui->btn1, SIGNAL(clicked()), this, SLOT(clickNumber()));
    connect(ui->btn2, SIGNAL(clicked()), this, SLOT(clickNumber()));
    connect(ui->btn3, SIGNAL(clicked()), this, SLOT(clickNumber()));
    connect(ui->btn4, SIGNAL(clicked()), this, SLOT(clickNumber()));
    connect(ui->btn5, SIGNAL(clicked()), this, SLOT(clickNumber()));
    connect(ui->btn6, SIGNAL(clicked()), this, SLOT(clickNumber()));
    connect(ui->btn7, SIGNAL(clicked()), this, SLOT(clickNumber()));
    connect(ui->btn8, SIGNAL(clicked()), this, SLOT(clickNumber()));
    connect(ui->btn9, SIGNAL(clicked()), this, SLOT(clickNumber()));

    // Operation buttons
    // Sign button
    connect(ui->btnSign, SIGNAL(clicked()), this, SLOT(operations()));
    // Percentage button
    connect(ui->btnPercent, SIGNAL(clicked()), this, SLOT(operations()));

    // Arithmetic operations
    // Plus button
    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(arithmeticOperations()));
    // Minus button
    connect(ui->btnMinus, SIGNAL(clicked()), this, SLOT(arithmeticOperations()));
    // Divide button
    connect(ui->btnDivide, SIGNAL(clicked()), this, SLOT(arithmeticOperations()));
    // Multiply button
    connect(ui->btnMultiply, SIGNAL(clicked()), this, SLOT(arithmeticOperations()));

    // Set checkable true for these buttons
    ui->btnPlus->setCheckable(true);
    ui->btnMinus->setCheckable(true);
    ui->btnMultiply->setCheckable(true);
    ui->btnDivide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * This method add new clicked numbers to result label
 */
void MainWindow::clickNumber()
{
    QPushButton *btn = static_cast<QPushButton *>(sender());
    double fullNumber = (ui->resultShow->text() + btn->text()).toDouble();
    QString newResult = QString::number(fullNumber, 'g', 12);

    ui->resultShow->setText(newResult);
}

/*
 * This method add floating point to number
 */
void MainWindow::on_btnDot_clicked()
{
    if (!(ui->resultShow->text().contains('.'))) {
        ui->resultShow->setText(ui->resultShow->text() + '.');
    }
}
/*
 * This method does basic operations between numbers
 */
void MainWindow::operations() {
    QPushButton *btn = static_cast<QPushButton *>(sender());
    QString btnText = btn->text();
    double fullNumber = ui->resultShow->text().toDouble();

    if (btnText == "+/-") {
        fullNumber *= -1;
    } else if (btnText == "%") {
        fullNumber *= 0.01;
    }

    QString newResult = QString::number(fullNumber, 'g', 12);

    ui->resultShow->setText(newResult);
}

/*
 * Arithmetic operations
 */
void MainWindow::arithmeticOperations()
{
    QPushButton *btn = static_cast<QPushButton *>(sender());
    // Save results to this global variable
    globalNumber = ui->resultShow->text().toDouble();
    btn->setChecked(true);
    ui->resultShow->setText("0");
}

/*
 * Clear screen
 */
void MainWindow::on_btnClear_clicked()
{
    ui->btnPlus->setChecked(false);
    ui->btnMinus->setChecked(false);
    ui->btnDivide->setChecked(false);
    ui->btnMultiply->setChecked(false);

    ui->resultShow->setText("0");
}

/*
 * Show result of arithmetic operations
 */
void MainWindow::on_btnEqual_clicked()
{
    QString newResult = QString::number(doOperations(), 'g', 12);
    ui->resultShow->setText(newResult);
}

double MainWindow::doOperations()
{
    double currentNumber = ui->resultShow->text().toDouble();
    double result = 0.0;

    if (ui->btnPlus->isChecked()) {
        result = globalNumber + currentNumber;
        ui->btnPlus->setChecked(false);
    } else if (ui->btnMinus->isChecked()) {
        result = globalNumber - currentNumber;
        ui->btnMinus->setChecked(false);
    } else if (ui->btnMultiply->isChecked()) {
        result = globalNumber * currentNumber;
        ui->btnMultiply->setChecked(false);
    } else if (ui->btnDivide->isChecked() && currentNumber != 0.0) {
        result = globalNumber / currentNumber;
        ui->btnDivide->setChecked(false);
    }

    return result;
}
