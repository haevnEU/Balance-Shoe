
#include "usersettings.h"

#include <util/filehandler.h>

using namespace haevn::esp::core;

UserSettings::UserSettings(){
    load();
    themes.append("AMOLED");
    themes.append("Aqua");
    themes.append("ConsoleStyle");
    themes.append("ElegantDark");
    themes.append("MaterialDark");
    themes.append("Ubuntu");
}

void UserSettings::load(){
    QString rawData = util::FileHandler::getFileHandler().read(fileName);

    QStringList entries = rawData.split("\n");
    if(entries.size() >= 4){
        setUserName(entries[0]);
        setUserWeight(entries[1].toUInt());
        setMaxWeight(entries[2].toUInt());
        setThemeName(entries[3]);
    }
}

void UserSettings::save(){
    QString data;
    data.append(getUserName()).append("\n")
        .append(QString::number(getUserWeight())).append("\n")
        .append(QString::number(getMaxWeight())).append("\n")
        .append(getThemeName());
    util::FileHandler::getFileHandler().save(data, fileName);
}

QString UserSettings::getUserName() const{
    return userName;
}

void UserSettings::setUserName(const QString &value){
    userName = value;
    emit userNameChanged(value);
}

uint UserSettings::getUserWeight() const{
    return userWeight;
}

void UserSettings::setUserWeight(uint value){
    userWeight = value;
    emit userWeightChanged(value);
}

uint UserSettings::getMaxWeight() const{
    return maxWeight;
}

void UserSettings::setMaxWeight(uint value){
    maxWeight = value;
    emit maxWeightChanged(value);
}

QString UserSettings::getThemeName() const{
    return themeName;
}

void UserSettings::setThemeName(const QString &value){
    themeName = value;
    emit themeChanged(value);
}
void UserSettings::setThemeName(int index){
    themeName = indexToThemeName(index);
    emit themeChanged(themeName);
}

QStringList UserSettings::getThemes(){
    return themes;
}

QString UserSettings::indexToThemeName(int index){
    return themes.at(index);
}

int UserSettings::themeNameToIndex(QString name){
    return themes.indexOf(name);
}
