#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "color.h"

void getStepCountFromUser(unsigned int *colorsCount);
void generateNewColors(QVBoxLayout *layout, int colorsCount, StdColor stdFromColor, StdColor stdToColor);
StdColor getStdColorFromUser(QString message="Select color");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scrollArea = new QScrollArea;
    layout = new QVBoxLayout();
    QWidget *widget = new QWidget;

    setCentralWidget(scrollArea);

    stdFromColor = getStdColorFromUser();
    stdToColor = getStdColorFromUser();

    getStepCountFromUser(&colorsCount);
    generateNewColors(layout, colorsCount, stdFromColor, stdToColor);

    widget->setLayout(layout);
    scrollArea->setWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSelect_from_color_triggered()
{
    stdFromColor = getStdColorFromUser();
    generateNewColors(layout, colorsCount, stdFromColor, stdToColor);
}
void MainWindow::on_actionSelect_to_color_triggered()
{
    stdToColor = getStdColorFromUser();
    generateNewColors(layout, colorsCount, stdFromColor, stdToColor);
}
void MainWindow::on_actionEnter_step_count_triggered()
{
    QWidget *widget = new QWidget;
    getStepCountFromUser(&colorsCount);
    generateNewColors(layout, colorsCount, stdFromColor, stdToColor);
    widget->setLayout(layout);
    scrollArea->setWidget(widget);
}
