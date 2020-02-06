/**
 * @file main.cpp
 * @brief This file provides the main entry point
 * @author Nils Milewski (nimile/10010480)
 */

#include <QApplication>
#include "core/windowhandler.h"
#include "core/usersettings.h"

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    haevn::esp::core::UserSettings::getUserSettings();
    haevn::esp::core::WindowHandler::getWindowHandler().show(haevn::esp::core::windows::introWindow);

    return a.exec();
}
