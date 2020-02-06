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
#include "winsettingspage.h"

#if defined(Q_OS_WINDOWS)

#include "core/windowhandler.h"
#include <iostream>
#include <QDebug>
#include <QScrollArea>
#include <QMessageBox>

using namespace haevn::esp::pages;

WinSettingsPage::WinSettingsPage(QWidget* parent) : QWidget(parent){
    setLayout(createLayout());
}

QLayout* WinSettingsPage::createLayout(){
    inputBAUD = new QLineEdit;
    inputDOutPin = new QLineEdit;
    inputSCKPint = new QLineEdit;
    inputReferenceWeight = new QLineEdit;
    inputTolerance = new QLineEdit;
    inputScaleValue = new QLineEdit;

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


    connect(btBack, &QPushButton::pressed, this, &WinSettingsPage::buttonBackPressed);
    connect(buttonSaveSetup, &QPushButton::pressed, this, &WinSettingsPage::buttonSavePressed);
    connect(btLotto, &QPushButton::pressed, this, &WinSettingsPage::buttonLottoPressed);

    return layout;

}

void WinSettingsPage::buttonSavePressed(){
    QString msg("");
    msg.append("BAUD: ").append(QString::number(inputBAUD->text().toInt())).append("\n");
    msg.append("DOUT pin: ").append(QString::number(inputDOutPin->text().toInt())).append("\n");
    msg.append("SCK pin: ").append(QString::number(inputSCKPint->text().toInt())).append("\n");
    msg.append("Reference weight: ").append(QString::number(inputReferenceWeight->text().toInt())).append("\n");
    msg.append("Tolerance: ").append(QString::number(inputTolerance->text().toInt())).append("\n");
    msg.append("Scale value: ").append(QString::number(inputScaleValue->text().toInt())).append("\n");

    QMessageBox::information(this, "Input", msg);
}

void WinSettingsPage::buttonBackPressed(){
    core::WindowHandler::getWindowHandler().show(core::windows::mainWindow);
}

void WinSettingsPage::buttonLottoPressed(){

    QString msg("Hier sind die kommenden Lotto zahlen(alle angaben ohne einem Gewehr)\nLottozahlen: ");
    int nmbr;
    srand(time(NULL));
    for(int i = 0; i < 6; i++){
        nmbr = rand() % 48 + 1;
        msg.append(QString::number(nmbr)).append(" ");
    }
    nmbr = rand() % 10;
    msg.append("\n").append("Supperzahl: ").append(QString::number(nmbr));
    QMessageBox::information(this, "Lottozahlen", msg);
}

#endif // defined(Q_OS_Win)
