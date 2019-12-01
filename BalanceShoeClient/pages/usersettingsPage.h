/**
 * @file usersettings.h
 * @brief This file wraps different UI depending on compiler
 * @author Nils Milewski (nimile/10010480)
 */

#ifndef USERSETTINGSPAGE_H
#define USERSETTINGSPAGE_H

#include <QObject>

#if defined(Q_OS_ANDROID)
#include "Android/androidusersettingspage.h"
#define UserSettingsPage AndroidUserSettingsPage
#elif defined(Q_OS_IOS)
#include "ios/iosusersettingspage.h"
#define UserSettingsPage IosUserSettingsPage
#elif defined(Q_OS_MACOS)
#include "Mac/macusersettingspage.h"
#define UserSettingsPage MacUserSettingsPage
#elif defined(Q_OS_WINDOWS)
#include "windows/winusersettingspage.h"
#define UserSettingsPage WinUserSettingsPage
#endif
#endif // USERSETTINGSPAGE_H
