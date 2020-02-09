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

    inName = new QLineEdit(this);

    inMaxWeight = new QLineEdit(this);
    inMaxWeight->setValidator(new QIntValidator(0, 500, this));

    btSave = new ArrowButton(ArrowButtonDirection::Accept, this);
    btDiscard = new ArrowButton(ArrowButtonDirection::Cross, this);

    lbBattery = new QLabel(this);
    lbName = new QLabel();

    QGridLayout* layout = new QGridLayout(this);

    QLabel* lbName = new QLabel("Name: ", this);
    QFont font = lbName->font();
    lbName->setFont(font);
    lbName->setAlignment(Qt::AlignLeft);
    layout->addWidget(lbName, 4, 0);
    layout->addWidget(inName, 4, 1, 1, 2);

    QLabel* lbMaxWeight = new QLabel("Maximales Gewicht: ", this);
    lbMaxWeight->setFont(font);
    lbMaxWeight->setAlignment(Qt::AlignLeft);
    layout->addWidget(lbMaxWeight, 5, 0);
    layout->addWidget(inMaxWeight, 5, 1, 1, 2);

    layout->addWidget(new ConnectPage("", false, &font, this), 6, 0, 1, 3);


    inMaxWeight->setText(QString::number(static_cast<double>(model.getMaxWeight())));
    inName->setText(model.getName());
    setLayout(layout);


    displayed = false;

    btSave->setRadius(25);
    btDiscard->setRadius(25);

    lbName->setText(model.getName());
    lbBattery->setText(QString::number(model.getBatteryPercentage()).append(" %"));
    layout->addWidget(lbName, 0, 0, Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(lbBattery, 0, 2,  Qt::AlignTop | Qt::AlignRight);

    layout->addWidget(btDiscard, 11, 0, Qt::AlignBottom);
    layout->addWidget(btSave, 11, 2, Qt::AlignBottom);

    connect(btSave, &ArrowButton::pressed, this, [=]{
        model.setMaxWeight(inMaxWeight->text().toInt());
        model.setName(inName->text());
        model.save();
        PageHandler::getInstance().requestPage(page::mainPage);
    });

    connect(btDiscard, &ArrowButton::pressed, this, [=]{
        PageHandler::getInstance().requestPage(page::mainPage);
    });

    setLayout(layout);

    connect(&model, &Model::nameChanged, this, &SettingsPage::nameChanged);
    connect(&model, &Model::maxWeightChanged, this, &SettingsPage::maxWeightChanged);
    connect(&model, &Model::batterPercentageChanged, this, &SettingsPage::batteryPercentageChanged);
}

SettingsPage::~SettingsPage(){}

void SettingsPage::show(){
    displayed = true;
    inName->setText(model.getName());
    inMaxWeight->setText(QString::number(static_cast<double>(model.getMaxWeight())));
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

void SettingsPage::maxWeightChanged(int weight){
    inMaxWeight->setText(QString::number(weight).append(" kg"));
}

void SettingsPage::batteryPercentageChanged(int battery){
    lbBattery->setText(QString::number(battery).append(" %"));
}
