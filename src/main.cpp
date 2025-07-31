// src/main.cpp
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("MdEditor");
    w.resize(1200, 900);
    w.show();

    return app.exec();
}