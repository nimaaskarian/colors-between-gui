#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include "color.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSelect_from_color_triggered();
    void on_actionSelect_to_color_triggered();
    void on_actionEnter_step_count_triggered();

private:
    Ui::MainWindow *ui;
    QVBoxLayout* layout;
    StdColor stdFromColor, stdToColor;
    unsigned int colorsCount = 8;
    QScrollArea *scrollArea;
};
#endif // MAINWINDOW_H
