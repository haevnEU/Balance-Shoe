QT       += core gui
QT += bluetooth
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    circleprogressbar.cpp \
    connectpage.cpp \
    esp32.cpp \
    main.cpp \
    mainpage.cpp \
    model.cpp \
    officon.cpp \
    pagehandler.cpp \
    settingspage.cpp \
    welcomepage.cpp

HEADERS += \
    circleprogressbar.h \
    connectpage.h \
    esp32.h \
    mainpage.h \
    model.h \
    officon.h \
    pagehandler.h \
    settingspage.h \
    welcomepage.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    res/baseline_bluetooth_searching_black.png \
    res/baseline_bluetooth_searching_white.png \
    res/baseline_check_circle_outline_black.png \
    res/baseline_check_circle_outline_white.png \
    res/baseline_error_outline_black.png \
    res/baseline_error_outline_white.png \
    res/baseline_highlight_off_black.png \
    res/baseline_highlight_off_white.png \
    res/baseline_keyboard_backspace_black.png \
    res/baseline_keyboard_backspace_white.png \
    res/baseline_navigate_before_black.png \
    res/baseline_navigate_before_white.png \
    res/baseline_navigate_next_black.png \
    res/baseline_navigate_next_white.png \
    res/baseline_power_settings_new_black.png \
    res/baseline_power_settings_new_white.png \
    res/baseline_schedule_black.png \
    res/baseline_schedule_white.png
