#include "macmainpage.h"

#if defined(Q_OS_MAC)

#include "core/windowhandler.h"
#include "util/filehandler.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include "util/bluetoothutil.h"

using namespace haevn::esp::pages;

MacMainPage::MacMainPage(QWidget *parent) : QWidget(parent){
    vib = &util::Vibrator::getVibrator();
    auto layout = new QVBoxLayout;
    auto buttonLayout = new QHBoxLayout;

    auto labelName = new QLabel("Balance Shoe");
    buttonUserSettings = new QPushButton("User Settings");
    buttonOn = new QPushButton("On");
    buttonOff = new QPushButton("Off");
    buttonOff->setEnabled(false);
    buttonStat = new QPushButton("Dev Settings");
    auto font = labelName->font();

    font.setPointSize(64);

    labelName->setFont(font);
    font.setPointSize(32);
    buttonUserSettings->setFont(font);
    buttonStat->setFont(font);
    buttonOn->setFont(font);
    buttonOff->setFont(font);

    layout->addWidget(labelName);

    layout->addWidget(buttonOn);
    layout->addWidget(buttonOff);

    buttonLayout->addWidget(buttonUserSettings);
    buttonLayout->addWidget(buttonStat);

    layout->addLayout(buttonLayout);
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    connect(buttonOn, &QPushButton::pressed, this, &MacMainPage::buttonOnPressed);
    connect(buttonOff, &QPushButton::pressed, this, &MacMainPage::buttonOffPressed);
    connect(buttonStat, &QPushButton::pressed, this, &MacMainPage::buttonDevPressed);
    connect(buttonUserSettings, &QPushButton::pressed, this, &MacMainPage::buttonShowUserSettings);



    auto btSave = new QPushButton("TEST COMMAND BUILD");
    auto btLoad = new QPushButton("Load");


    connect(btSave, &QPushButton::clicked, [this](){
        QMessageBox::information(this, "Bluetooth create command", bluetooth::util::test());
    });

    connect(btLoad, &QPushButton::clicked, [this](){
        QString tmp = util::FileHandler::getFileHandler().read("user.set");
        QMessageBox::information(this, "Info", tmp);
    });

    auto hbox = new QHBoxLayout();
    hbox->addWidget(btSave);
    hbox->addWidget(btLoad);
    layout->addLayout(hbox);
}


void MacMainPage::buttonOnPressed(){
    buttonOff->setEnabled(true);
    buttonOn->setEnabled(false);
    vib->vibrate(5000);
}

void MacMainPage::buttonOffPressed(){
    buttonOff->setEnabled(false);
    buttonOn->setEnabled(true);
    vib->vibrateStop();
}

void MacMainPage::buttonShowUserSettings(){
    core::WindowHandler::getWindowHandler().show(core::windows::userSettingsWindow);
}

void MacMainPage::buttonDevPressed(){
    core::WindowHandler::getWindowHandler().show(core::windows::devSettingsWindow);
}


#endif // defined(Q_OS_MAC)
