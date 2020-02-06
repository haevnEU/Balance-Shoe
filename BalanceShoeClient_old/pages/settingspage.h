/**
 * @file settingspage.h
 * @brief This file wraps different UI depending on compiler
 * @author Nils Milewski (nimile/10010480)
 */

#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QObject>

#if defined(Q_OS_ANDROID)
#include "Android/androidsettingspage.h"
#define SettingsPage AndroidSettingsPage
#elif defined(Q_OS_IOS)
#include "ios/iossettingspage.h"
#define SettingsPage IosSettingsPage
#elif defined(Q_OS_MACOS)
#include "Mac/macsettingspage.h"
#define SettingsPage MacSettingsPage
#elif defined(Q_OS_WINDOWS)
#include "windows/winsettingspage.h"
#define SettingsPage WinSettingsPage
#endif

#endif // SETTINGSPAGE_H
