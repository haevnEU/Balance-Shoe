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
#include "winusersettingspage.h"

#if defined(Q_OS_WINDOWS)

#include "core/windowhandler.h"
#include <QScrollArea>
#include "core/usersettings.h"

using namespace haevn::esp::pages;

WinUserSettingsPage::WinUserSettingsPage(QWidget *parent) : QWidget(parent){
    font = QWidget::font();
    font.setPointSize(24);

    setLayout(createLayout());
    auto& userSettings = core::UserSettings::getUserSettings();

    connect(&userSettings, &core::UserSettings::userNameChanged, this, &WinUserSettingsPage::userNameChanged);
    connect(&userSettings, &core::UserSettings::userWeightChanged, this, &WinUserSettingsPage::userWeightChanged);
    connect(&userSettings, &core::UserSettings::maxWeightChanged, this, &WinUserSettingsPage::maxWeightChanged);
    connect(&userSettings, &core::UserSettings::themeChanged, this, &WinUserSettingsPage::themeChanged);
}

void WinUserSettingsPage::currentIndexChanged(int index){
    core::UserSettings::getUserSettings().setThemeName(index);
    core::WindowHandler::getWindowHandler().changeTheme(core::UserSettings::getUserSettings().indexToThemeName(index));

}

QLayout* WinUserSettingsPage::createLayout(){

    auto layout = new QGridLayout();

    inputName = new QLineEdit();
    inputName->setText(core::UserSettings::getUserSettings().getUserName());
    inputWeight = new QLineEdit();
    inputWeight->setText(QString::number(core::UserSettings::getUserSettings().getUserWeight()));
    inputMaxWeight = new QLineEdit();
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
    connect(btBack, &QPushButton::pressed, this, &WinUserSettingsPage::buttonBackPressed);
    connect(buttonSaveSettings, &QPushButton::pressed, this, &WinUserSettingsPage::buttonSavePressed);

    return layout;
}

#include <QMessageBox>
#include "util/filehandler.h"
void WinUserSettingsPage::buttonSavePressed(){
    auto name = inputName->text();
    auto weight = inputWeight->text().toUInt();
    auto maxWeight = inputMaxWeight->text().toUInt();
    core::UserSettings::getUserSettings().setUserName(name);
    core::UserSettings::getUserSettings().setUserWeight(weight);
    core::UserSettings::getUserSettings().setMaxWeight(maxWeight);
    core::UserSettings::getUserSettings().save();
}

void WinUserSettingsPage::buttonBackPressed(){
    auto& wd = core::WindowHandler::getWindowHandler();
    wd.show(core::windows::mainWindow);
}

void WinUserSettingsPage::userNameChanged(QString name){
    inputName->setText(name);
}

void WinUserSettingsPage::userWeightChanged(uint weight){
    inputWeight->setText(QString::number(weight));
}

void WinUserSettingsPage::maxWeightChanged(uint weight){
    inputMaxWeight->setText(QString::number(weight));
}

void WinUserSettingsPage::themeChanged(QString name){
    core::WindowHandler::getWindowHandler().changeTheme(name);
}

#endif // defined(Q_OS_Win)
