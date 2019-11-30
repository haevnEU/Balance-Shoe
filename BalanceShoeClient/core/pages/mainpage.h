#ifndef MAINPAGE_H
#define MAINPAGE_H

/* Qt widgets */
#include <QWidget>          // Used as base class
#include <QLabel>
#include <QSpacerItem>      // Used to insert space between UI elements
#include <QPushButton>

/* Qt layout */
#include <QVBoxLayout>      // Used as primary layout

/* User inccldues */
#include "../util/vibrator.h"       // Used to vibrate the device
#include "../util/utils.h"          // Used to access project utilities

namespace haevn::esp::pages{
    class MainPage : public QWidget{

        Q_OBJECT

    private attributes:

        util::Vibrator* vib;

        QPushButton* buttonOff;

        QPushButton* buttonOn;

        QPushButton* buttonSettings;

        QPushButton* buttonStat;

    public methods:

        MainPage(QWidget* parent = nullptr);

    private slots:

        void buttonOnPressed();

        void buttonOffPressed();

        void buttonShowUserSettings();

        void buttonStatPressed();
    };
}
#endif // MAINPAGE_H
