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
#include "pagehandler.h"

#include <QFile>

PageHandler::PageHandler(QObject *parent) : QObject(parent), model(Model::getInstance()){
    mainPage = new MainPage();
    welcomePage = new WelcomePage();
    settingsPage = new SettingsPage();
    connectPage = new ConnectPage("Verbinden", true);
    QFile styleFile(":/style/res/QTDark.qss");
    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    welcomePage->setStyleSheet(style);
    mainPage->setStyleSheet(style);
    settingsPage->setStyleSheet(style);
    connectPage->setStyleSheet(style);
}

PageHandler::~PageHandler(){
    mainPage->hide();
    welcomePage->hide();
    settingsPage->hide();
    connectPage->hide();

    delete mainPage;
    delete settingsPage;
    delete connectPage;
}

void PageHandler::requestPage(page which){
    mainPage->hide();
    welcomePage->hide();
    settingsPage->hide();
    connectPage->hide();
    if(!Model::getInstance().isFirstRun() && !ESP32::getInstance().isDeviceConnected()){
        connectPage->show();
    }else{

        switch(which){
        case page::mainPage:
            mainPage->show();
            break;
        case page::welcomePage:
            welcomePage->show();
            break;
        case page::settingsPage:
            settingsPage->show();
            break;
        }
    }
}
