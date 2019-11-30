#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H



/* Qt system */
#include <QInputMethod>     // Used to access touch events
#include <QGuiApplication>  // Used to access virtual keyboard

/* Qt widgets */
#include <QLineEdit>    // Used as base class

/* Project includes */
#include "../util/utils.h"  // Used to access project utilities

#if defined(Q_OS_ANDROID)

namespace haevn::esp::widgets{
    class CustomLineEdit : public QLineEdit{

        Q_OBJECT

    public methods:

        CustomLineEdit(QWidget* parent = nullptr);

    signals:

        void focussed(bool hasFocus);

    protected methods:

        virtual void focusInEvent(QFocusEvent *e);

        virtual void focusOutEvent(QFocusEvent *e);
    };
}

#endif // defined(Q_OS_ANDROID)

#endif // CUSTOMLINEEDIT_H
