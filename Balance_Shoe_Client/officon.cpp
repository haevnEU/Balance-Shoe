#include "officon.h"
#include "pagehandler.h"

#include <QPainter>

OffIcon::OffIcon(QWidget* parent) : OffIcon(50, parent){}

OffIcon::OffIcon(int radius, QWidget* parent) : QWidget(parent), value(0) {
    setRadius(radius);
    color.setRgb(0x03, 0xC2, 0xFC);
    active = false;
    off();
}

void OffIcon::setRadius(int radius) {

    this->radius = radius * 2 * PageHandler::multiplier;
    setFixedSize(this->radius + static_cast<int>(this->radius * 0.0), this->radius + static_cast<int>(this->radius * 0.0));
    update();
}

void OffIcon::paintEvent(QPaintEvent *) {
   QPainter p(this);
    QPainterPath path;
    QPen pen;
    QLine line;
    int radius = this->radius * 0.9;
    line.setLine(radius * 0.5, -radius *0.5, radius * 0.5, radius * 0.75);
    p.translate(2, 2);
    p.setRenderHint(QPainter::Antialiasing);
    //path.arcTo(QRectF(0, radius* 0.3, radius, radius), 60 * 16, -300 * 16);
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(color);
    pen.setWidth(4);
    p.setPen(pen);
    p.drawLine(line);
    p.drawArc(0, radius * 0.1, radius, radius, 60 * 16 , -16 * 300);
    p.strokePath(path, pen);
}

void OffIcon::on(){
    color.setRgb(54, 184, 50);
    update();
    active = true;
}

void OffIcon::off(){
    color.setRgb(184, 50, 50);
    update();
    active = false;
}

bool OffIcon::isActive(){
    return active;
}

void OffIcon::mousePressEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event);
    active = !active;
    if(active){
        on();
    }else {
        off();
    }
    emit pressed();
}
