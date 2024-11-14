#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSplitter>
#include "widgets/bottommiddlewidget.h"
#include "widgets/leftsidebarwidget.h"
#include "widgets/rightsidebarwidget.h"
#include "widgets/topmiddlewidget.h"
#include "widgets/menubarwidget.h"
#include "widgets/WidgetViewController.h"

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIcon>

#include "widgets/image_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onShowLeftSidebarClicked(bool isChecked);
    void onShowRightSidebarClicked(bool isChecked);
    void onShowLoggerClicked(bool isChecked);
    void onShowImageClicked(bool isChecked);

private slots:

private:
    Ui::MainWindow *ui;
    ImageWidget *imageWidget;  // Member variable for the custom widget

    WidgetViewController *viewController;
    LeftSidebarWidget *leftSidebarWidget;
    RightSidebarWidget *rightSidebarWidget;
    TopMiddleWidget *topMiddleWidget;
    BottomMiddleWidget *bottomMiddleWidget;
    QSplitter *middleSplitter;
    QSplitter *mainSplitter;
    MenuBarWidget *menuBarWidget;

    // signals:


};

#endif // MAINWINDOW_H
