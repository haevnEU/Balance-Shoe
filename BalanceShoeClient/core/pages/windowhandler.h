#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

/* Qt System */
#include <QObject>

/* User includes */
#include "intropage.h"
#include "mainpage.h"
#include "settingspage.h"
#include "usersettings.h"

#include "../util/utils.h"

namespace haevn::esp::pages{
    enum windows{
        introWindow = 0,
        mainWindow = 1,
        settingsWindow = 2,
        statisticsWindow = 3,
        userSettingsWindow = 4,
        devSettingsWindow = 5
    };

    class WindowHandler : public QObject{
        Q_OBJECT

    public:
        static WindowHandler& getWindowHandler(){
            static WindowHandler instance;
            return instance;

        }
    public slots:

        void show(windows window);

        void changeTheme(QString name);

    private:
        QWidget* lastPage;
        QWidget* currentPage;

        IntroPage* introPage;
        MainPage* mainPage;
        SettingsPage* settingsPage;
        UserSettings* userSettingsPage;

        WindowHandler();
        ~WindowHandler();
    };
}
#endif // WINDOWHANDLER_H
