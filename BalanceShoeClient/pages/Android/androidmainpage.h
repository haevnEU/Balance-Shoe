/**
 * @file androidmainpage.h
 * @brief Provides the logic to handle main page
 * @details This file contains the logic for the main page
 *          At this page it is possible to invoke different settings
 *          it is also possible to start the ESP.
 * @author Nils Milewski (nimile/10010480)
 */
#ifndef ANDROIDMAINPAGE_H
#define ANDROIDMAINPAGE_H

#include <QObject>

#if defined(Q_OS_ANDROID)

#include <QWidget>

/* Qt widgets */
#include <QWidget>          // Used as base class
#include <QLabel>
#include <QSpacerItem>      // Used to insert space between UI elements
#include <QPushButton>

/* Qt layout */
#include <QVBoxLayout>      // Used as primary layout

/* User inccldues */
#include "util/vibrator.h"       // Used to vibrate the device
#include "util/utils.h"          // Used to access project utilities


namespace haevn::esp::pages{
   /**
     * @brief The AndroidMainPage class This lass contains the logic to handle main page
     * @details This class contains the logic for the main page
     *          At this page it is possible to invoke different settings
     *          it is also possible to start the ESP.
     * @author Nils Milewski (nimile/10010480)
     */
    class AndroidMainPage : public QWidget{

        Q_OBJECT

    private attributes:

        util::Vibrator* vib;

        QPushButton* buttonOff;

        QPushButton* buttonOn;

        QPushButton* buttonUserSettings;

        QPushButton* buttonStat;

    public methods:

        /**
          * @brief AndroidMainPage This is a constructor.
          * @details This constructor initializes all required attributes and the UI.
          *          It also connects all required signals to their equivalent slot.
          * @param parent This is the parrent object of this page, default nullptr.
          * @author Nils Milewski (nimile/10010480)
          */
        AndroidMainPage(QWidget* parent = nullptr);

    private slots:

        /**
          * @brief buttonOnPressed Currently this method activates the vibration of the device.
          * @details This slot will be invoked if the buttonOn is pressed. It will start the
          *          Bluetooth (Low Energy) connection to the ESP ans enters a listen mode.
          * @author Nils Milewski (nimile/10010480)
          */
        void buttonOnPressed();

        /**
          * @brief buttonOffPressed Currently this method deactivates the vibration of the device.
          * @details This slot will be invoked if the buttonOff is pressed. It will shut down the
          *          Bluetooth (Low Energy) connection to the ESP ans leaves the listen mode.
          * @author Nils Milewski (nimile/10010480)
          */
        void buttonOffPressed();

        /**
          * @brief buttonShowUserSettings This method invokes the user settings.
          * @details This slot will be invoked if the buttonUserSettings is pressed.
          *          It will call the \a show method of the \a WindowHandle object with
          *          \a userSettingsWindow as argument.
          * @author Nils Milewski (nimile/10010480)
          */
        void buttonShowUserSettings();

        /**
          * @brief buttonShowDevSettings This method invokes the developer settings.
          * @details This slot will be invoked if the buttonDevSettings is pressed.
          *          It will call the \a show method of the \a WindowHandle object with
          *          \a devSettingsWindow as argument.
          * @author Nils Milewski (nimile/10010480)
          */
        void buttonDevPressed();

        /**
         * @brief showBluetoothDialog This method opens a dialog of bluetooth devices nearby.
         * @details This slot will be invoked if buttonOn is pressed.
         *          It will open a dialog window where all bluetooth devices nearby gets shown.
         * @author Marc Nowakowski (marcnow/10009339)
         */
        void showBluetoothDialog();
    };
}

#endif // defined(Q_OS_ANDROID)

#endif // ANDROIDMAINPAGE_H
