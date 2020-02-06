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
#include "welcomepage.h"
#include "pagehandler.h"
#include <QtGlobal>
#include <QIntValidator>

WelcomePage::WelcomePage(QWidget *parent) : QWidget(parent), model(Model::getInstance()), esp(ESP32::getInstance()){

    inName = new QLineEdit(this);
    inMaxWeight = new QLineEdit(this);

    btNext = new QPushButton(this);
    btSearch = new QPushButton(this);
    btDeviceTest = new QPushButton(this);
    btDeviceFound = new QPushButton(this);
    btDeviceConnected = new QPushButton(this);

    QLabel* lbName = new QLabel("Name: ", this);
    QLabel* lbWelcome = new QLabel("Wilkommen", this);
    QLabel* lbDeviceTested = new QLabel("Test: ", this);
    QLabel* lbDeviceFound = new QLabel("Gefunden: ", this);
    QLabel* lbDeviceConnected = new QLabel("Verbunden: ", this);
    QLabel* lbMaxWeight = new QLabel("Maximales Gewicht: ", this);
    QLabel* lbInfoText = new QLabel("Gib deine Basics ein.", this);

    QFont font = lbWelcome->font();
    QGridLayout* layout = new QGridLayout(this);

    displayed = false;

    inMaxWeight->setValidator(new QIntValidator(0, 500, this));

    font.setPointSize(32);
    lbWelcome->setFont(font);
    lbWelcome->setAlignment(Qt::AlignCenter);
    layout->addWidget(lbWelcome, 0, 0, 1, 3);

    font.setPointSize(24);
    lbInfoText->setFont(font);
    lbInfoText->setAlignment(Qt::AlignCenter);
    layout->addWidget(lbInfoText, 1, 0, 1, 3);

    font.setPointSize(16);
    lbName->setFont(font);
    lbName->setAlignment(Qt::AlignLeft);
    layout->addWidget(lbName, 2, 0, 1, 1);
    layout->addWidget(inName, 2, 1, 1, 2);


    lbMaxWeight->setFont(font);
    lbMaxWeight->setAlignment(Qt::AlignLeft);
    layout->addWidget(lbMaxWeight, 4, 0, 1, 1);
    layout->addWidget(inMaxWeight, 4, 1, 1, 2);

    layout->addWidget(btSearch, 6, 1, 1, 1);

    lbDeviceFound->setFont(font);
    lbDeviceFound->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    layout->addWidget(lbDeviceFound, 8, 0, Qt::AlignLeft);
    layout->addWidget(btDeviceFound, 8, 1, Qt::AlignLeft);

    lbDeviceConnected->setFont(font);
    lbDeviceConnected->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    layout->addWidget(lbDeviceConnected, 9, 0, Qt::AlignLeft);
    layout->addWidget(btDeviceConnected, 9, 1, Qt::AlignLeft);

    lbDeviceTested->setFont(font);
    lbDeviceTested->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    layout->addWidget(lbDeviceTested, 10, 0, Qt::AlignLeft);
    layout->addWidget(btDeviceTest, 10, 1, Qt::AlignLeft);

    layout->addWidget(btNext, 11, 1, 1, 1);

    connect(btNext, &QPushButton::pressed, this, &WelcomePage::buttonNextPressed);

    inName->setText(model.getName());
    setLayout(layout);

    btNext->setFlat(true);
    btSearch->setFlat(true);
    btSearch->setToolTip("Sohle suchen.");
    btDeviceFound->setFlat(true);
    btDeviceConnected->setFlat(true);
    btDeviceTest->setFlat(true);

    btNext->setIcon(QIcon(":/icons/res/baseline_navigate_next_white.png"));
    btSearch->setIcon(QIcon(":/icons/res/baseline_bluetooth_searching_white.png"));
    btDeviceFound->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));
    btDeviceConnected->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));
    btDeviceTest->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));

#ifdef Q_OS_MACOS
    btNext->setIconSize(QSize(50, 50));
    btNext->setFixedSize(QSize(50, 50));
    btSearch->setIconSize(QSize(50, 50));
    btSearch->setFixedSize(QSize(50, 50));
    btDeviceFound->setIconSize(QSize(50, 50));
    btDeviceFound->setFixedSize(QSize(50, 50));
    btDeviceConnected->setIconSize(QSize(50, 50));
    btDeviceConnected->setFixedSize(QSize(50, 50));
    btDeviceTest->setIconSize(QSize(50, 50));
    btDeviceTest->setFixedSize(QSize(50, 50));
#else

    btNext->setIconSize(QSize(100, 100));
    btNext->setFixedSize(QSize(100, 100));
    btSearch->setIconSize(QSize(100, 100));
    btSearch->setFixedSize(QSize(100, 100));
    btDeviceFound->setIconSize(QSize(100, 100));
    btDeviceFound->setFixedSize(QSize(100, 100));
    btDeviceConnected->setIconSize(QSize(100, 100));
    btDeviceConnected->setFixedSize(QSize(100, 100));
    btDeviceTest->setIconSize(QSize(100, 100));
    btDeviceTest->setFixedSize(QSize(100, 100));
#endif
    connect(btSearch, &QPushButton::pressed, &esp, &ESP32::discover);


    connect(btSearch, &QPushButton::pressed, &esp,[=]{

        btDeviceFound->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));
        btDeviceConnected->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));
        btDeviceTest->setIcon(QIcon(":/icons/res/baseline_schedule_white.png"));
    });




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

WelcomePage::~WelcomePage(){
}

void WelcomePage::buttonNextPressed(){
    // 1. Validate
    if("" == inName->text() || "" == inMaxWeight->text()){
        return;
    }
    // 2. Set Values
    model.setName(inName->text());
    model.setMaxWeight(inMaxWeight->text().toInt());

    // 3. Send Values

    PageHandler::getInstance().requestPage(page::mainPage);
}

void WelcomePage::show(){
    displayed = true;
    QWidget::show();
}

void WelcomePage::hide(){

    displayed = false;
    QWidget::hide();
}

bool WelcomePage::isDisplayed(){
    return displayed;
}
