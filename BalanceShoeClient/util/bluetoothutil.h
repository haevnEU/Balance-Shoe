
#ifndef BLUETOOTHUTIL_H
#define BLUETOOTHUTIL_H

#include <QObject>
#include <QString>
#include <QStringList>


#include "util/utils.h"


namespace haevn::esp::bluetooth::util{

#define START_BYTE 0xAA
#define END_BYTE 0xFF

// USER settings
#define WEIGHT      0x01
#define MAX_WEIGHT  0x02

// Device settings
#define BAUD        0xA1
#define DOUT        0xA2
#define SCK         0xA3
#define REF_WEIGHT  0xA4
#define TOLERANCE   0xA5
#define SCALE_VALUE 0xA6

enum commands{
    weight = WEIGHT,
    max_weight = MAX_WEIGHT,

    baud = BAUD,
    dout = DOUT,
    sck = SCK,
    ref_weight = REF_WEIGHT,
    tolerance = TOLERANCE,
    scale_value = SCALE_VALUE
};
    char* createFullCommand(commands command, char* dataIn);
    char calcCheckSum(commands command, char *dataIn);
    char calcCheckSum(char *data);
    QString test();
}
#endif // BLUETOOTHUTIL_H
