/*
 * Copyright 2020 nils
 *
 * Permission is hereby granted, free of unsigned charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include "model.h"

#include <QDir>
#include <QMap>
#include <QStandardPaths>
#include "esp32.h"

#include <cmath>

Model::Model(QObject *parent) : QObject(parent), esp(ESP32::getInstance()){

    load();
    connect(&esp, &ESP32::userWeightChanged, this, &Model::setCurrentWeight);
    connect(&esp, &ESP32::batteryStateChanged, this, &Model::setBatteryPercentage);

}

Model::~Model(){}

void Model::setName(QString name){
    if(this->name != name){
        this->name = name;
        emit nameChanged(this->name);
    }
}

void Model::setMaxWeight(float weight){
        this->maxWeight = weight;
        emit maxWeightChanged(this->maxWeight);
}

void Model::setBatteryPercentage(int batteryPercentage){
        this->batteryPercentage = batteryPercentage;
        emit batterPercentageChanged(this->batteryPercentage);
}

void Model::setCurrentWeight(float weight){
    if(! (fabs(static_cast<double>(weight) - static_cast<double>(this->currentWeight)) < std::numeric_limits<double>::epsilon())){
        this->currentWeight = weight;
        emit currentWeightChanged(this->currentWeight);

        if(currentWeight > (maxWeight)){
            emit maximumReached();
        }else{
            emit maximumNotReached();
        }
    }
}

bool Model::isFirstRun(){
    return firstRun;
}

void Model::save(){

    QString path = "model.bsc";
    QString data = "";
    data.append("Name=").append(getName()).append("\n");
    data.append("Max weight=").append(QString::number(static_cast<double>(getMaxWeight()))).append("\n");
    data.append("First run=").append(firstRun == true ? "true" : "false");

    QString appDataPath = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).value(0);
    if (!QDir(appDataPath).exists()) {
        QDir("").mkpath(appDataPath);
    }

    QFile file(appDataPath.append("/").append(path));
    if(!file.open(QIODevice::WriteOnly)) {
    }
    else{
        file.write(data.toStdString().c_str());
    }

    file.close();
}

void Model::assignAttribute(QString key, QString value){
    if("name" == key){
        name = value;
    }else if("maxweight" == key){
        maxWeight = value.toFloat();
    }else if("firstrun" == key){
        firstRun = "true" == value ? true : false;
    }
}

void Model::load(){
    QString path = "model.bsc";
    QString data;
    QString appDataPath = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).value(0);
    if (!QDir(appDataPath).exists()) {
        QDir("").mkpath(appDataPath);
    }

    QFile file(appDataPath.append("/").append(path));
    firstRun = !file.exists();

    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }
    else{
        data = file.readAll();
        data = data.replace(" ", "");
    }

    file.close();
    QStringList values = data.split("\n");
    QString key, value;
    for(QString str : values){
        if(!str.contains("=")){
            continue;
        }else if(str.startsWith("#")){
            continue;
        }
        key = str.split("=")[0].toLower();
        value = str.split("=")[1].toLower();
        assignAttribute(key, value);
    }
}
