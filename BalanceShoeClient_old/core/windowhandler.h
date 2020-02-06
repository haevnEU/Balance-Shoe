/**
 * @file windowhandler.h
 * @brief Provides the logic to handle different pages
 * @details This file contains the primary logic which is used to display different
 *          pages.
 * @author Nils Milewski (nimile/10010480)
 * @todo add clsoing for desktop
 */

#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

/* Qt System */
#include <QObject>      // Used as baseclass

/* User includes */
#include "pages/intropage.h"
#include "pages/mainpage.h"
#include "pages/settingspage.h"
#include "pages/usersettingsPage.h"

#include "util/utils.h"  // Used to access application utilities

namespace haevn::esp::core{

    /**
     * @brief The windows enum This enumeration is used to determine different pages.
     * @author Nils Milewski (nimile/10010480)
     */
    enum windows{
        introWindow = 0,
        mainWindow = 1,
        statisticsWindow = 2,
        userSettingsWindow = 3,
        devSettingsWindow = 4
    };

    /**
     * @brief The WindowHandler class This class provides the logic to handle different pages
     * @details This class will handle different pages. It will used a enumeration to
     *          determine the next page. It an show and display the enum equivalent page.
     * @author Nils Milewski (nimile/10010480)
     */
    class WindowHandler : public QObject{

        Q_OBJECT

    public static_methods:
        /**
         * @brief getWindowHandler This static method returns the singleton object of the class.
         * @details This static method initializes a new instance of this class iff none exist
         *          otherwise the existing instance will be returned.
         *          This singleton implementation will provide automatic destruction if the
         *          application exits.
         * @author Nils Milewski (nimile/10010480)
         */
        static WindowHandler& getWindowHandler(){
            static WindowHandler instance;
            return instance;
        }

    private methods:

        /**
         * @brief WindowHandler This is a constructor.
         * @details This constructor initializes all required pages by the application.
         * @author Nils Milewski (nimile/10010480)
         */
        WindowHandler();

        /**
         * @brief ~WindowHandler This is a destructor.
         * @details This destructor released occupied memory which this class allocated.
         * @author Nils Milewski (nimile/10010480)
         */
        ~WindowHandler();

    public slots:

        /**
         * @brief show This slot is called when a page should be displayed.
         * @details This method accepts a windows type enumeration, it will
         *          used the enumeration to determine which page should be
         *          displayed.
         * @param window This argument is used to determine the next page.
         * @author Nils Milewski (nimile/10010480)
         */
        void show(windows window);

        /**
         * @brief changeTheme This slot is called when the theme should be changed.
         * @details This method accepts a QString which represent the theme name.
         *          It will load the equivaltent qss file from the resources and
         *          assigns it to the application.
         * @param name This argument is used to determine the new theme.
         * @author Nils Milewski (nimile/10010480)
         */
        void changeTheme(QString name);

    private attributes:

        /**
         * @brief lastPage This attribute is used to handle a backbutton pressed
         */
        QWidget* lastPage;

        /**
         * @brief currentPage This attribute holds the current page
         */
        QWidget* currentPage;

        /**
         * @brief mainPage This attribute holds the main page
         */
        pages::MainPage* mainPage;

        /**
         * @brief introPage This attribute holds the intro page
         */
        pages::IntroPage* introPage;

        /**
         * @brief settingsPage This attribute holds the developer settings page
         */
        pages::SettingsPage* developerSettingsPage;

        /**
         * @brief userSettingsPage This attribute holds the user settings page
         */
        pages::UserSettingsPage* userSettingsPage;

    };
}
#endif // WINDOWHANDLER_H
