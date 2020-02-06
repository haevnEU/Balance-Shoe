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
#ifndef ESP32_H
#define ESP32_H

#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QObject>

enum ESP32Characteristics{
    userWeight,
    userMaxWeight,
    batteryLevel
};

struct BLEService{
    QString UUID;
    QStringList characteristics;
};

class ESP32 : public QObject{

    Q_OBJECT

public:
    static ESP32& getInstance(){
        static ESP32 instance;
        return instance;
    }

private:
   QBluetoothDeviceInfo* device;
   QLowEnergyController* deviceController;
   QBluetoothDeviceDiscoveryAgent* discoveryAgent;
   const QString deviceUUID = QString("3FA5B4BC-4F85-4905-A2AD-3713CF11E5F8").toLower();

   BLEService requiredServices[3];
   QLowEnergyService* userService;

   QLowEnergyCharacteristic* user_weight;
   QLowEnergyCharacteristic* user_max_loaded_weight;

   int charCounter = 0;
   bool deviceConnected_m = false;


private:
   explicit ESP32(QObject *parent = nullptr);
   QString log;

public:
    ~ESP32();

    void createCharacteristic(QLowEnergyCharacteristic &c);
    void subscribeNotification(QLowEnergyCharacteristic &c);

    bool isDeviceConnected(){
        return deviceConnected_m;
    }

signals:
    void connected();
    void disconnected();
    void serviceDiscoveryStarted();
    void serviceDiscovered();
    void servicesFailed();
    void servicesFound();
    void serviceTested();

    void deviceReady();


    void deviceFound();
    void deviceNotFound();

    void serviceFound();
    void serviceNotFound();
    void characteristicsFound();
    void characteristicsNotFound();

    void userWeightChanged(float);
    void batteryStateChanged(int);

    void deviceConnected();
    void deviceDisconnected();
public slots:
    void discover();
    void send(ESP32Characteristics which, QByteArray data);
    unsigned int read(ESP32Characteristics which);

private slots:
    void connectTo();
    void discoveryFinished();
    void serviceDiscoverFinished();
    void characteristicFound();
};

#endif // ESP32_H
