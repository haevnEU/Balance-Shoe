/**
 * @file vibrator.h
 * @brief Provides the access to the device vibration
 * @details This file contains the access to a vibration of target device
 * @author Nils Milewski (nimile/10010480)
 * @bug Currently the JNI interface wont work
 * details:
 * In file included from ../Balance-Shoe/BalanceShoeClient/core/pages/usersettings.cpp:2:
 * In file included from ../Balance-Shoe/BalanceShoeClient/core/pages/windowhandler.h:17:
 * In file included from ../Balance-Shoe/BalanceShoeClient/core/pages/mainpage.h:23:
 * In file included from ../Balance-Shoe/BalanceShoeClient/core/pages/../util/vibrator.h:16:
 * In file included from ../../../Qt/5.13.1/android_arm64_v8a/include/QtAndroidExtras/QAndroidJniEnvironment:1:
 * In file included from ../../../Qt/5.13.1/android_arm64_v8a/include/QtAndroidExtras/qandroidjnienvironment.h:43:
 * /Users/nils/Library/Android/ndk/sysroot/usr/include/jni.h:977:61: error: expected expression
 * { return functions->RegisterNatives(this, clazz, methods, nMethods); }
 */

#ifndef VIBRATOR_H
#define VIBRATOR_H

#include "utils.h"

#include <QObject>
#if 0 //defined(Q_OS_ANDROID)
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#endif

namespace haevn::esp::util{

    class Vibrator : public QObject{

        Q_OBJECT

    public static_methods:
        /**
         * @brief getVibrator This static method returns the singleton object of the class.
         * @details This static method initializes a new instance of this class iff none exist
         *          otherwise the existing instance will be returned.
         *          This singleton implementation will provide automatic destruction if the
         *          application exits.
         * @author Nils Milewski (nimile/10010480)
         */
        static Vibrator& getVibrator(){
            static Vibrator instance;
            return instance;
        }

    private attributes:

    #if 0 //defined(Q_OS_ANDROID)
        /**
         * @brief vibratorService This attribute contains the vibrator service of an android device
         */
        QAndroidJniObject vibratorService;
    #endif

    private methods:

        /**
         * @brief Vibrator This constructor initializes a new instance of this class.
         * @details This constructor creates all required steps to access the device vibration.<br>
         *          Under android it will setup the JNI interface.<br>
         *          Under desktop it will do nothing.<br>
         * @author Nils Milewski (nimile/10010480)
         */
        Vibrator(QObject* parent = nullptr);

    public slots:

        /**
         * @brief vibrate This method let the device vibrate for a specific amount of time
         * @details This method calls the vibrate method of the device with milliseconds as argument.
         * @param milliseconds Duration of the vibration.
         * @author Nils Milewski (nimile/10010480)
         */
        void vibrate(int milliseconds);

        /**
         * @brief vibrate This method let the device vibrate for a long time.
         * @details This method calls the \a vibrate method with a long duration
         * @author Nils Milewski (nimile/10010480)
         */
        void vibrate();

        /**
         * @brief vibrateStop This method stops the device vibration.
         * @details This method will stop the vibration of the device.
         * @author Nils Milewski (nimile/10010480)
         */
        void vibrateStop();
    };
}
#endif // VIBRATOR_H
