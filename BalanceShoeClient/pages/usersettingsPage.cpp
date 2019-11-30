#include "usersettingsPage.h"
#include "core/windowhandler.h"
#include <QScrollArea>
#include "core/usersettings.h"

using namespace haevn::esp::pages;

UserSettingsPage::UserSettingsPage(QWidget *parent) : QWidget(parent){
    font = QWidget::font();
    font.setPointSize(24);

 #if defined(Q_OS_ANDROID)
#else
    auto scrollArea = new QScrollArea(this);
#endif

    setLayout(createLayout());
    auto& userSettings = core::UserSettings::getUserSettings();

    connect(&userSettings, &core::UserSettings::userNameChanged, this, &UserSettingsPage::userNameChanged);
    connect(&userSettings, &core::UserSettings::userWeightChanged, this, &UserSettingsPage::userWeightChanged);
    connect(&userSettings, &core::UserSettings::maxWeightChanged, this, &UserSettingsPage::maxWeightChanged);
    connect(&userSettings, &core::UserSettings::themeChanged, this, &UserSettingsPage::themeChanged);
}

void UserSettingsPage::currentIndexChanged(int index){
    core::UserSettings::getUserSettings().setThemeName(index);
    core::WindowHandler::getWindowHandler().changeTheme(core::UserSettings::getUserSettings().indexToThemeName(index));

}

#if defined(Q_OS_ANDROID)
QLayout* UserSettingsPage::createLayout(){

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

    layout->addWidget(buttonSaveSettings, 4, 1);


    layout->addWidget(btBack, 5, 0, 1, 2);

    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(10);


    connect(comboBoxTheme, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
    connect(btBack, &QPushButton::pressed, this, &UserSettingsPage::buttonBackPressed);
    connect(buttonSaveSettings, &QPushButton::pressed, this, &UserSettingsPage::buttonSavePressed);

    return layout;
}
#else
QLayout* UserSettings::createLayout(){
    inputName = new QLineEdit();
    inputWeight = new  QLineEdit;
    inputMaxWeight = new  QLineEdit;
    comboBoxTheme = new QComboBox();
    buttonSaveSettings = new QPushButton("Save");
}

#endif
#include <QMessageBox>
#include "../util/filehandler.h"
void UserSettingsPage::buttonSavePressed(){
    auto name = inputName->text();
    auto weight = inputWeight->text().toUInt();
    auto maxWeight = inputMaxWeight->text().toUInt();
    core::UserSettings::getUserSettings().setUserName(name);
    core::UserSettings::getUserSettings().setUserWeight(weight);
    core::UserSettings::getUserSettings().setMaxWeight(maxWeight);
    core::UserSettings::getUserSettings().save();
}

void UserSettingsPage::buttonBackPressed(){
    auto& wd = core::WindowHandler::getWindowHandler();
    wd.show(core::windows::mainWindow);
}

void UserSettingsPage::userNameChanged(QString name){
    inputName->setText(name);
}

void UserSettingsPage::userWeightChanged(uint weight){
    inputWeight->setText(QString::number(weight));
}

void UserSettingsPage::maxWeightChanged(uint weight){
    inputMaxWeight->setText(QString::number(weight));
}

void UserSettingsPage::themeChanged(QString name){
    core::WindowHandler::getWindowHandler().changeTheme(name);
}
