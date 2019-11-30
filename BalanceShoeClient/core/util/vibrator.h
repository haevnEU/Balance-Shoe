#ifndef VIBRATOR_H
#define VIBRATOR_H

#include "utils.h"

#include <QObject>
#if 0 // defined(Q_OS_ANDROID)
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#endif

namespace haevn::esp::util{
    class Vibrator : public QObject{

        Q_OBJECT

    public methods:
        explicit Vibrator(QObject *parent = 0);
    public slots:
        void vibrate(int milliseconds);
        void vibrate();
        void vibrateStop();
    private:
    #if 0 //defined(Q_OS_ANDROID)
        QAndroidJniObject vibratorService;
    #endif
    };
}
#endif // VIBRATOR_H
