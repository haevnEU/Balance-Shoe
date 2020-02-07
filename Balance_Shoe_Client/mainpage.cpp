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
#include "mainpage.h"

#include "pagehandler.h"

#include <QAudioOutput>
#include <QDir>
#include <QSound>
#include <QStandardPaths>

MainPage::MainPage(QWidget *parent) : QWidget(parent), model(Model::getInstance()){

    QGridLayout* layout = new QGridLayout();

    btOnOff = new QPushButton("On", this);
    btSettings = new QPushButton("Settings", this);

    lbName = new QLabel("Name", this);
    lbCurrentBatteryPercentage = new QLabel("", this);
    lbCurrentPercentage = new QLabel("Aktuelle Belastung: ", this);

    displayMaxWeight = new QLineEdit(this);
    displayCurrentWeight = new QLineEdit(this);


    QLabel* lbMaxWeight = new QLabel("Maximum: ", this);

    displayed = false;

    layout->addWidget(lbName, 0, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(lbCurrentBatteryPercentage, 0, 2, 1,1,  Qt::AlignTop | Qt::AlignRight);

    layout->addWidget(lbMaxWeight, 2, 0, 1, 1,  Qt::AlignTop);
    layout->addWidget(displayMaxWeight, 2, 1, 1, 2,  Qt::AlignTop);
    layout->addWidget(lbCurrentPercentage, 3, 0, 1, 1,  Qt::AlignTop);
    layout->addWidget(displayCurrentWeight, 3, 1, 1, 2,  Qt::AlignTop);


    layout->addItem(new QSpacerItem(10, 10), 4, 0, 1, 3);

    layout->addWidget(btOnOff, 5, 1, 1, 1);
    layout->addItem(new QSpacerItem(10, 10), 6, 0, 1, 3);
    layout->addWidget(btSettings, 7, 0, 1, 1, Qt::AlignBottom);

    setLayout(layout);

    connect(btSettings, &QPushButton::pressed, this, &MainPage::onButtonSettingsPressed);
    connect(btOnOff, &QPushButton::pressed, this, &MainPage::onButtonOnOffPressed);

    connect(&model, &Model::nameChanged, this, &MainPage::nameChanged);
    connect(&model, &Model::maxWeightChanged, this, &MainPage::maxWeightChanged);
    connect(&model, &Model::batterPercentageChanged, this, &MainPage::batteryPercentageChanged);
    connect(&model, &Model::currentWeightChanged, this, &MainPage::currentWeight);


    warner = new QSound("qrc:/sound/res/nebelhorn.wav");

    connect(&model, &Model::maximumReached, this, [=]{
        if(isOn){
            if(warner->isFinished()){
                warner->play("qrc:/sound/res/nebelhorn.wav");
            }
        }
    });

    connect(&model, &Model::maximumNotReached, this, [=]{
        if(isOn){
            warner->stop();
        }
    });

    displayCurrentWeight->setText(QString::number(static_cast<double>(model.getCurrentWeight())).append(" kg"));
    displayMaxWeight->setText(QString::number(static_cast<double>(model.getMaxWeight())).append(" kg"));
    lbName->setText(model.getName());

    isOn = false;
}


MainPage::~MainPage(){
}

void MainPage::show(){
    displayed = true;
    QWidget::show();
}

void MainPage::hide(){

    displayed = false;
    QWidget::hide();
}

bool MainPage::isDisplayed(){
    return displayed;
}

void MainPage::onButtonSettingsPressed(){
    PageHandler::getInstance().requestPage(page::settingsPage);
}

void MainPage::onButtonOnOffPressed(){
    isOn = !isOn;
    if(isOn){
        btOnOff->setText("Off");
    }else{
        btOnOff->setText("On");
    }
}

void MainPage::nameChanged(QString name){
    lbName->setText(name);
}

void MainPage::weightChanged(int weight){
    displayCurrentWeight->setText(QString::number(weight).append(" kg"));
}

void MainPage::currentWeight(float weight){
    displayCurrentWeight->setText(QString::number(static_cast<double>(weight)).append(" kg"));
}

void MainPage::maxWeightChanged(int weight){
    displayMaxWeight->setText(QString::number(weight).append(" kg"));
}

void MainPage::batteryPercentageChanged(int battery){
    lbCurrentBatteryPercentage->setText(QString::number(battery).append(" %"));
}

