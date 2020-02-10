#include "connectpage.h"
#include "pagehandler.h"

#include <QGridLayout>
#include <QPainter>
#include <qlabel.h>
#include <qtimer.h>
#include <circleprogressbar.h>
ConnectPage::ConnectPage(QString text, bool isSettingsPage, QFont* font, QWidget *parent) : QWidget(parent), model(Model::getInstance()), esp(ESP32::getInstance()){

    progressDeviceSearch = new CircleProgressBar(25);
    progressDeviceTested = new CircleProgressBar(25);
    progressDeviceFound = new CircleProgressBar(25);

    btSearch = new BluetoothButton(25, this);

    QLabel* lbWelcome = new QLabel(text, this);
    QLabel* lbDeviceTested = new QLabel("Test: ", this);
    QLabel* lbDeviceFound = new QLabel("Gefunden: ", this);
    QLabel* lbDeviceConnected = new QLabel("Verbunden: ", this);


    QFont usedFont = nullptr != font ? *font : lbWelcome->font();
    QGridLayout* layout = new QGridLayout(this);
    int pointSize = usedFont.pointSize();
    usedFont.setPointSize(32);
    lbWelcome->setFont(usedFont);
    usedFont.setPointSize(pointSize);
    lbDeviceFound->setFont(usedFont);
    lbDeviceTested->setFont(usedFont);
    lbDeviceConnected->setFont(usedFont);

    lbWelcome->setAlignment(Qt::AlignCenter);
    lbDeviceFound->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    lbDeviceTested->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    lbDeviceConnected->setAlignment(Qt::AlignLeft | Qt::AlignCenter);

    layout->addWidget(lbWelcome, 0, 0, 1, 3);
    layout->addWidget(btSearch, 6, 1, 1, 1);
    layout->addWidget(lbDeviceFound, 8, 0, Qt::AlignLeft);
    layout->addWidget(progressDeviceSearch, 8, 1, Qt::AlignVCenter | Qt::AlignHCenter);

    layout->addWidget(lbDeviceConnected, 9, 0, Qt::AlignLeft);
    layout->addWidget(progressDeviceFound, 9, 1, Qt::AlignVCenter | Qt::AlignHCenter);

    layout->addWidget(lbDeviceTested, 10, 0, Qt::AlignLeft);
    layout->addWidget(progressDeviceTested, 10, 1, Qt::AlignVCenter | Qt::AlignHCenter);

    connect(btSearch, &BluetoothButton::pressed, this, &ConnectPage::buttonSearchPressed);

    setLayout(layout);



    btSearch->setToolTip("Sohle suchen.");


    if(isSettingsPage){
        btNext = new ArrowButton(ArrowButtonDirection::Right, this);
        layout->addWidget(btNext, 11, 1, 1, 1);
        connect(btNext, &ArrowButton::pressed, this, &ConnectPage::buttonNextPressed);

        btNext->setRadius(25);
        btNext->setEnabled(false);

        connect(&ESP32::getInstance(), &ESP32::deviceConnected, this, [=]{
            btNext->setEnabled(true);
        });

        connect(&ESP32::getInstance(), &ESP32::deviceDisconnected, this, [=]{
            btNext->setEnabled(false);
        });
    }else{
        connect(&ESP32::getInstance(), &ESP32::deviceConnected, this, [=]{
            emit deviceConnected();
        });
        connect(&ESP32::getInstance(), &ESP32::deviceDisconnected, this, [=]{
            emit deviceDisconnected();
        });
    }
    connect(btSearch, &BluetoothButton::pressed, &esp, &ESP32::discover);

        connect(btSearch,&BluetoothButton::pressed, this, [=]{
            progressDeviceSearch->setIntermidate();
            progressDeviceFound->setIntermidate();
            progressDeviceTested->setIntermidate();

            progressDeviceSearch->start();
            QTimer* tmr = new QTimer(this);
            tmr->setInterval(500);
            QTimer* tmr2 = new QTimer(this);
            tmr2->setInterval(1000);

            connect(tmr, &QTimer::timeout, this, [=]{
                progressDeviceFound->start();
                tmr->stop();
            });
            connect(tmr2, &QTimer::timeout, this, [=]{
                progressDeviceTested->start();
                tmr2->stop();
            });
            tmr->start();
            tmr2->start();
        });


    connect(&esp, &ESP32::deviceFound, this, [=]{
            progressDeviceSearch->setSucceed();
    });

    connect(&esp, &ESP32::deviceNotFound, this, [=]{
        progressDeviceSearch->setFail();
        progressDeviceFound->setFail();
        progressDeviceTested->setFail();
    });

    connect(&esp, &ESP32::serviceFound, this, [=]{
        progressDeviceFound->setSucceed();
    });

    connect(&esp, &ESP32::serviceNotFound, this, [=]{
        progressDeviceFound->setFail();
        progressDeviceTested->setFail();
    });

    connect(&esp, &ESP32::characteristicsFound, this, [=]{
        progressDeviceTested->setSucceed();
    });

    connect(&esp, &ESP32::characteristicsNotFound, this, [=]{
        progressDeviceTested->setFail();
    });
    connect(&esp, &ESP32::deviceTimeout, this, [=]{
        progressDeviceSearch->setFail();
        progressDeviceFound->setFail();
        progressDeviceTested->setFail();
    });

}

ConnectPage::~ConnectPage(){
}

void ConnectPage::buttonNextPressed(){
    PageHandler::getInstance().requestPage(page::mainPage);
}

void ConnectPage::buttonSearchPressed(){
    // 1. Invoke device search

}

void ConnectPage::show(){
    QWidget::show();
}

void ConnectPage::hide(){
    QWidget::hide();
}
