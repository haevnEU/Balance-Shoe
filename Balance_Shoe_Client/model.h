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
#ifndef MODEL_H
#define MODEL_H

#include "esp32.h"

#include <QObject>

class Model : public QObject{

    Q_OBJECT

public:

    static Model& getInstance(){
        static Model instance;
        return instance;
    }

private:
    bool firstRun = true;
    bool autoConnect = true;

    QString name;
    float maxWeight;
    int batteryPercentage;
    float currentWeight;

    explicit Model(QObject *parent = nullptr);
    ESP32& esp;

public:

        float getMaxWeight(){
            return maxWeight;
        }

        int getBatteryPercentage(){
            return batteryPercentage;
        }

        float getCurrentWeight(){
            return currentWeight;
        }

        QString getName(){
            return name;
        }

        bool autoReconnect(){
            return autoConnect;
        }

        void autoReconnect(bool connect);

        void save();
        void load();
        bool isFirstRun();
        ~Model();
signals:
        void currentWeightChanged(float weight);

        void maximumReached();
        void maximumNotReached();

        void nameChanged(QString newName);
        void maxWeightChanged(float newMaxWeight);
        void batterPercentageChanged(int batteryPercentage);
public slots:

        void setCurrentWeight(float weight);
        void setName(QString name);
        void setMaxWeight(float weight);
        void setBatteryPercentage(int batteryPercentage);
};

#endif // MODEL_H
