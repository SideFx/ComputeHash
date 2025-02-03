#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (QLocale::system().name().contains("en_")) {
        QTranslator translator;
        if (translator.load("ComputeHash_en_US.qm")) a.installTranslator(&translator);
    }
    MainWindow w;
    w.show();
    return a.exec();
}
