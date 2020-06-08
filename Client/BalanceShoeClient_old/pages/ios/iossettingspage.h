/**
 * @file iossettingspage.h
 * @brief Provides the logic to handle the developer settings
 * @details This file contains the logic for the developer settings.
 * @author Nils Milewski (nimile/10010480)
 */
#ifndef IOSSETTINGSPAGE_H
#define IOSSETTINGSPAGE_H

#include <QObject>

#if defined(Q_OS_IOS)

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
     * @brief The IosSettingsPage class
     * @details This class should only be available during the development of the project.
     *          Later it should be placed in a separate support app therefore no documentation
     *          will be provided.
     * @author Nils Milewski (nimile/10010480)
     */
    class IosSettingsPage : public QWidget{

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

        IosSettingsPage(QWidget* parent = nullptr);

        QLayout *createLayout();

    private slots:

        void buttonBackPressed();

        void buttonLottoPressed();

        void buttonSavePressed();
    };
}

#endif // defined(Q_OS_Ios)

#endif // IosSETTINGSPAGE_H
