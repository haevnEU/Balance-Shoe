/**
 * @file main.cpp
 * @brief This file provides the main entry point
 * @author Nils Milewski (nimile/10010480)
 */

#include <QApplication>
#include "pages/windowhandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    haevn::esp::pages::WindowHandler::getWindowHandler().show(haevn::esp::pages::windows::introWindow);
    haevn::esp::pages::WindowHandler::getWindowHandler().changeTheme("MaterialDark");

    return a.exec();
}
