#include "mainwindow.h"
#include <QApplication>

#include "widgets/LoggerWidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/styles/light-mode.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = file.readAll();
        a.setStyleSheet(styleSheet);
        file.close();
    } else {
        qDebug() << "Failed to load stylesheet";
    }
    MainWindow w;
    w.show();
    return a.exec();

}
