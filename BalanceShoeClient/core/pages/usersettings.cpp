#include "usersettings.h"
#include "windowhandler.h"
#include <QScrollArea>

using namespace haevn::esp::pages;

UserSettings::UserSettings(QWidget *parent) : QWidget(parent){
    font = QWidget::font();
    font.setPointSize(24);

 #if defined(Q_OS_ANDROID)
#else
    auto scrollArea = new QScrollArea(this);
#endif

    setLayout(createLayout());
}

void UserSettings::currentIndexChanged(int index){
    switch(index){
    case 0:
        WindowHandler::getWindowHandler().changeTheme("AMOLED");
        break;
    case 1:
        WindowHandler::getWindowHandler().changeTheme("Aqua");
        break;
    case 2:
        WindowHandler::getWindowHandler().changeTheme("ConsoleStyle");
        break;
    case 3:
        WindowHandler::getWindowHandler().changeTheme("ElegantDark");
        break;
    case 4:
        WindowHandler::getWindowHandler().changeTheme("MaterialDark");
        break;
    case 5:
        WindowHandler::getWindowHandler().changeTheme("Ubuntu");
        break;
    }
}

#if defined(Q_OS_ANDROID)
QLayout* UserSettings::createLayout(){

    auto layout = new QGridLayout();

    inputName = new widgets::CustomLineEdit();
    inputWeight = new widgets::CustomLineEdit();
    inputMaxWeight = new widgets::CustomLineEdit();
    buttonSaveSettings = new QPushButton("Save");
    comboBoxTheme = new QComboBox();


    inputMaxWeight->setValidator( new QIntValidator(0, 100, this) );
    inputWeight->setValidator( new QIntValidator(0, 100, this) );

    comboBoxTheme->addItem("AMOLED");
    comboBoxTheme->addItem("Aqua");
    comboBoxTheme->addItem("ConsoleStyle");
    comboBoxTheme->addItem("ElegantDark");
    comboBoxTheme->addItem("MaterialDark");
    comboBoxTheme->addItem("Ubuntu");


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
    connect(btBack, &QPushButton::pressed, this, &UserSettings::buttonBackPressed);
    connect(buttonSaveSettings, &QPushButton::pressed, this, &UserSettings::buttonSavePressed);

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

void UserSettings::buttonSavePressed(){
    auto name = inputName->text();
    auto weight = inputWeight->text().toInt();
    auto maxWeight = inputMaxWeight->text().toInt();
    QMessageBox::question(this, "Info", QString("Name").append(name)
                                        .append("\nWeight: ").append(QString::number(weight))
                                        .append("\nMax weght: ").append(QString::number(maxWeight)));
}

void UserSettings::buttonBackPressed(){
    auto& wd = WindowHandler::getWindowHandler();
    wd.show(windows::mainWindow);
}
