#include "circleprogressbar.h"
#include "pagehandler.h"

#include <QPainter>
#include <QTimer>


CircleProgressBar::CircleProgressBar(QWidget* parent) : CircleProgressBar(50, parent){}

CircleProgressBar::CircleProgressBar(int radius, QWidget* parent) : QWidget(parent), value(0) {
    setRadius(radius);
    tmr2 = new QTimer();
    tmr2->setInterval(100);

    color.setRgb(0x03, 0xC2, 0xFC);
    active = false;
}

void CircleProgressBar::setValue(int value) {
    this->value = value;
    update();
}

void CircleProgressBar::paintEvent(QPaintEvent *) {
    qreal pd = (static_cast<double>(value) / 100) * 360;
    QPainter p(this);
    QPainterPath path;
    QPen pen;

    p.translate(2, 2);
    p.setRenderHint(QPainter::Antialiasing);

    path.moveTo(radius * 0.5,0);
    path.arcTo(QRectF(0, 0, radius - 2, radius - 2), 90, -pd);

    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(color);
    pen.setWidth(radius * 0.04);
    p.strokePath(path, pen);
}

void CircleProgressBar::setFail(){

    setColor(0xFC, 0x03, 0x03);
    tmr2->stop();
    update();
}

void CircleProgressBar::setSucceed(){
    setColor(0x03, 0xFC, 0x52);
    setValue(100);
    tmr2->stop();
    update();
}

void CircleProgressBar::setRadius(int radius){

    this->radius = radius * 2* PageHandler::multiplier;
    setFixedSize(this->radius + static_cast<int>(this->radius * 0.1), this->radius + static_cast<int>(this->radius * 0.1));

    update();
}

void CircleProgressBar::setColor(int r, int g, int b, int a){
    color.setRed(r);
    color.setGreen(g);
    color.setBlue(b);
    color.setAlpha(a);
}

void CircleProgressBar::start(){
    if(active){
        return;
    }
    reserColor();
    tmr2->start();
    active = true;
}

void CircleProgressBar::stop(){
    setColor(0xFC, 0x03, 0xE3);
    update();
    tmr2->stop();
    active = false;
}

void CircleProgressBar::reserColor(){
    setColor(0x03, 0xC2, 0xFC);
}

void CircleProgressBar::mousePressEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event);
    emit pressed();
}

void CircleProgressBar::setIntermidate(){
    connect(tmr2, &QTimer::timeout, this, [=]{
        value++;
        value %= 100;
        update();

    });
}
