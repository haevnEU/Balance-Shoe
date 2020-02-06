/*
 * Copyright 2019 nils
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
#include "iosusersettingspage.h"

#if defined(Q_OS_IOS)

#include "core/windowhandler.h"
#include <QScrollArea>
#include "core/usersettings.h"

using namespace haevn::esp::pages;

IosUserSettingsPage::IosUserSettingsPage(QWidget *parent) : QWidget(parent){
    font = QWidget::font();
    font.setPointSize(24);

    setLayout(createLayout());
    auto& userSettings = core::UserSettings::getUserSettings();

    connect(&userSettings, &core::UserSettings::userNameChanged, this, &IosUserSettingsPage::userNameChanged);
    connect(&userSettings, &core::UserSettings::userWeightChanged, this, &IosUserSettingsPage::userWeightChanged);
    connect(&userSettings, &core::UserSettings::maxWeightChanged, this, &IosUserSettingsPage::maxWeightChanged);
    connect(&userSettings, &core::UserSettings::themeChanged, this, &IosUserSettingsPage::themeChanged);
}

void IosUserSettingsPage::currentIndexChanged(int index){
    core::UserSettings::getUserSettings().setThemeName(index);
    core::WindowHandler::getWindowHandler().changeTheme(core::UserSettings::getUserSettings().indexToThemeName(index));

}

QLayout* IosUserSettingsPage::createLayout(){

    auto layout = new QGridLayout();

    inputName = new widgets::CustomLineEdit();
    inputName->setText(core::UserSettings::getUserSettings().getUserName());
    inputWeight = new widgets::CustomLineEdit();
    inputWeight->setText(QString::number(core::UserSettings::getUserSettings().getUserWeight()));
    inputMaxWeight = new widgets::CustomLineEdit();
    inputMaxWeight->setText(QString::number(core::UserSettings::getUserSettings().getMaxWeight()));
    buttonSaveSettings = new QPushButton("Save");
    comboBoxTheme = new QComboBox();
    comboBoxTheme->setCurrentText(core::UserSettings::getUserSettings().getThemeName());

    inputMaxWeight->setValidator( new QIntValidator(0, 100, this) );
    inputWeight->setValidator( new QIntValidator(0, 100, this) );

    for(auto theme : core::UserSettings::getUserSettings().getThemes()){
        comboBoxTheme->addItem(theme);
    }
    comboBoxTheme->setCurrentIndex(core::UserSettings::getUserSettings().themeNameToIndex());

    auto labelName = new QLabel("Name");
    auto labelWeight = new QLabel("Weight");
    auto labelMaxWeight = new QLabel("Max weight");
    auto labelThemes = new QLabel("Theme");
    auto btBack = new QPushButton("Back");

    labelMaxWeight->setFont(font);
    labelWeight->setFont(font);
    labelName->setFont(font);
    labelThemes->setFont(font);
    buttonSaveSettings->setFont(font);
    inputName->setFont(font);
    inputWeight->setFont(font);
    inputMaxWeight->setFont(font);

    layout->addWidget(labelName, 0, 0);
    layout->addWidget(inputName, 0, 1);
    layout->addWidget(labelWeight, 1, 0);
    layout->addWidget(inputWeight, 1, 1);
    layout->addWidget(labelMaxWeight, 2, 0);
    layout->addWidget(inputMaxWeight, 2, 1);
    layout->addWidget(labelThemes, 3, 0);
    layout->addWidget(comboBoxTheme, 3, 1);

    layout->addWidget(buttonSaveSettings, 5, 1);


    layout->addWidget(btBack, 6, 0, 1, 2);

    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(10);


    connect(comboBoxTheme, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
    connect(btBack, &QPushButton::pressed, this, &IosUserSettingsPage::buttonBackPressed);
    connect(buttonSaveSettings, &QPushButton::pressed, this, &IosUserSettingsPage::buttonSavePressed);

    return layout;
}

#include <QMessageBox>
#include "util/filehandler.h"
void IosUserSettingsPage::buttonSavePressed(){
    auto name = inputName->text();
    auto weight = inputWeight->text().toUInt();
    auto maxWeight = inputMaxWeight->text().toUInt();
    core::UserSettings::getUserSettings().setUserName(name);
    core::UserSettings::getUserSettings().setUserWeight(weight);
    core::UserSettings::getUserSettings().setMaxWeight(maxWeight);
    core::UserSettings::getUserSettings().save();
}

void IosUserSettingsPage::buttonBackPressed(){
    auto& wd = core::WindowHandler::getWindowHandler();
    wd.show(core::windows::mainWindow);
}

void IosUserSettingsPage::userNameChanged(QString name){
    inputName->setText(name);
}

void IosUserSettingsPage::userWeightChanged(uint weight){
    inputWeight->setText(QString::number(weight));
}

void IosUserSettingsPage::maxWeightChanged(uint weight){
    inputMaxWeight->setText(QString::number(weight));
}

void IosUserSettingsPage::themeChanged(QString name){
    core::WindowHandler::getWindowHandler().changeTheme(name);
}

#endif // defined(Q_OS_Ios)
