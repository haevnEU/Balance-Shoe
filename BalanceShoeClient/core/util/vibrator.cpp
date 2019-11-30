#include "vibrator.h"


#include <QDebug>

using namespace haevn::esp::util;

Vibrator::Vibrator(QObject *parent) : QObject(parent){

#if 0 // defined(Q_OS_ANDROID)
    QAndroidJniObject vibroString = QAndroidJniObject::fromString("vibrator");
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject appctx = activity.callObjectMethod("getApplicationContext","()Landroid/content/Context;");
    vibratorService = appctx.callObjectMethod("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;", vibroString.object<jstring>());
#endif
}

#if 0 //defined(Q_OS_ANDROID)

void Vibrator::vibrateStop(){
    if (vibratorService.isValid()) {
        vibratorService.callMethod<void>("cancel");
    } else {
        qDebug() << "No vibrator service available";
    }
}

void Vibrator::vibrate(){
   vibrate(600000);
}

void Vibrator::vibrate(int milliseconds) {
    if (vibratorService.isValid()) {
        jlong ms = milliseconds;
        vibratorService.callMethod<void>("vibrate", "(J)V", ms);
    } else {
        qDebug() << "No vibrator service available";
    }
}

#else


void Vibrator::vibrateStop(){

}

void Vibrator::vibrate(){
   vibrate(600000);
}

void Vibrator::vibrate(int milliseconds) {
    Q_UNUSED(milliseconds);
}


#endif
