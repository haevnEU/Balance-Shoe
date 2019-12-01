/**
 * @file androidsettingspage.h
 * @brief Provides the logic to handle the developer settings
 * @details This file contains the logic for the developer settings.
 * @author Nils Milewski (nimile/10010480)
 */
#ifndef ANDROIDSETTINGSPAGE_H
#define ANDROIDSETTINGSPAGE_H

#include <QObject>

#if defined(Q_OS_ANDROID)

/* QT widgets */
#include <QWidget>      // Used as base class
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QSpacerItem>

/* Qt layout */
#include <QGridLayout>  // Used as primary layout

/* User includes */
#include "util/utils.h"              // Used to access project utilities
#include "widgets/customlineedit.h"  // Used to enable touch interaction for QLineEdit

namespace haevn::esp::pages{

    /**
     * @brief The AndroidSettingsPage class
     * @details This class should only be available during the development of the project.
     *          Later it should be placed in a separate support app therefore no documentation
     *          will be provided.
     * @author Nils Milewski (nimile/10010480)
     */
    class AndroidSettingsPage : public QWidget{

        Q_OBJECT

    private attributes:

        widgets::CustomLineEdit* inputBAUD;

        widgets::CustomLineEdit* inputDOutPin;

        widgets::CustomLineEdit* inputSCKPint;

        widgets::CustomLineEdit* inputReferenceWeight;

        widgets::CustomLineEdit* inputTolerance;

        widgets::CustomLineEdit* inputScaleValue;

        QPushButton* buttonSaveSetup;

        QFont font;

    public methods:

        AndroidSettingsPage(QWidget* parent = nullptr);

        QLayout *createLayout();

    private slots:

        void buttonBackPressed();

        void buttonLottoPressed();

        void buttonSavePressed();
    };
}

#endif // defined(Q_OS_ANDROID)

#endif // ANDROIDSETTINGSPAGE_H
