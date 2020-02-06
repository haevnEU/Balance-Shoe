/**
 * @file Winintropage.h
 * @brief Provides the logic to handle intro page
 * @details This file contains the logic for the intro page
 *          At this page it is possible to start the setup proccess.
 * @author Nils Milewski (nimile/10010480)
 */
#ifndef WININTROPAGE_H
#define WININTROPAGE_H

#include <QObject>

#if defined(Q_OS_WINDOWS)

/* Qt widgets */
#include <QWidget>      // Used as base class
#include <QLabel>
#include <QPushButton>

/* Qt layout */
#include <QVBoxLayout>  // Used as primary layout
#include <QSpacerItem>

/* Project includes */
#include "util/utils.h"          // Used to access project utilities

namespace haevn::esp::pages{

    /**
     * @brief The WinIntroPage class This class provides  the logic to handle intro page
     * @details This class contains the logic for the intro page
     *          At this page it is possible to start the setup proccess.
     * @author Nils Milewski (nimile/10010480)
     */
    class WinIntroPage : public QWidget{

        Q_OBJECT

    public methods:

        /**
         * @brief WinIntroPage This is a constructor.
         * @details This constructor initializes all required attributes and the UI.
         *          It also connects all required signals to their equivalent slot.
         * @param parent This is the parrent object of this page, default nullptr.
         * @author Nils Milewski (nimile/10010480)
         */
        WinIntroPage(QWidget* parent = nullptr);

    public slots:

        /**
         * @brief buttonStartSetupPressed This method invokes the setup proccess.
         * @details This slot will be invoked if the buttonStartSetup is pressed.
         *          It will invoke the setup proccess.
         * @author Nils Milewski (nimile/10010480)
         */
        void buttonStartSetupPressed();

    };
}

#endif // defined(Q_OS_WINDOWS)

#endif // WinINTROPAGE_H
