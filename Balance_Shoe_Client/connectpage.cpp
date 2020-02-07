#include "connectpage.h"
#include "pagehandler.h"

#include <QGridLayout>
#include <qlabel.h>

ConnectPage::ConnectPage(QString text, bool isSettingsPage, QFont* font, QWidget *parent) : QWidget(parent), model(Model::getInstance()), esp(ESP32::getInstance()){

    btSearch = new QPushButton(this);
    btDeviceTest = new QPushButton(this);
    btDeviceFound = new QPushButton(this);
    btDeviceConnected = new QPushButton(this);

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
    layout->addWidget(btDeviceFound, 8, 1, Qt::AlignLeft);

    layout->addWidget(lbDeviceConnected, 9, 0, Qt::AlignLeft);
    layout->addWidget(btDeviceConnected, 9, 1, Qt::AlignLeft);

    layout->addWidget(lbDeviceTested, 10, 0, Qt::AlignLeft);
    layout->addWidget(btDeviceTest, 10, 1, Qt::AlignLeft);

    connect(btSearch, &QPushButton::pressed, this, &ConnectPage::buttonSearchPressed);

    setLayout(layout);

    btSearch->setFlat(true);
    btDeviceTest->setFlat(true);
    btDeviceFound->setFlat(true);
    btDeviceConnected->setFlat(true);


    btSearch->setToolTip("Sohle suchen.");
    btDeviceTest->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));
    btDeviceFound->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));
    btDeviceConnected->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));
    btSearch->setIcon(QIcon(":/icons/res/baseline_bluetooth_searching_white.png"));

#ifdef Q_OS_MACOS
    btSearch->setIconSize(QSize(50, 50));
    btSearch->setFixedSize(QSize(50, 50));
    btDeviceTest->setIconSize(QSize(50, 50));
    btDeviceTest->setFixedSize(QSize(50, 50));
    btDeviceFound->setIconSize(QSize(50, 50));
    btDeviceFound->setFixedSize(QSize(50, 50));
    btDeviceConnected->setIconSize(QSize(50, 50));
    btDeviceConnected->setFixedSize(QSize(50, 50));
#else

    btSearch->setIconSize(QSize(100, 100));
    btSearch->setFixedSize(QSize(100, 100));
    btDeviceTest->setIconSize(QSize(100, 100));
    btDeviceTest->setFixedSize(QSize(100, 100));
    btDeviceFound->setIconSize(QSize(100, 100));
    btDeviceFound->setFixedSize(QSize(100, 100));
    btDeviceConnected->setIconSize(QSize(100, 100));
    btDeviceConnected->setFixedSize(QSize(100, 100));
#endif

    if(isSettingsPage){
#ifdef Q_OS_MACOS
        btNext = new QPushButton(this);
        layout->addWidget(btNext, 11, 1, 1, 1);

        connect(btNext, &QPushButton::pressed, this, &ConnectPage::buttonNextPressed);
        btNext->setFlat(true);
        btNext->setIcon(QIcon(":/icons/res/baseline_navigate_next_white.png"));
        btNext->setIconSize(QSize(50, 50));
        btNext->setFixedSize(QSize(50, 50));
#else
        btNext->setIconSize(QSize(100, 100));
        btNext->setFixedSize(QSize(100, 100));
#endif
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
    connect(btSearch, &QPushButton::pressed, &esp, &ESP32::discover);

    connect(&esp, &ESP32::deviceFound, this, [=]{
            btDeviceFound->setIcon(QIcon(":/icons/res/baseline_check_circle_outline_white.png"));
    });

    connect(&esp, &ESP32::deviceNotFound, this, [=]{
            btDeviceFound->setIcon(QIcon(":/icons/res/baseline_highlight_off_white.png"));
    });

    connect(&esp, &ESP32::serviceFound, this, [=]{
            btDeviceConnected->setIcon(QIcon(":/icons/res/baseline_check_circle_outline_white.png"));
    });

    connect(&esp, &ESP32::serviceNotFound, this, [=]{
            btDeviceConnected->setIcon(QIcon(":/icons/res/baseline_highlight_off_white.png"));
    });

    connect(&esp, &ESP32::characteristicsFound, this, [=]{
        btDeviceTest->setIcon(QIcon(":/icons/res/baseline_check_circle_outline_white.png"));
    });

    connect(&esp, &ESP32::characteristicsNotFound, this, [=]{
        btDeviceTest->setIcon(QIcon(":/icons/res/baseline_highlight_off_white.png"));
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
