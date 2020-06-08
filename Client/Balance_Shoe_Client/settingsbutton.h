#ifndef SETTINGSBUTTON_H
#define SETTINGSBUTTON_H

#include <QWidget>

class SettingsButton : public QWidget
{
    Q_OBJECT

    struct Circle{
        QPoint center;
        int radius;
    };
    int value;
    QColor color;
    int radius = 50;
    QLine* verical1;
    Circle* circle1;
    QLine* verical2;
    Circle* circle2;
    QLine* verical3;
    Circle* circle3;

public:

    explicit SettingsButton(QWidget* parent = nullptr);
    explicit SettingsButton(int radius, QWidget *parent = nullptr);
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
#endif // SETTINGSBUTTON_H
