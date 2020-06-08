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
#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QObject>
#include <QWidget>

#include <QGridLayout>

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include "model.h"

#include "esp32.h"
#include "arrowbutton.h"
class SettingsPage : public QWidget{

    Q_OBJECT

private:


    const int servicePin = 1234;
    bool displayed;

    QLineEdit* inMaxWeight;
    QLineEdit* inName;

    ArrowButton* btSave;
    ArrowButton* btDiscard;
    QLabel* lbName;
    QLabel* lbBattery;
    Model& model;

    ESP32& esp;
public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();

    void show();
    void hide();
    bool isDisplayed();
signals:

public slots:
    void nameChanged(QString name);
    void maxWeightChanged(int weight);
    void batteryPercentageChanged(int battery);
};

#endif // SETTINGSPAGE_H
