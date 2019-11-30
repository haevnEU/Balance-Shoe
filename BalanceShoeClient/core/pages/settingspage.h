#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

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
#include "../util/utils.h"              // Used to access project utilities
#if defined(Q_OS_ANDROID)               // Next includes are only used when android is build
#include "../widgets/customlineedit.h"  // Used to enable touch interaction for QLineEdit
#endif

namespace haevn::esp::pages{
    class SettingsPage : public QWidget{

        Q_OBJECT

    private attributes:

    #if defined(Q_OS_ANDROID)

        widgets::CustomLineEdit* inputBAUD;

        widgets::CustomLineEdit* inputDOutPin;

        widgets::CustomLineEdit* inputSCKPint;

        widgets::CustomLineEdit* inputReferenceWeight;

        widgets::CustomLineEdit* inputTolerance;

        widgets::CustomLineEdit* inputScaleValue;

        QPushButton* buttonSaveSetup;

    #else
        QLineEdit* inputName;
        QLineEdit* inputWeight;
        QLineEdit* inputMaxWeight;
        QPushButton* buttonSaveSettings;

        QCheckBox* checkBoxDebug;
        QLineEdit* inputBAUD;
        QLineEdit* inputDOutPin;
        QLineEdit* inputSCKPint;
        QLineEdit* inputReferenceWeight;
        QLineEdit* inputTolerance;
        QLineEdit* inputScaleValue;

        QComboBox* comboBoxTheme;
        QPushButton* buttonSaveSetup;

    #endif

        QFont font;

    public methods:

        SettingsPage(QWidget* parent = nullptr);

        QLayout *createLayout();

    private slots:

        void buttonBackPressed();

        void buttonLottoPressed();

        void buttonSavePressed();
    };
}
#endif // SETTINGSPAGE_H
