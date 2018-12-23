#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProgressBar>
#include <QGamepadManager>
#include <QGamepad>

void MainWindow::axisChanged(QProgressBar &brogressBar, double value)
{
    int delta = (brogressBar.maximum() - brogressBar.minimum()) / 2;

    brogressBar.setValue(brogressBar.minimum() + (static_cast<int>(value) * delta));
}

void MainWindow::axisLeftXChanged(double val)
{
    axisChanged(*ui->pbAxisLeftXChanged, val);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    auto padsId = QGamepadManager::instance()->connectedGamepads();

    if (!padsId.isEmpty())
    {
        QGamepad * pad = new QGamepad(padsId[0], this);

        QObject::connect(pad, SIGNAL(axisLeftXChanged), this, SLOT(axisLeftXChanged));
    }

    ui->setupUi(this);

    ui->lbPadCounter->setNum(padsId.size());
}

MainWindow::~MainWindow()
{
    delete ui;
}
