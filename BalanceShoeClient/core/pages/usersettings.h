#ifndef USERSETTINGS_H
#define USERSETTINGS_H

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
#include "../util/utils.h"              // Used to access project utilities
#include "../widgets/customlineedit.h"  // Used to enable touch interaction for QLineEdit

namespace haevn::esp::pages{
    class UserSettings: public QWidget{

        Q_OBJECT

    private:

    #if defined(Q_OS_ANDROID)
        widgets::CustomLineEdit* inputName;
        widgets::CustomLineEdit* inputWeight;
        widgets::CustomLineEdit* inputMaxWeight;
        QComboBox* comboBoxTheme;

        QPushButton* buttonSaveSettings;
    #else
        QLineEdit* inputName;
        QLineEdit* inputWeight;
        QLineEdit* inputMaxWeight;
        QComboBox* comboBoxTheme;

        QPushButton* buttonSaveSettings;

    #endif

        QFont font;

    public:
        UserSettings(QWidget* parent = nullptr);
        QLayout *createLayout();

    public slots:
        void buttonBackPressed();
        void currentIndexChanged(int index);
        void buttonSavePressed();
    };
}
#endif // USERSETTINGS_H
