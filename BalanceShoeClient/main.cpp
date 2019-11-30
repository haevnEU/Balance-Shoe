#include <QApplication>
#include <QFile>

#include "intropage.h"
#include "windowhandler.h"

void changeTheme(){

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WindowHandler::getWindowHandler().show(windows::introWindow);
    WindowHandler::getWindowHandler().changeTheme("MaterialDark");


    return a.exec();
}
