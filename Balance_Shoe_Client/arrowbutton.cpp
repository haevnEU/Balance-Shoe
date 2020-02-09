#include "arrowbutton.h"

#include <QPainter>

#include<QDebug>

ArrowButton::ArrowButton(ArrowButtonDirection dir, QWidget *parent) : ArrowButton(dir, 50, parent){}

ArrowButton::ArrowButton(ArrowButtonDirection dir, int radius, QWidget *parent) : QWidget(parent){
    this->dir = dir;
    verical = new QLine();
    lower = new QLine();
    upper = new QLine(); setRadius(radius);
    color.setRgb(0x03, 0xC2, 0xFC);
    update();
}


void ArrowButton::setEnabled(bool state){
    QWidget::setEnabled(state);

    qDebug() << state << " " << isEnabled();
    if(true == isEnabled()){
        color.setRgb(0x03, 0xC2, 0xFC);
    }else{
        color.setRgb(0x82, 0xA5, 0xB0);
    }

    update();
}
#include<QEvent>
bool ArrowButton::event(QEvent *event){
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

void ArrowButton::setRadius(int radius){
#ifdef Q_OS_ANDROID
    this->radius = radius * 4;
#else
    this->radius = radius * 2;
#endif

    setMinimumSize(2 * this->radius + 10, 2 * this->radius + 10);
    setMaximumSize(2 * this->radius + 10, 2 * this->radius + 10);
    switch(dir){
    case ArrowButtonDirection::Right:
        verical->setP1(QPoint(static_cast<int>(0.25 * this->radius), static_cast<int>(0.5 * this->radius)));
        verical->setP2(QPoint(static_cast<int>(0.75 * this->radius), static_cast<int>(0.5 * this->radius)));

        upper->setP1(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.35 * this->radius)));
        upper->setP2(QPoint(static_cast<int>(0.75 * this->radius), static_cast<int>(0.5 * this->radius)));

        lower->setP1(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>((1 - 0.35) * this->radius)));
        lower->setP2(QPoint(static_cast<int>(0.75 * this->radius), static_cast<int>(0.5 * this->radius)));
        break;

    case ArrowButtonDirection::Left:
        verical->setP1(QPoint(static_cast<int>(0.25 * this->radius), static_cast<int>(0.5 * this->radius)));
        verical->setP2(QPoint(static_cast<int>(0.75 * this->radius), static_cast<int>(0.5 * this->radius)));

        upper->setP1(QPoint(static_cast<int>(0.25 * this->radius), static_cast<int>(0.5 * this->radius)));
        upper->setP2(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.35 * this->radius)));

        lower->setP1(QPoint(static_cast<int>(0.25 * this->radius), static_cast<int>(0.5 * this->radius)));
        lower->setP2(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>((1 - 0.35) * this->radius)));

        break;
    case ArrowButtonDirection::Up:
        break;
    case ArrowButtonDirection::Down:
        break;


    case ArrowButtonDirection::Accept:
        verical->setP1(QPoint(static_cast<int>(0 * this->radius), static_cast<int>(0 * this->radius)));
        verical->setP2(QPoint(static_cast<int>(0 * this->radius), static_cast<int>(0 * this->radius)));

        upper->setP1(QPoint(static_cast<int>(0.25 * this->radius), static_cast<int>(0.5 * this->radius)));
        upper->setP2(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.75 * this->radius)));

        lower->setP1(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.75 * this->radius)));
        lower->setP2(QPoint(static_cast<int>(0.75 * this->radius), static_cast<int>(0.25 * this->radius)));
        break;
    case ArrowButtonDirection::Cross:
        verical->setP1(QPoint(static_cast<int>(0 * this->radius), static_cast<int>(0 * this->radius)));
        verical->setP2(QPoint(static_cast<int>(0 * this->radius), static_cast<int>(0 * this->radius)));

        upper->setP1(QPoint(static_cast<int>(0.25 * this->radius), static_cast<int>(0.25 * this->radius)));
        upper->setP2(QPoint(static_cast<int>(0.75 * this->radius), static_cast<int>(0.75 * this->radius)));

        lower->setP1(QPoint(static_cast<int>(0.75 * this->radius), static_cast<int>(0.25 * this->radius)));
        lower->setP2(QPoint(static_cast<int>(0.25 * this->radius), static_cast<int>(0.75 * this->radius)));
        break;
    }

    update();

}

void ArrowButton::paintEvent(QPaintEvent* event){
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

     p.drawLine(*upper);
     p.drawLine(*lower);
     p.drawLine(*verical);
     p.drawEllipse(0, 0, radius, radius);
    // p.drawArc(0, radius, radius, radius,0 , -16 * 360);
     p.strokePath(path, pen);
}
/*
void ArrowButton::mousePressEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event);

    qDebug() << isEnabled();
    if(isEnabled()){
        emit pressed();
    }
}*/
