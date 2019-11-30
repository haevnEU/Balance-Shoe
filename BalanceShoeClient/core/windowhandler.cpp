#include "windowhandler.h"

#include <QDebug>
#include <QFile>
#include <QApplication>
#include "../util/filehandler.h"
#include "usersettings.h"

using namespace haevn::esp::core;

WindowHandler::WindowHandler(){
    introPage = new pages::IntroPage;
    mainPage = new pages::MainPage;
    developerSettingsPage = new pages::SettingsPage;
    userSettingsPage = new pages::UserSettingsPage();
    lastPage = nullptr;

    changeTheme(UserSettings::getUserSettings().getThemeName());
}

WindowHandler::~WindowHandler(){
    delete introPage;
    delete mainPage;
    delete developerSettingsPage;
    delete userSettingsPage;
}

void WindowHandler::show(windows window){
    if(nullptr != currentPage){
        currentPage->close();
        lastPage = currentPage;
    }
    switch (window) {
        case windows::introWindow:
            currentPage = introPage;
        break;
        case windows::mainWindow:
            currentPage = mainPage;
        break;
        case windows::settingsWindow:
            currentPage = developerSettingsPage;
        break;
        case windows::statisticsWindow:
        break;
        case windows::userSettingsWindow:
            currentPage = userSettingsPage;
        break;
        case windows::devSettingsWindow:
            currentPage = developerSettingsPage;
        break;
    }
    currentPage->show();
}

void WindowHandler::changeTheme(QString name){
    QString data;
    QString fileName(":themes/styles/");
    fileName.append(name).append(".qss");

    qDebug() << "Theme name: " << fileName;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"filenot opened"<<endl;
    }
    else
    {
        qDebug()<<"file opened"<<endl;
        data = file.readAll();
    }

    file.close();

    qApp->setStyleSheet(data);
}

