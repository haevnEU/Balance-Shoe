/**
 * @file MACusersettings.h
 * @brief Provides the logic to handle the user settings
 * @details This file contains the logic for the user settings.
 *          The following settings can be made here
 *          Name (String input)<br>
 *          Weight (Integer input) <br>
 *          Max weight (Integer input) <br>
 *          Theme (ComboBox choice)
 * @author Nils Milewski (nimile/10010480)
 */
#ifndef MACUSERSETTINGSPAGE_H
#define MACUSERSETTINGSPAGE_H

#include <QObject>
#if defined(Q_OS_MAC)

/* Qt widgets */
#include <QWidget>      // Used as base class
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QLineEdit>
#include <QComboBox>

/* Qt layout*/
#include <QGridLayout>  // Used as layout

/* Project includes */
#include "util/utils.h"              // Used to access project utilities
#include "core/usersettings.h"

namespace haevn::esp::pages{

    /**
     * @brief The UserSettings class This class provides the logic to handle the user settings
     * @details This class contains the logic and UI for the user settings.
     * @author Nils Milewski (nimile/10010480)
     */
    class MacUserSettingsPage : public QWidget{

        Q_OBJECT

    private attributes:

        QFont font;
        QLineEdit* inputName;
        QLineEdit* inputWeight;
        QLineEdit* inputMaxWeight;
        QComboBox* comboBoxTheme;
        QPushButton* buttonSaveSettings;


    public methods:

        /**
         * @brief MacUserSettingsPage This is a constructor.
         * @details This constructor initializes all required attributes and the UI.
         *          To create the UI the constructor will call the createLayout method.
         * @param parent This is the parrent object of this page, default nullptr.
         * @author Nils Milewski (nimile/10010480)
         */
        MacUserSettingsPage(QWidget* parent = nullptr);

    private methods:

        /**
         * @brief createLayout This method create the layout of this widget.
         * @details This method implements the layout of this widget. Important note
         *          if the compiler is set to a desktop version it will create a desktop
         *          layout. If its set to an Mac compiler it will create a layout
         *          which is specialized for an Mac device.
         * @return Layout based on the compiler.
         * @author Nils Milewski (nimile/10010480)
         */
        QLayout* createLayout();

    private slots:

        /**
         * @brief buttonBackPressed This method returns to the previous page.
         * @details This slot invokes the \a back method of the \a windowHandler
         * @author Nils Milewski (nimile/10010480)
         */
        void buttonBackPressed();

        /**
         * @brief currentIndexChanged This method changes the theme of the application.
         * @details This slot is invoked when the QComboBox for the themes changed his index.
         *          This method will invoke the \a changeTheme method of the \a windowHandler
         * @author Nils Milewski (nimile/10010480)
         */
        void currentIndexChanged(int index);

        /**
         * @brief buttonSavePressed This method saves the changes that the user made.
         * @details This slot will be invoked if the savebutton is pressed. It will save
         *          settings to the device and pushes it changes to the ESP32.
         * @author Nils Milewski (nimile/10010480)
         */
        void buttonSavePressed();

        /**
         * @brief userNameChanged This method changes the content of the user name field.
         * @details This slot will be invoked if the user name changes inside the \a UserSettings
         *          class. It will set the current text of the user name field.
         * @author Nils Milewski (nimile/10010480)
         */
        void userNameChanged(QString name);

        /**
         * @brief userWeightChanged This method changes the content of the user weight field.
         * @details This slot will be invoked if the user weight changes inside the \a UserSettings
         *          class. It will set the current text of the user weight field.
         * @author Nils Milewski (nimile/10010480)
         */
        void userWeightChanged(uint weight);

        /**
         * @brief maxWeightChanged This method changes the content of the max weight field.
         * @details This slot will be invoked if the max eight changes inside the \a UserSettings
         *          class. It will set the current text of the max weight field.
         * @author Nils Milewski (nimile/10010480)
         */
        void maxWeightChanged(uint weight);

        /**
         * @brief themeChanged This method changes the content selected index of the theme comboBox.
         * @details This slot will be invoked if the theme changes inside the \a UserSettings
         *          class. It will set the current index of the the combobox field.
         * @author Nils Milewski (nimile/10010480)
         */
        void themeChanged(QString name);

    };
}

#endif // defined(Q_OS_MAC)
#endif // MACUSERSETTINGSPAGE_H
