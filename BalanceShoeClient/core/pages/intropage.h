#ifndef INTROPAGE_H
#define INTROPAGE_H

/* Qt widgets */
#include <QWidget>      // Used as base class
#include <QLabel>
#include <QPushButton>

/* Qt layout */
#include <QVBoxLayout>  // Used as primary layout
#include <QSpacerItem>

/* Project includes */
#include "../util/utils.h"          // Used to access project utilities
namespace haevn::esp::pages{
    class IntroPage : public QWidget{

        Q_OBJECT

    public methods:

        IntroPage(QWidget* parent = nullptr);

    public slots:

        void buttonStartSetupPressed();

    };
}
#endif // INTROPAGE_H
