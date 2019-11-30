#include "settingspage.h"

#include "windowhandler.h"
#include <iostream>
#include <QDebug>
#include <QScrollArea>


using namespace haevn::esp::pages;

SettingsPage::SettingsPage(QWidget* parent) : QWidget(parent){

    setLayout(createLayout());
}



#if defined(Q_OS_ANDROID)

QLayout* SettingsPage::createLayout(){

    inputBAUD = new widgets::CustomLineEdit;
    inputDOutPin = new widgets::CustomLineEdit;
    inputSCKPint = new widgets::CustomLineEdit;
    inputReferenceWeight = new widgets::CustomLineEdit;
    inputTolerance = new widgets::CustomLineEdit;
    inputScaleValue = new widgets::CustomLineEdit;

    inputBAUD->setFont(font);
    inputDOutPin->setFont(font);
    inputSCKPint->setFont(font);
    inputReferenceWeight->setFont(font);
    inputTolerance->setFont(font);
    inputScaleValue->setFont(font);

    buttonSaveSetup = new QPushButton("Save Setup");
    buttonSaveSetup->setFont(font);

    QPushButton* btBack = new QPushButton("Back");
    btBack->setFont(font);


    QGridLayout* layout = new QGridLayout();

    QLabel* labelBaud = new QLabel("Baud");
    labelBaud->setFont(font);
    layout->addWidget(labelBaud, 4, 0);
    layout->addWidget(inputBAUD, 4, 1);


    QLabel* labelDout = new QLabel("DOUT pin");
    labelDout->setFont(font);
    layout->addWidget(labelDout, 5, 0);
    layout->addWidget(inputDOutPin, 5, 1);


    QLabel* labelSck = new QLabel("SCK Pin");
    labelSck->setFont(font);
    layout->addWidget(labelSck, 6, 0);
    layout->addWidget(inputSCKPint, 6, 1);


    QLabel* labelRef = new QLabel("Reference weight");
    labelRef->setFont(font);
    layout->addWidget(labelRef, 7, 0);
    layout->addWidget(inputReferenceWeight, 7, 1);

    QLabel* labelTolerance = new QLabel("Tolerance");
    labelTolerance->setFont(font);
    layout->addWidget(labelTolerance, 8, 0);
    layout->addWidget(inputTolerance, 8, 1);


    QLabel* labelScaleValue = new QLabel("Scale value");
    labelScaleValue->setFont(font);
    layout->addWidget(labelScaleValue, 9, 0);
    layout->addWidget(inputScaleValue, 9, 1);


    layout->addWidget(buttonSaveSetup, 10, 0, 1, 2);
    layout->addWidget(btBack, 11, 0, 1, 2);

    QPushButton* btLotto = new QPushButton("Do not press until jackpot is 1Mrd €");

    layout->addWidget(new QLabel(""), 12, 0, 1, 2);
    layout->addWidget(btLotto, 13, 0, 1, 2);

    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(20);


    connect(btBack, &QPushButton::pressed, this, &SettingsPage::buttonBackPressed);
    connect(buttonSaveSetup, &QPushButton::pressed, this, &SettingsPage::buttonSavePressed);
    connect(btLotto, &QPushButton::pressed, this, &SettingsPage::buttonLottoPressed);

    return layout;

}
#else

QLayout* SettingsPage::createLayout(){
    inputBAUD = new QLineEdit;
    inputDOutPin = new QLineEdit;
    inputSCKPint = new QLineEdit;
    inputReferenceWeight = new QLineEdit;
    inputTolerance = new QLineEdit;
    inputScaleValue = new QLineEdit;
}
#endif

#include <QMessageBox>

void SettingsPage::buttonSavePressed(){

    QString msg("");
    msg.append("BAUD: ").append(QString::number(inputBAUD->text().toInt())).append("\n");
    msg.append("DOUT pin: ").append(QString::number(inputDOutPin->text().toInt())).append("\n");
    msg.append("SCK pin: ").append(QString::number(inputSCKPint->text().toInt())).append("\n");
    msg.append("Reference weight: ").append(QString::number(inputReferenceWeight->text().toInt())).append("\n");
    msg.append("Tolerance: ").append(QString::number(inputTolerance->text().toInt())).append("\n");
    msg.append("Scale value: ").append(QString::number(inputScaleValue->text().toInt())).append("\n");

    QMessageBox::information(this, "Input", msg);
}

void SettingsPage::buttonBackPressed(){
    auto& wd = WindowHandler::getWindowHandler();
    wd.show(windows::mainWindow);
}

void SettingsPage::buttonLottoPressed(){

    QString msg("Hier sind die kommenden Lotto zahlen(alle angaben ohne einem Gewehr)\n");
    int nmbr;
    srand(time(0));
    for(int i = 0; i < 6; i++){
        nmbr = rand() % 48 + 1;
        msg.append(QString::number(nmbr)).append(" ");
    }
    QMessageBox::information(this, "Lottozahlen", msg);
}
