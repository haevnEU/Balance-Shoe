/**
 * @file customlineedit.h
 * @brief Provides a custom implementation of QLineEdit widget.
 * @details This file contains a derivate implementation of a QLineEdit.
 *          It is needed to use android touch interaction.
 * @author Nils Milewski (nimile/10010480)
 */

#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

/* Qt system */
#include <QInputMethod>     // Used to access touch events
#include <QGuiApplication>  // Used to access virtual keyboard

/* Qt widgets */
#include <QLineEdit>    // Used as base class

/* Project includes */
#include "../util/utils.h"  // Used to access project utilities

#if 1//defined(Q_OS_ANDROID)

namespace haevn::esp::widgets{

    /**
     * @brief CustomLineEdit class Provides a custom implementation of QLineEdit widget.
     * @details This file contains a derivate implementation of a QLineEdit.
     *          It is needed to use android touch interaction
     */
    class CustomLineEdit : public QLineEdit{

        Q_OBJECT

    public methods:

        /**
         * @brief CustomLineEdit This is a constructor.
         * @details This constructor enables the touch interaction, this widget
         *          should be used if the device has touch interaction
         * @param parent This argument is used to assign a parent to the widget
         * @author Nils Milewski (nimile/10010480)
         */
        CustomLineEdit(QWidget* parent = nullptr);

    signals:

        /**
         * @brief focussed This signal is emitted if the focus of the widget changed.
         * @param hasFocus This argument is true iff the widget gains focus
         * @author Nils Milewski (nimile/10010480)
         */
        void focussed(bool hasFocus);

    protected methods:

        /**
         * @brief focusInEvent This event is a re implentation.
         * @details This event occurres if the widget gained the focus.
         *          The focus signal will be emitted with true as argument.
         *          If a virtual keyboard is available it will be invoked.
         * @param e This argument is provided for the base implementation.
         * @author Nils Milewski (nimile/10010480)
         */
        virtual void focusInEvent(QFocusEvent *e);

        /**
         * @brief focusOutEvent This event is a re implentation.
         * @details This event occurres if the widgets loses the focus.
         *          The focus signal will be emitted with true as argument.
         *          If a virtual keyboard is available it will be invoked.
         * @param e This argument is provided for the base implementation.
         * @author Nils Milewski (nimile/10010480)
         */
        virtual void focusOutEvent(QFocusEvent *e);
    };
}

#endif // defined(Q_OS_ANDROID)
#endif // CUSTOMLINEEDIT_H
