#ifndef CIRCLEPROGRESSBAR_H
#define CIRCLEPROGRESSBAR_H

#include <QPainter>
#include <QWidget>

class CircleProgressBar : public QWidget{

        Q_OBJECT

    int value;
    QTimer* tmr2;
   QColor color;
    int radius = 50;
    bool active;
        public:
    CircleProgressBar(QWidget *parent = nullptr);
    CircleProgressBar(int radius, QWidget* parent = nullptr);
    void setValue(int pp);
    void paintEvent(QPaintEvent *);
    void start();
    void stop();
    void setIntermidate();
    void setFail();
    void setSucceed();

    void setRadius(int r);

    void setColor(int r, int g, int b, int a = 255);
    void reserColor();
    void mousePressEvent ( QMouseEvent * event );
signals:
    void pressed();
};

#endif // CIRCLEPROGRESSBAR_H
