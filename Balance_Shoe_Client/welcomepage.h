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
#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>

#include "model.h"
#include "esp32.h"

class WelcomePage : public QWidget{

    Q_OBJECT

private:

    QLineEdit* inName;
    QLineEdit* inMaxWeight;

    QPushButton* btSearch;
    QPushButton* btNext;
    QPushButton* btDeviceFound;
    QPushButton* btDeviceConnected;
    QPushButton* btDeviceTest;

    bool displayed;
    Model& model;
    ESP32& esp;

public:
    explicit WelcomePage(QWidget *parent = nullptr);
    ~WelcomePage();
    void hide();
    void show();
    bool isDisplayed();
signals:

public slots:
    void buttonNextPressed();
};

#endif // WELCOMEPAGE_H
