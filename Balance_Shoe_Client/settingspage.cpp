/*
 * Copyright 2020 nils
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include "settingspage.h"

#include "pagehandler.h"

#include <QInputDialog>
#include <QIntValidator>
#include <QMessageBox>

SettingsPage::SettingsPage(QWidget *parent) : QWidget(parent), model(Model::getInstance()), esp(ESP32::getInstance()) {
    displayed = false;

    inWeight = new QLineEdit(this);
    inWeight->setValidator(new QIntValidator(0, 500, this));

    inMaxWeight = new QLineEdit(this);
    inMaxWeight->setValidator(new QIntValidator(0, 500, this));


    btSearch = new QPushButton(this);
    btDeviceFound = new QPushButton(this);
    btDeviceConnected = new QPushButton(this);
    btDeviceTest = new QPushButton(this);
    btSave = new QPushButton(this);
    btDiscard = new QPushButton(this);

    lbBattery = new QLabel(this);
    lbName = new QLabel();

    QGridLayout* layout = new QGridLayout(this);

    QLabel* lbWeight = new QLabel("Gewicht: ", this);
    QFont font = lbWeight->font();
    lbWeight->setFont(font);
    lbWeight->setAlignment(Qt::AlignLeft);
    layout->addWidget(lbWeight, 3, 0, 1, 1);
    layout->addWidget(inWeight, 3, 1, 1, 2);

    QLabel* lbMaxWeight = new QLabel("Maximales Gewicht: ", this);
    lbMaxWeight->setFont(font);
    lbMaxWeight->setAlignment(Qt::AlignLeft);
    layout->addWidget(lbMaxWeight, 4, 0, 1, 1);
    layout->addWidget(inMaxWeight, 4, 1, 1, 2);

    layout->addWidget(btSearch, 6, 1, 1, 1);

    QLabel* lbDeviceFound = new QLabel("Gefunden: ", this);
    lbDeviceFound->setFont(font);
    lbDeviceFound->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    layout->addWidget(lbDeviceFound, 7, 0, Qt::AlignLeft);
    layout->addWidget(btDeviceFound, 7, 1, Qt::AlignLeft);

    QLabel* lbDeviceConnected = new QLabel("Verbunden: ", this);
    lbDeviceConnected->setFont(font);
    lbDeviceConnected->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    layout->addWidget(lbDeviceConnected, 8, 0, Qt::AlignLeft);
    layout->addWidget(btDeviceConnected, 8, 1, Qt::AlignLeft);

    QLabel* lbDeviceTested = new QLabel("Test: ", this);
    lbDeviceTested->setFont(font);
    lbDeviceTested->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    layout->addWidget(lbDeviceTested, 9, 0, Qt::AlignLeft);
    layout->addWidget(btDeviceTest, 9, 1, Qt::AlignLeft);

    layout->addWidget(btDiscard, 10, 0, 1, 1);
    layout->addWidget(btSave, 10, 0, 1, 1);


    inMaxWeight->setText(QString::number(static_cast<double>(model.getMaxWeight())));
    setLayout(layout);

    btSearch->setFlat(true);
    btSearch->setToolTip("Sohle suchen.");
    btDeviceFound->setFlat(true);
    btDeviceConnected->setFlat(true);
    btDeviceTest->setFlat(true);

    btSearch->setIcon(QIcon(":/icons/res/baseline_bluetooth_searching_white.png"));
    btDeviceFound->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));
    btDeviceConnected->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));
    btDeviceTest->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));

    btSave->setFlat(true);
    btDiscard->setFlat(true);
    btSave->setIcon(QIcon(":/icons/res/baseline_check_circle_outline_white.png"));
    btDiscard->setIcon(QIcon(":/icons/res/baseline_highlight_off_white.png"));
    displayed = false;


#ifdef Q_OS_MACOS
    btSave->setIconSize(QSize(50, 50));
    btSave->setFixedSize(QSize(50, 50));
    btDiscard->setIconSize(QSize(50, 50));
    btDiscard->setFixedSize(QSize(50, 50));
    btSearch->setIconSize(QSize(50, 50));
    btSearch->setFixedSize(QSize(50, 50));
    btDeviceFound->setIconSize(QSize(50, 50));
    btDeviceFound->setFixedSize(QSize(50, 50));
    btDeviceConnected->setIconSize(QSize(50, 50));
    btDeviceConnected->setFixedSize(QSize(50, 50));
    btDeviceTest->setIconSize(QSize(50, 50));
    btDeviceTest->setFixedSize(QSize(50, 50));
#else

    btSave->setIconSize(QSize(100, 100));
    btSave->setFixedSize(QSize(100, 100));
    btDiscard->setIconSize(QSize(100, 100));
    btDiscard->setFixedSize(QSize(100, 100));
    btSearch->setIconSize(QSize(100, 100));
    btSearch->setFixedSize(QSize(100, 100));
    btDeviceFound->setIconSize(QSize(100, 100));
    btDeviceFound->setFixedSize(QSize(100, 100));
    btDeviceConnected->setIconSize(QSize(100, 100));
    btDeviceConnected->setFixedSize(QSize(100, 100));
    btDeviceTest->setIconSize(QSize(100, 100));
    btDeviceTest->setFixedSize(QSize(100, 100));
#endif

    lbName->setText(model.getName());
    lbBattery->setText(QString::number(model.getBatteryPercentage()).append(" %"));
    layout->addWidget(lbName, 0, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(lbBattery, 0, 2, 1,1,  Qt::AlignTop | Qt::AlignRight);

    layout->addWidget(btSave, 11, 2, 1, 1, Qt::AlignBottom);
    layout->addWidget(btDiscard, 11, 0, 1, 1, Qt::AlignBottom);

    connect(btSave, &QPushButton::pressed, this, [=]{
        model.setMaxWeight(inMaxWeight->text().toInt());

        model.save();
        PageHandler::getInstance().requestPage(page::mainPage);
    });

    connect(btDiscard, &QPushButton::pressed, this, [=]{
        PageHandler::getInstance().requestPage(page::mainPage);
    });
    QPushButton* btDeviceSettings = new QPushButton("Device Settings");
    layout->addWidget(btDeviceSettings, 20, 1, 1, 1, Qt::AlignBottom);
    connect(btDeviceSettings, &QPushButton::pressed, this,[=]{
        bool ok;
            QString text = QInputDialog::getText(this, "Service Pin",
                                                 "Für diese Aktion wird der Service pin benötigt.", QLineEdit::Normal,
                                                 "", &ok);
            if (ok && !text.isEmpty()) {
                int pin = text.toInt();
                if(pin == servicePin){
                    QMessageBox::information(this, "Authentifiziert", "Geräte Einstellungen sichtbar");
                }else{

                    QMessageBox::warning(this, "Nicht authentifiziert", "Der Service Pin ist falsch");
                }
            }
    });

    setLayout(layout);

    connect(&model, &Model::nameChanged, this, &SettingsPage::nameChanged);
    connect(&model, &Model::maxWeightChanged, this, &SettingsPage::maxWeightChanged);
    connect(&model, &Model::batterPercentageChanged, this, &SettingsPage::batteryPercentageChanged);

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

SettingsPage::~SettingsPage(){
}

void SettingsPage::show(){
    displayed = true;
    QWidget::show();
}

void SettingsPage::hide(){

    displayed = false;
    QWidget::hide();
}

bool SettingsPage::isDisplayed(){
    return displayed;
}

void SettingsPage::nameChanged(QString name){
    lbName->setText(name);
}

void SettingsPage::weightChanged(int weight){
    inWeight->setText(QString::number(weight).append(" kg"));
}

void SettingsPage::maxWeightChanged(int weight){
    inMaxWeight->setText(QString::number(weight).append(" kg"));
}

void SettingsPage::batteryPercentageChanged(int battery){
    lbBattery->setText(QString::number(battery).append(" %"));
}
