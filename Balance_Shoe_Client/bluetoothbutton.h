#ifndef BLUETOOTHBUTTON_H
#define BLUETOOTHBUTTON_H

#include <QWidget>
#include <QEvent>

class BluetoothButton : public QWidget{

    Q_OBJECT

    int value;
    QColor color;
    int radius = 50;
    QLine* verical;

    QLine* upper1;
    QLine* upper2;
    QLine* lower1;
    QLine* lower2;

public:

    explicit BluetoothButton(QWidget* parent = nullptr);
    explicit BluetoothButton(int radius, QWidget *parent = nullptr);
    void setRadius(int pp);
    void paintEvent(QPaintEvent *) override;
  //  void mousePressEvent(QMouseEvent *event) override;
public slots:
    void setEnabled(bool state);
signals:
        void pressed();
private:
        bool event(QEvent *event) override;
signals:

public slots:
};

#endif // BLUETOOTHBUTTON_H
