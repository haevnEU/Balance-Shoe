#ifndef ARROWBUTTON_H
#define ARROWBUTTON_H

#include <QWidget>

#include <QDebug>
#include <qpushbutton.h>
enum ArrowButtonDirection{
    Up, Right, Left, Down, Cross, Accept
};

class ArrowButton : public QWidget{
    Q_OBJECT


    ArrowButtonDirection dir;

    int value;
    QColor color;
    int radius = 50;
    QLine* verical;

    QLine* upper;
    QLine* lower;

public:

    explicit ArrowButton(ArrowButtonDirection dir, QWidget* parent = nullptr);
    explicit ArrowButton(ArrowButtonDirection dir, int radius, QWidget *parent = nullptr);
    void setRadius(int pp);
    void paintEvent(QPaintEvent *) override;
public slots:
    void setEnabled(bool state);
signals:
        void pressed();
private:
        bool event(QEvent *event) override;

};

#endif // ARROWBUTTON_H
