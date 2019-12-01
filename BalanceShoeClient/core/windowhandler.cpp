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

    // Close current page iff theres an existing page
    // => First run this shouldnt be executed
    if(nullptr != currentPage){
        currentPage->close();
        lastPage = currentPage;
    }
    // This switches the displaying page
    switch (window) {
        case windows::introWindow:
            currentPage = introPage;
        break;
        case windows::mainWindow:
            currentPage = mainPage;
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
    // This method takes the theme name, to receive the full path
    // it is mandatory to change the full name
    // 1. The location of the styles resource folder must be added
    QString fileName(":themes/styles/");
    // 2. The theme name and extension must be added
    fileName.append(name).append(".qss");

    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)) {
        // At this point the theme file exists and will be read from disk
        data = file.readAll();
        qApp->setStyleSheet(data);
    }

    file.close();
}

