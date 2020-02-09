#ifndef OFFICON_H
#define OFFICON_H

#include <QWidget>

class OffIcon : public QWidget
{    Q_OBJECT

     int value;
     QColor color;
     int radius = 50;
     bool active;

 public:

     OffIcon(QWidget *parent = nullptr);
     OffIcon(int radius, QWidget* parent = nullptr);
     void setRadius(int pp);
     void paintEvent(QPaintEvent *);

      void on();
       void off();
        bool isActive();
 signals:
         void pressed();
 private:
         void mousePressEvent(QMouseEvent *event);
};

#endif // OFFICON_H
