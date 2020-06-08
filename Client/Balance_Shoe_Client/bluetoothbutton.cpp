#include "bluetoothbutton.h"
#include "pagehandler.h"

BluetoothButton::BluetoothButton(QWidget *parent) : BluetoothButton(50, parent){

}

BluetoothButton::BluetoothButton(int radius, QWidget *parent) : QWidget(parent){
    verical = new QLine();
    upper1 = new QLine();
    upper2 = new QLine();
    lower1 = new QLine();
    lower2 = new QLine();

    setRadius(radius);
}

void BluetoothButton::setRadius(int radius){
    this->radius = radius * 2 * PageHandler::multiplier;
    setFixedSize(this->radius + static_cast<int>(this->radius * 0.1), 2 * this->radius + static_cast<int>(this->radius * 0.1));

    verical->setP1(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.1 * this->radius)));
    verical->setP2(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.9 * this->radius)));

    upper1->setP1(QPoint(static_cast<int>(0.3 * this->radius), static_cast<int>(0.2 * this->radius)));
    upper1->setP2(QPoint(static_cast<int>(0.7 * this->radius), static_cast<int>(0.7 * this->radius)));
    upper2->setP1(QPoint(static_cast<int>(0.7 * this->radius), static_cast<int>(0.7 * this->radius)));
    upper2->setP2(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.9 * this->radius)));

    lower1->setP1(QPoint(static_cast<int>(0.5 * this->radius), static_cast<int>(0.1 * this->radius)));
    lower1->setP2(QPoint(static_cast<int>(0.7 * this->radius), static_cast<int>(0.3 * this->radius)));
    lower2->setP1(QPoint(static_cast<int>(0.7 * this->radius), static_cast<int>(0.3 * this->radius)));
    lower2->setP2(QPoint(static_cast<int>(0.3 * this->radius), static_cast<int>(0.8 * this->radius)));
    color.setRgb(0x03, 0xC2, 0xFC);
    update();
}

void BluetoothButton::paintEvent(QPaintEvent *event){
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

     p.drawLine(*upper1);
     p.drawLine(*lower1);
     p.drawLine(*upper2);
     p.drawLine(*lower2);
     p.drawLine(*verical);
     p.drawEllipse(0, 0, radius, radius);
     p.strokePath(path, pen);
}

void BluetoothButton::setEnabled(bool state){
    QWidget::setEnabled(state);

    qDebug() << state << " " << isEnabled();
    if(true == isEnabled()){
        color.setRgb(0x03, 0xC2, 0xFC);
    }else{
        color.setRgb(0x82, 0xA5, 0xB0);
    }

    update();
}

bool BluetoothButton::event(QEvent *event)
{
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
