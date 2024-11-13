#ifndef CONTOUR_WIDGET_H
#define CONTOUR_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QStackedWidget>
#include <QSlider>


class SharpenWidget:public QWidget
{
    Q_OBJECT
public:
    explicit SharpenWidget(QWidget* parent=nullptr);


private:
    QLabel *label;
    QToolButton *toggleButton;
    QWidget *slidersWidget;
signals:
    void applyFilter();

private slots:
    void handleApplyFilter();

};

#endif
