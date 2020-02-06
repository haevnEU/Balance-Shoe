/**
 * @file intropage.h
 * @brief This file wraps different UI depending on compiler
 * @author Nils Milewski (nimile/10010480)
 */
#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QObject>

#if defined(Q_OS_ANDROID)
#include "Android/androidintropage.h"
#define IntroPage AndroidIntroPage
#elif defined(Q_OS_IOS)
#include "ios/iosintropage.h"
#define IntroPage IosIntroPage
#elif defined(Q_OS_MACOS)
#include "Mac/macintropage.h"
#define IntroPage MacIntroPage
#elif defined(Q_OS_WINDOWS)
#include "windows/winintropage.h"
#define IntroPage WinIntroPage
#endif // defined(Q_OS_ANDROID)

#endif // INTROPAGE_H
