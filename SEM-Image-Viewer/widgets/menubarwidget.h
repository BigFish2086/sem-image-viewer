#ifndef MENUBARWIDGET_H
#define MENUBARWIDGET_H

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QMainWindow>
#include <QObject>
#include <QImage>
#include <QFileDialog>
#include <iostream>
#include <thread>
#include <vector>
#include <QMetaObject>
#include <QThread>

#include "../core/engines/Workspace.h"
#include "../core/data/Image.h"
#include "../core/data/ImageFormat.h"

#include<iostream>

using namespace std;



class MenuBarWidget : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBarWidget(QWidget *parent = nullptr);

private:
    void fileMenu();
    void editMenu();
    void viewMenu();
    void optionsMenu();

signals:
    void showLeftSidebarClicked(bool isChecked);
    void showRightSidebarClicked(bool isChecked);
    void showLoggerClicked(bool isChecked);
    void showImageClicked(bool isChecked);
    void exportProgressUpdated();
    void exportStarted(int maxIterations);
    void exportFinished();
private slots:
    void exportImages(QString format);
    void exportSelectedImage(QString format);
    // void exportAll();

};

#endif // MENUBARWIDGET_H
