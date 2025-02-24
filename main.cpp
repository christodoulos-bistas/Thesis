#include "mainwindow.h"
#include <mainwindow.cpp>
#include <QApplication>
#include<QFile>
#include <QShortcut>
#include <QKeySequence>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.showMaximized();

    // Create a shortcut to toggle full-screen mode
    QShortcut *toggleFullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F11), &w);
    QObject::connect(toggleFullScreenShortcut, &QShortcut::activated, [&]() {
        if (w.isFullScreen()) {
            w.showMaximized();
        } else {
            w.showFullScreen();
        }
    });


    return a.exec();
}






























