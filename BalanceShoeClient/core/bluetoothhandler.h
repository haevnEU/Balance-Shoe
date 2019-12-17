#ifndef BLUETOOTHHANDLER_H
#define BLUETOOTHHANDLER_H

#include <qbluetoothlocaldevice.h>

#include <QDialog>
#include <QLabel>
#include <QListWidget>

QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

namespace haevn::esp::core {

    class BluetoothHandler : public QDialog
    {
        Q_OBJECT

        public:
            /**
             * @brief BluetoothHandler class shows bluetooth devices nearby
             * @details In general this class contains the logic to handle the bluetooth devices nearby.
             * @param parent
             * @author Marc Nowakowski (marcnow/10009339)
             */
            BluetoothHandler(QWidget* parent = nullptr);

            /**
              * @brief destructor to delete discoveryAgent and localDevice
              * @author Marc Nowakowski (marcnow/10009339)
              */
            ~BluetoothHandler();

        private:
            /**
             * @brief discoveryAgent shows bluetooth devices nearby
             * @author Marc Nowakowski (marcnow/10009339)
             */
            QBluetoothDeviceDiscoveryAgent* discoveryAgent;

            /**
             * @brief localDevice enables the access to a bluetooth device
             * @author Marc Nowakowski (marcnow/1009339)
             */
            QBluetoothLocalDevice* localDevice;

            QLabel* labelName;
            QPushButton* buttonScan;
            QPushButton* buttonClear;
            QPushButton* buttonQuit;
            QListWidget* deviceList;

        public slots:
            /**
             * @brief deviceDiscovered displays a device when it gets discovered
             * @details This slot will be invoked when discoveryAgent discovers a bluetooth device nearby.
             *          The device will then be displayed on the dialog.
             *          It also checks if a device is already displayed, so a device only exists one time in the list.
             *          If a device is paired or authorized paired it gets displayed in the color green
             *          and if a device is not paired it gets displayed blue.
             * @param deviceInfo
             * @author Marc Nowakowski (marcnow/1009339)
             */
            void deviceDiscovered(const QBluetoothDeviceInfo&);

            /**
             * @brief showPairingMenu shows menu when clicked on a device in a list
             * @details This slot will be invoked when clicked on a device in the bluetooth list.
             *          It show two Actions: "Pair..." and "Unpair...".
             *          If clicked on "Pair..." it connects to the bluetooth device.
             *          And if clicked on "Unpair..." it removes the connection to the bluetooth device.
             * @param Cursor Position
             * @author Marc Nowakowski (marcnow/1009339)
             */
            void showPairingMenu(const QPoint& pos);

            /**
             * @brief pairingDone displays if a pairing is done in a certain color
             * @details This slot will be invoked when localDevice finished the pairing.
             *          If the devices are paired the device will be displayed green
             *          and if the devices gets unpaired the device will be displayed red.
             * @param bluetoothAddress and pairingStatus
             * @author Marc Nowakowski (marcnow/1009339)
             */
            void pairingDone(const QBluetoothAddress&, QBluetoothLocalDevice::Pairing);


        private slots:
            /**
             * @brief startScan starts the scan
             * @details This slot will be invoked when clicked on buttonScan.
             *          The discoveryAgent starts a scan of bluetooth devices nearby.
             *          The buttonScan will be disabled.
             * @author Marc Nowakowski (marcnow/1009339)
             */
            void startScan();

            /**
             * @brief scanFinished
             * @details This slot will be invoked when discoveryAgent finished the scan.
             *          The buttonScan will be enabled.
             * @author Marc Nowakowski (marcnow/1009339)
             */
            void scanFinished();

        };
}

#endif // BLUETOOTHHANDLER_H
