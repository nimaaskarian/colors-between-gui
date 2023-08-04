#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QInputDialog>
#include <QScrollArea>
#include "color.h"
#include "mainwindow.h"

void getStepCountFromUser(unsigned int *colorsCount);
void generateNewColors(QVBoxLayout *layout, int colorsCount, StdColor stdFromColor, StdColor stdToColor);
StdColor getStdColorFromUser(QString message="Select color");

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // QWidget *widget = new QWidget;
    MainWindow window;
    // // Create the main window
    // QScrollArea *scrollArea = new QScrollArea;


    // StdColor stdFromColor = getStdColorFromUser();
    // StdColor stdToColor = getStdColorFromUser();

    // unsigned int colorsCount = 8;
    // getStepCountFromUser(colorsCount);
    // generateNewColors(&layout, colorsCount, stdFromColor, stdToColor);

    // widget->setLayout(&layout);
    // scrollArea->setWidget(widget);
    // window.setCentralWidget(scrollArea);
    window.show();
    return app.exec();
}

StdColor getStdColorFromUser(QString message)
{
    QColor qColor = QColorDialog::getColor(Qt::white, nullptr, message);
    StdColor srgb = colorToStdColor(colorFromQColor(qColor));
    return srgb;
}

void getStepCountFromUser(unsigned int *colorsCount)
{
    bool ok;
    unsigned int input = QInputDialog::getInt(nullptr, "Enter a Number", "Step Count:", (*colorsCount), 0, 255, 1, &ok);
    if (ok)
        *colorsCount = input;
}

void generateNewColors(QVBoxLayout *layout, int colorsCount, StdColor stdFromColor, StdColor stdToColor)
{

    StdColor white;
    white.r = 1;
    white.g = 1;
    white.b = 1;

    StdColor black = colorToStdColor(colorBlack());


    colorsCount++;
    QLayoutItem * item;
    while ( (item = layout->takeAt(0)) != NULL ) {
        delete item->widget();
        delete item;
    }
    StdColor colorDifference;
    colorDifference.r = (stdToColor.r - stdFromColor.r)/colorsCount;
    colorDifference.g = (stdToColor.g - stdFromColor.g)/colorsCount;
    colorDifference.b = (stdToColor.b - stdFromColor.b)/colorsCount;

    // Create labels using the hex codes
    for (int i = 0; i < colorsCount+1; ++i) {
     StdColor currentAddition = multipleStdColor(colorDifference ,i);
        StdColor srgb = addStdColors(stdFromColor,  currentAddition);
        auto hexCode = stdColorQString(srgb);
        QLabel* label = new QLabel;
        label->setAutoFillBackground(true);
        label->setFixedHeight(20);

        // Set the background color using the hex code
        auto lBackground = relativeLuminanceStdColor(srgb);
        auto lBlack = relativeLuminanceStdColor(black);
        auto lWhite = relativeLuminanceStdColor(white);
        QPalette palette = label->palette();
        palette.setColor(QPalette::Window, QColor(hexCode));
        if (contrastRatio(lBackground, lBlack) > contrastRatio(lBackground, lWhite)) {
            palette.setColor(QPalette::WindowText, QColor(stdColorQString(black)));
        } else
            palette.setColor(QPalette::WindowText, QColor(stdColorQString(white)));
        label->setText(hexCode);
        label->setPalette(palette);

        layout->addWidget(label);
        // window.layout()->addWidget(label);
        // window.layout()->addItem(&label);

    }
}
