#include "bluetoothhandler.h"
#include <qbluetoothdevicediscoveryagent.h>

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMenu>

using namespace haevn::esp::core;

BluetoothHandler::BluetoothHandler(QWidget* parent) : QDialog(parent) {

    auto layout = new QVBoxLayout;
    auto buttonLayout = new QHBoxLayout;

    auto labelName = new QLabel("Bluetooth Scanner");
    buttonScan = new QPushButton("Scan");
    buttonClear = new QPushButton("Clear");
    buttonQuit = new QPushButton("Quit");
    deviceList = new QListWidget();
    auto font = labelName->font();

    font.setPointSize(32);

    labelName->setFont(font);
    font.setPointSize(16);
    buttonScan->setFont(font);
    buttonClear->setFont(font);
    buttonQuit->setFont(font);
    font.setPointSize(12);
    deviceList->setFont(font);

    layout->addWidget(labelName);
    layout->addWidget(deviceList);

    buttonLayout->addWidget(buttonScan);
    buttonLayout->addWidget(buttonClear);
    buttonLayout->addWidget(buttonQuit);

    layout->addLayout(buttonLayout);
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    localDevice = new QBluetoothLocalDevice();

    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothHandler::deviceDiscovered);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BluetoothHandler::scanFinished);

    deviceList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(deviceList, &QListWidget::customContextMenuRequested, this, &BluetoothHandler::showPairingMenu);
    connect(localDevice, &QBluetoothLocalDevice::pairingFinished, this, &BluetoothHandler::pairingDone);

    connect(buttonScan, &QPushButton::clicked, this, &BluetoothHandler::startScan);
    connect(buttonClear, &QPushButton::clicked, deviceList, &QListWidget::clear);
    connect(buttonQuit, &QPushButton::clicked, this, &BluetoothHandler::close);
}

BluetoothHandler::~BluetoothHandler() {
    delete discoveryAgent;
    delete localDevice;
}

void BluetoothHandler::startScan() {
    discoveryAgent->start();
    buttonScan->setEnabled(false);
}

void BluetoothHandler::scanFinished() {
    buttonScan->setEnabled(true);
}

void BluetoothHandler::deviceDiscovered(const QBluetoothDeviceInfo& deviceInfo) {
    QString device = QString("%1 %2").arg(deviceInfo.address().toString()).arg(deviceInfo.name());
    QList<QListWidgetItem*> itemList = deviceList->findItems(device, Qt::MatchExactly);

    if(itemList.empty()) {
        QListWidgetItem* item = new QListWidgetItem(device);
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(deviceInfo.address());

        if(pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired) {
            item->setTextColor(QColor(Qt::green));
        } else {
            item->setTextColor(QColor(Qt::blue));
        }
        deviceList->addItem(item);
    }
}

void BluetoothHandler::showPairingMenu(const QPoint &pos) {

    if(deviceList->count() == 0) {
        return;
    }

    QMenu menu(this);
    QAction* pairAction = menu.addAction("Pair...");
    QAction* unpairAction = menu.addAction("Unpair...");
    QAction* chosenAction = menu.exec(deviceList->viewport()->mapToGlobal(pos));
    QListWidgetItem* currentItem = deviceList->currentItem();

    QString text = currentItem->text();
    int index = text.indexOf(' ');
    if(index == -1) {
        return;
    }

    QBluetoothAddress address(text.left(index));

    if(chosenAction == pairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Paired);
    } else if(chosenAction == unpairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Unpaired);
    }
}

void BluetoothHandler::pairingDone(const QBluetoothAddress& address, QBluetoothLocalDevice::Pairing pairingStatus) {

    QList<QListWidgetItem*> itemList = deviceList->findItems(address.toString(), Qt::MatchContains);

    if(pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired) {
        for(int i = 0; i < itemList.size(); i++) {
            QListWidgetItem* item = itemList.at(i);
            item->setTextColor(QColor(Qt::green));
        }
    } else {
        for(int i = 0; i < itemList.size(); i++) {
            QListWidgetItem* item = itemList.at(i);
            item->setTextColor(QColor(Qt::red));
        }
    }
}
