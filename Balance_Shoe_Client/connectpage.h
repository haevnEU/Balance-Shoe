
#ifndef CONNECTPAGE_H
#define CONNECTPAGE_H

#include "model.h"

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include "circleprogressbar.h"
#include "arrowbutton.h"
class ConnectPage : public QWidget{

    Q_OBJECT

private:

    CircleProgressBar* progressDeviceSearch;
    CircleProgressBar* progressDeviceFound;
    CircleProgressBar* progressDeviceTested;

    QPushButton* btSearch;
    //QPushButton* btNext;
    ArrowButton* btNext;
    Model& model;
    ESP32& esp;

public:
    explicit ConnectPage(QString text, bool isSettingsPage = false, QFont* font = nullptr, QWidget *parent = nullptr);
    ~ConnectPage();

    void hide();
    void show();

public slots:
    void buttonNextPressed();
    void buttonSearchPressed();
signals:
    void deviceDisconnected();
    void deviceConnected();
};

#endif // CONNECTPAGE_H
