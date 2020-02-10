#include "pagehandler.h"
#include "settingsbutton.h"



SettingsButton::SettingsButton(QWidget *parent) : SettingsButton(50, parent){}

SettingsButton::SettingsButton(int radius, QWidget *parent) : QWidget(parent){
    verical1 = new QLine();
    circle1 = new Circle();
    verical2 = new QLine();
    circle2 = new Circle();
    verical3 = new QLine();
    circle3 = new Circle();
    setRadius(radius);
    color.setRgb(0x03, 0xC2, 0xFC);
    update();
}


void SettingsButton::setEnabled(bool state){
    QWidget::setEnabled(state);

    if(true == isEnabled()){
        color.setRgb(0x03, 0xC2, 0xFC);
    }else{
        color.setRgb(0x82, 0xA5, 0xB0);
    }

    update();
}
#include<QEvent>
#include <qpainter.h>
bool SettingsButton::event(QEvent *event){
    /*
     *   = 194,
        TouchUpdate = 195,
        TouchEnd = 196,
     */
    switch(event->type()){
    case QEvent::Type::MouseButtonPress:
    case QEvent::Type::TouchBegin:
        if(isEnabled()){
            emit pressed();
        }
        break;
    case QEvent::Type::MouseButtonRelease:
    case QEvent::Type::TouchEnd:
        break;
    case QEvent::Type::MouseButtonDblClick:
        break;
    default:break;

    }

    return QWidget::event(event);
}

void SettingsButton::setRadius(int radius){

    this->radius = radius * 2 * PageHandler::multiplier;
    setFixedSize(this->radius + static_cast<int>(this->radius * 0.1), this->radius + static_cast<int>(this->radius * 0.1));

    verical1->setP1(QPoint(static_cast<int>(0.25 * this->radius), static_cast<int>(0.25 * this->radius)));
    verical1->setP2(QPoint(static_cast<int>(0.25 * this->radius), static_cast<int>(0.75 * this->radius)));
    circle1->radius = static_cast<int>(0.05 * this->radius);
    circle1->center = QPoint(static_cast<int>(0.25 * this->radius), static_cast<int>(0.5 * this->radius));

    verical2->setP1(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.25 * this->radius)));
    verical2->setP2(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.75 * this->radius)));
    circle2->radius = static_cast<int>(0.05 * this->radius);
    circle2->center = QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.35 * this->radius));

    verical3->setP1(QPoint(static_cast<int>(0.75 * this->radius), static_cast<int>(0.25 * this->radius)));
    verical3->setP2(QPoint(static_cast<int>(0.75 * this->radius), static_cast<int>(0.75 * this->radius)));
    circle3->radius = static_cast<int>(0.05 * this->radius);
    circle3->center = QPoint(static_cast<int>(0.75 * this->radius), static_cast<int>((1-0.35) * this->radius));

    update();
}

void SettingsButton::paintEvent(QPaintEvent* event){
    QWidget::paintEvent(event);
    QPainter p(this);
     QPainterPath path;
     QPen pen;
     p.translate(2, 2);
     p.setRenderHint(QPainter::Antialiasing);

     pen.setCapStyle(Qt::FlatCap);
     pen.setColor(color);
     pen.setWidth(static_cast<int>(radius * 0.04));
     p.setPen(pen);

     p.drawLine(*verical1);
     p.drawLine(*verical2);
     p.drawLine(*verical3);
     p.setBrush(QBrush(color));
     //p.drawEllipse(0, 0, radius, radius);
     p.drawEllipse(circle1->center, circle1->radius, circle1->radius);
     p.drawEllipse(circle2->center, circle2->radius, circle2->radius);
     p.drawEllipse(circle3->center, circle3->radius, circle3->radius);
     p.setBrush(QBrush(Qt::transparent));
     p.drawEllipse(0, 0, radius, radius);
     //p.drawArc(0, radius, radius, radius,0 , -16 * 360);
     p.strokePath(path, pen);
}
