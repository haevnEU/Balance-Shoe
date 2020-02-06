/**
 * @file mainpage.h
 * @brief This file wraps different UI depending on compiler
 * @author Nils Milewski (nimile/10010480)
 */

#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QObject>

#if defined(Q_OS_ANDROID)
#include "Android/androidmainpage.h"
#define MainPage AndroidMainPage
#elif defined(Q_OS_IOS)
#include "ios/iosmainpage.h"
#define MainPage IosMainPage
#elif defined(Q_OS_MACOS)
#include "Mac/macmainpage.h"
#define MainPage MacMainPage
#elif defined(Q_OS_WINDOWS)
#include "windows/winmainpage.h"
#define MainPage WinMainPage
#endif


#endif // MAINPAGE_H
