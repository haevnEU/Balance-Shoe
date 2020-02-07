/*
 * Copyright 2020 nils
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
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
#include "esp32.h"

#include <QBluetoothUuid>
#include <QTimer>
#include "model.h"

ESP32::ESP32(QObject *parent) : QObject(parent){

    requiredServices[1].UUID = QString("5A16B114-07C9-4FB4-8028-555DA52F0A3E").toLower();
    requiredServices[1].characteristics.append(QString("3845372F-32AC-443F-A397-17C24B97A4D3").toLower()); // user weight
    requiredServices[1].characteristics.append(QString("A896D9F3-F8E8-4343-98BA-04C1F71F1FBD").toLower()); // user max weight

    requiredServices[2].UUID = "E9CADE94-f98B-45F4-A987-4ADC311737B7";
    requiredServices[2].characteristics.append("13b78f5c-08fb-49a0-be7e-bf956e302d7b");

    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &ESP32::discoveryFinished);


    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, [=](const QBluetoothDeviceInfo &info){
        qDebug() << info.name() << " " << info.address() << " " << info.deviceUuid();
        if(info.name().toUpper().contains("BALANCE")){
            this->device = new QBluetoothDeviceInfo(info);
            deviceController = new QLowEnergyController(*this->device);
            discoveryAgent->stop();
            emit deviceFound();
            return;
        }
    });

    connect(this, &ESP32::deviceFound, this, &ESP32::connectTo);
}

ESP32::~ESP32(){

    discoveryAgent->stop();
    delete discoveryAgent;
}

void ESP32::discover(){
    discoveryAgent->start();
}

void ESP32::discoveryFinished(){
    QBluetoothUuid deviceUUID(this->deviceUUID);
    for(QBluetoothDeviceInfo device : discoveryAgent->discoveredDevices()){
        qDebug() << device.name() << " " << device.deviceUuid();
        if(device.name().toUpper().contains("BALANCE")){
            this->device = new QBluetoothDeviceInfo(device);
            deviceController = new QLowEnergyController(*this->device);
            emit deviceFound();
            return;
        }

    }
    emit deviceNotFound();
}

void ESP32::connectTo(){

    QObject::connect(deviceController, &QLowEnergyController::discoveryFinished,this, &ESP32::serviceDiscoverFinished);

    QObject::connect(deviceController, &QLowEnergyController::connected,this, [=]{
        deviceController->discoverServices();
        deviceConnected_m = true;
        emit deviceConnected();
    });

    QObject::connect(deviceController, &QLowEnergyController::disconnected, this, [=]{
        deviceConnected_m = false;
        emit deviceDisconnected();
        if(Model::getInstance().autoReconnect()){
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, [=]{
                deviceController->connectToDevice();
            });
            timer->start(5*1000); //time specified in ms
        }
    });

    deviceController->connectToDevice();
}

void ESP32::serviceDiscoverFinished(){
    for(QBluetoothUuid uuid : deviceController->services()){
       if(QBluetoothUuid(requiredServices[1].UUID) == uuid){
            // User
            userService = deviceController->createServiceObject(uuid);
       }else{
            qDebug() << "UNKWON UUID: " <<  uuid;
        }
    }

    if(nullptr !=  userService){// && nullptr != batteryService){
        emit serviceFound();
    }

    if(userService->state() == QLowEnergyService::DiscoveryRequired){
        userService->discoverDetails();
        connect(userService, &QLowEnergyService::stateChanged, this, [=](QLowEnergyService::ServiceState state){
            if(QLowEnergyService::ServiceState::ServiceDiscovered == state){
                for(QLowEnergyCharacteristic ch : userService->characteristics()){
                    charCounter++;
                    createCharacteristic(ch);
                    subscribeNotification(ch);
                }
                characteristicFound();
            }
        });
    }

}

void ESP32::subscribeNotification(QLowEnergyCharacteristic& c){
    //PreCondition: service details already discovered
          if (!c.isValid())
              return;

          QLowEnergyDescriptor notification = c.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
          if (!notification.isValid())
              return;

          // establish hook into notifications
          connect(userService, &QLowEnergyService::characteristicChanged,
                  this, [=](QLowEnergyCharacteristic c,QByteArray d){
                if(c == *user_weight){
                   /* qDebug() << "Received: " << d.toUInt() << QString::number(d.toUInt()) << " " << static_cast<unsigned char>(d[0])
                            << " " << static_cast<unsigned char>(d[1])
                            << " " << static_cast<unsigned char>(d[2]);
                   */

                    float userWeight = (static_cast<float>(d[0]) * 100) +  static_cast<float>(d[1]);
                    userWeight /= 100;
                    int battery = d[2];

                   // qDebug() << userWeight;
                 //   qDebug() << battery;

                    emit userWeightChanged(userWeight);
                    emit batteryStateChanged(battery);
                }
          });

          // enable notification
          userService->writeDescriptor(notification, QByteArray::fromHex("0100"));

          // disable notification
          //service->writeDescriptor(notification, QByteArray::fromHex("0000"));
}

void ESP32::createCharacteristic(QLowEnergyCharacteristic& c){

    QString uuid = c.uuid().toString().toUpper().replace("{", "").replace("}", "");
    log.append(uuid).append("##");
    if(uuid.startsWith("3845372F")){//-32AC-443F-A397-17C24B97A4D3"){
        user_weight = new QLowEnergyCharacteristic(c);
    }else if(uuid.startsWith("A896D9F3")){//-F8E8-4343-98BA-04C1F71F1FBD"){
        user_max_loaded_weight= new QLowEnergyCharacteristic(c);
    }else {}
    qDebug() << log;
}

void ESP32::characteristicFound(){
    qDebug() << charCounter;
    if(charCounter >= 2){
        emit characteristicsFound();
    }
}

void ESP32::send(ESP32Characteristics which, QByteArray data){
    if(!deviceConnected_m){
        return;
    }
    switch(which){
        case ESP32Characteristics::userWeight:
            userService->writeCharacteristic(*user_weight, data);
            break;
        case ESP32Characteristics::userMaxWeight:
            userService->writeCharacteristic(*user_max_loaded_weight, data);
            break;

        case ESP32Characteristics::batteryLevel:
            break;
    }
}

unsigned int ESP32::read(ESP32Characteristics which){
    if(!deviceConnected_m){
        return 0;
    }
    switch(which){
        case ESP32Characteristics::userWeight:
            if(user_weight == nullptr) break;
            userService->readCharacteristic(*user_weight);
            return user_weight->value()[0];
        case ESP32Characteristics::userMaxWeight:
            if(user_max_loaded_weight == nullptr) break;
                userService->readCharacteristic(*user_max_loaded_weight);
                return user_max_loaded_weight->value()[0];
        case ESP32Characteristics::batteryLevel:break;
    }

    return 0xFF;
}
