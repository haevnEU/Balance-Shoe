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
#ifndef PAGEHANDLER_H
#define PAGEHANDLER_H

#include <QObject>

#include "mainpage.h"
#include "welcomepage.h"
#include "settingspage.h"
#include "connectpage.h"
#include "model.h"
enum page{
    mainPage = 0, welcomePage = 1, settingsPage = 2
};

class PageHandler : public QObject{
    Q_OBJECT
public:
    static PageHandler& getInstance(){
        static PageHandler instance;
        return instance;
    }

#ifdef Q_OS_ANDROID
    static const int multiplier = 2;
#else
    static const int multiplier = 1;
#endif
private:

    MainPage* mainPage;
    WelcomePage* welcomePage;
    SettingsPage* settingsPage;
    ConnectPage* connectPage;
    explicit PageHandler(QObject *parent = nullptr);

public:
    ~PageHandler();

    Model& model;
signals:

public slots:

    void requestPage(page which);
};

#endif // PAGEHANDLER_H
