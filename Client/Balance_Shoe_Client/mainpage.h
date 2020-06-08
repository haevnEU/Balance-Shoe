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
#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QObject>
#include <QSound>
#include <QWidget>
#include <qaudiooutput.h>
#include <qfile.h>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "model.h"
#include <QSoundEffect>
#include <QMediaPlayer>
#include "officon.h"
#include "settingsbutton.h"

class MainPage : public QWidget{

    Q_OBJECT

private:

    bool displayed;

    bool isOn;

    SettingsButton* btSettings;
    OffIcon* btOff;

    QLineEdit* displayMaxWeight;
    QLineEdit* displayCurrentWeight;
    QLabel* lbName;
    QLabel* lbCurrentPercentage;
    QLabel* lbCurrentBatteryPercentage;

    Model& model;
    QSound* warner;

public:

    explicit MainPage(QWidget *parent = nullptr);

    ~MainPage();

    void show();
    void hide();
    bool isDisplayed();
signals:

public slots:
    void onButtonSettingsPressed();
    void onButtonOnOffPressed();
    void batteryPercentageChanged(int battery);
    void
    maxWeightChanged(int weight);
    void weightChanged(int weight);
    void currentWeight(float weight);
    void nameChanged(QString name);
};

#endif // MAINPAGE_H
