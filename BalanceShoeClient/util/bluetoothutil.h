
#ifndef BLUETOOTHUTIL_H
#define BLUETOOTHUTIL_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "util/utils.h"

namespace haevn::esp::bluetooth{

    #define START_BYTE 0xAF
    #define END_BYTE 0xFE

    // USER settings
    #define USER_WEIGHT      0x01
    #define USER_MAX_WEIGHT  0x02

    // Device settings
    #define CONFIG_BAUD        0xA1
    #define CONFIG_DOUT        0xA2
    #define CONFIG_SCK         0xA3
    #define CONFIG_REF_WEIGHT  0xA4
    #define CONFIG_TOLERANCE   0xA5
    #define CONFIG_SCALE_VALUE 0xA6

    #define DEVICE_BATTERY_STATE 0xB1
    #define DEVICE_LOG 0xB2



    /**
     * @brief The commands enum This enumeration is used to differentiate between different commands
     * @author Nils Milewski (nimile/10010480)
     */
    enum bluetoothCommands{
        weight = USER_WEIGHT,
        max_weight = USER_MAX_WEIGHT,

        baud = CONFIG_BAUD,
        dout = CONFIG_DOUT,
        sck = CONFIG_SCK,
        ref_weight = CONFIG_REF_WEIGHT,
        tolerance = CONFIG_TOLERANCE,
        scale_value = CONFIG_SCALE_VALUE,
        battery_state = DEVICE_BATTERY_STATE,
        device_log = DEVICE_LOG
    };

    class BluetoothCommandHandler : public QObject{

        Q_OBJECT

    public static_methods:

        /**
         * @brief getFileHandler This static method returns the singleton object of the class.
         * @details This static method initializes a new instance of this class iff none exist
         *          otherwise the existing instance will be returned.
         *          This singleton implementation will provide automatic destruction if the
         *          application exits.
         * @author Nils Milewski (nimile/10010480)
         */
        static BluetoothCommandHandler& getBluetoothCommandHandler(){
            static BluetoothCommandHandler instance; // Guaranteed to be destroyed
            return instance;
        }
    private methods:

        BluetoothCommandHandler(QObject* parent = nullptr);
        ~BluetoothCommandHandler();

    public methods:

        /**
         * @brief createFullCommand This method create a new command.
         * @details This method will create a new command based on command enum and data
         * @arg command Command which should be created
         * @arg data Data which schould be used for the command
         * @return Command which can be used to send the ESP32 over bluetooth
         * @author Nils Milewski (nimile/10010480)
         */
        char* createFullCommand(bluetoothCommands command, char* dataIn);


        /**
         * @brief calcCheckSum This method calculates the checksum of a bluetooth command.
         * @details This method uses the fletcher' 16 algorithm to calcualte a one byte
         *          checksum of the data and command.
         * @arg command Command
         * @arg data Data
         * @return checksum
         * @author Nils Milewski (nimile/10010480)
         */
        char calcCheckSum(bluetoothCommands command, char *dataIn);

        /**
         * @brief calcCheckSum This method calculates the checksum of a bluetooth command.
         * @details This method uses the fletcher' 16 algorithm to calcualte a one byte
         *          checksum of a 5byte data packet.
         * @arg data Data
         * @return checksum
         * @author Nils Milewski (nimile/10010480)
         */
        char calcCheckSum(char *data);

        /**
         * @brief test TESTIN CHECK SUM
         * @return
         * @todo remove
         * @deprecated
         */
        QString test();
    };
}
#endif // BLUETOOTHUTIL_H
