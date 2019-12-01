#include "filehandler.h"

using namespace haevn::esp::util;

FileHandler::FileHandler()
{

}

FileHandler::~FileHandler()
{

}

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
void FileHandler::save(QString data, QString path){

    QString appDataPath = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).value(0);
    if (!QDir(appDataPath).exists()) {
        QDir("").mkpath(appDataPath);
    }

    QFile file(appDataPath.append("/").append(path));
    if(!file.open(QIODevice::WriteOnly)) {
    }
    else
    {
        data = file.write(data.toStdString().c_str());
    }

    file.close();
}

QString FileHandler::read(QString path){
    QString data;
    QString appDataPath = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).value(0);
    if (!QDir(appDataPath).exists()) {
        QDir("").mkpath(appDataPath);
    }

    QFile file(appDataPath.append("/").append(path));
    if(!file.open(QIODevice::ReadOnly)) {
    }
    else
    {
        data = file.readAll();
    }

    file.close();

    return data;
}
