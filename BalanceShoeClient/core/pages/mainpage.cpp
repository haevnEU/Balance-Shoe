#include "mainpage.h"
#include "windowhandler.h"

using namespace haevn::esp::pages;

MainPage::MainPage(QWidget *parent) : QWidget(parent){
    vib = new util::Vibrator;
    auto layout = new QVBoxLayout;
    auto buttonLayout = new QHBoxLayout;

    auto labelName = new QLabel("Balance Shoe");
    buttonSettings = new QPushButton("User Settings");
    buttonOn = new QPushButton("On");
    buttonOff = new QPushButton("Off");
    buttonOff->setEnabled(false);
    buttonStat = new QPushButton("Dev Settings");
    auto font = labelName->font();

    font.setPointSize(64);

    labelName->setFont(font);
    font.setPointSize(32);
    buttonSettings->setFont(font);
    buttonStat->setFont(font);
    buttonOn->setFont(font);
    buttonOff->setFont(font);

    layout->addWidget(labelName);
#if defined(Q_OS_ANDROID)
    layout->addItem(new QSpacerItem(10, 1000));
#endif
    layout->addWidget(buttonOn);
    layout->addWidget(buttonOff);
#if defined(Q_OS_ANDROID)
    layout->addItem(new QSpacerItem(10, 500));
    layout->addItem(new QSpacerItem(10, 500));
#endif

    buttonLayout->addWidget(buttonSettings);
    buttonLayout->addWidget(buttonStat);

    layout->addLayout(buttonLayout);
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);
    connect(buttonOn, &QPushButton::pressed, this, &MainPage::buttonOnPressed);
    connect(buttonOff, &QPushButton::pressed, this, &MainPage::buttonOffPressed);
    connect(buttonStat, &QPushButton::pressed, this, &MainPage::buttonStatPressed);
    connect(buttonSettings, &QPushButton::pressed, this, &MainPage::buttonShowUserSettings);
}


void MainPage::buttonOnPressed(){

    buttonOff->setEnabled(true);
    buttonOn->setEnabled(false);
    vib->vibrate(5000);
}

void MainPage::buttonOffPressed(){
    buttonOff->setEnabled(false);
    buttonOn->setEnabled(true);
    vib->vibrateStop();
}

void MainPage::buttonShowUserSettings(){
    WindowHandler::getWindowHandler().show(windows::userSettingsWindow);
}

void MainPage::buttonStatPressed(){
    WindowHandler::getWindowHandler().show(windows::settingsWindow);
}
