QT += core gui
QT += widgets
#QT += virtualkeyboard

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android: QT += androidextras

DISTFILES += \
    android-sources/AndroidManifest.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

RESOURCES += \
    themes.qrc

HEADERS += \
    core/pages/intropage.h \
    core/pages/mainpage.h \
    core/pages/settingspage.h \
    core/pages/usersettings.h \
    core/pages/windowhandler.h \
    core/util/filehandler.h \
    core/util/utils.h \
    core/util/vibrator.h \
    core/widgets/customlineedit.h

SOURCES += \
    core/main.cpp \
    core/pages/intropage.cpp \
    core/pages/mainpage.cpp \
    core/pages/settingspage.cpp \
    core/pages/usersettings.cpp \
    core/pages/windowhandler.cpp \
    core/util/filehandler.cpp \
    core/util/vibrator.cpp \
    core/widgets/customlineedit.cpp
