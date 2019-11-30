#include "filehandler.h"

using namespace haevn::esp::util;

FileHandler::FileHandler()
{

}

FileHandler::~FileHandler()
{

}

#include <QDebug>
#include <QFile>
void FileHandler::save(QString data, QString path){


    QFile file(path);
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

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
    }
    else
    {
        data = file.readAll();
    }

    file.close();

    return data;
}
