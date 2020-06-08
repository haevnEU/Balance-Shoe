#include "bluetoothutil.h"

using namespace haevn::esp::bluetooth;

BluetoothCommandHandler::BluetoothCommandHandler(QObject *parent) : QObject(parent){}

BluetoothCommandHandler::~BluetoothCommandHandler(){}

char* BluetoothCommandHandler::createFullCommand(bluetoothCommands command, char* dataIn){
    char* dataOut = static_cast<char*>(malloc(sizeof (char) * 8));
    if(nullptr == dataOut){
        return nullptr;
    }
    dataOut[0] = START_BYTE;
    dataOut[1] = command;
    for(int i = 0; i < 4; i++){
        dataOut[2 + i] = dataIn[i];
    }
    dataOut[6] = calcCheckSum(command, dataIn);
    dataOut[7] = END_BYTE;
    return dataOut;
}

char BluetoothCommandHandler::calcCheckSum(bluetoothCommands command, char* dataIn){

    char data[5];
    data[0] = command;
    for(int i = 0; i < 4; ++i){
        data[i + 1] = dataIn[i];
    }
    return calcCheckSum(data);
}

char BluetoothCommandHandler::calcCheckSum(char* data){

    /* Code from https://en.wikipedia.org/wiki/Fletcher%27s_checksum#Fletcher-16 */
    uint16_t sum1 = 0;
    uint16_t sum2 = 0;
    int index;
    for ( index = 0; index < 5; ++index ) {
        sum1 = (sum1 + data[index]) % 255;
        sum2 = (sum2 + sum1) % 255;
    }
    return static_cast<char>((sum2 << 8) | sum1);
}

QString BluetoothCommandHandler::test(){

    char data[] = {'A', 'B', 'C', 'D'};
    char* result = createFullCommand(bluetoothCommands::sck, data);
    QString tmp = "Dummy commands\n";
    for(int i = 0; i < 8; i++){
        tmp.append(QString::number(result[i])).append(" ");
    }
    tmp.append("\n");

    result = createFullCommand(bluetoothCommands::dout, data);

    for(int i = 0; i < 8; i++){
        tmp.append(QString::number(result[i])).append(" ");
    }

    tmp.append("\n");
    data[2] = 'B';
    result = createFullCommand(bluetoothCommands::dout, data);

    for(int i = 0; i < 8; i++){
        tmp.append(QString::number(result[i])).append(" ");
    }
    tmp.append("\n");
    data[2] = 0;
    result = createFullCommand(bluetoothCommands::dout, data);

    for(int i = 0; i < 8; i++){
        tmp.append(QString::number(result[i])).append(" ");
    }

    tmp.append("\n");
    char tmp2[5];
    tmp2[0] = result[1];
    tmp2[1] = result[2];
    tmp2[2] = result[3];
    tmp2[3] = result[4];
    tmp2[4] = result[5];
    char checkSum = calcCheckSum(tmp2);

    tmp.append("Checksum tests\n");
    tmp.append("result := calcCheckSum(received) == received[6]");
    tmp.append("\n");

    tmp.append("Checksum test 1\n")
            .append((checkSum == result[6] ? "true" : "false"))
            .append(" := ")
            .append(QString::number(checkSum))
            .append(" == ")
            .append(QString::number(result[6]));

    result[2] = 0xFF;
    tmp2[0] = result[1];
    tmp2[1] = result[2];
    tmp2[2] = result[3];
    tmp2[3] = result[4];
    tmp2[4] = result[5];

    checkSum = calcCheckSum(tmp2);

    tmp.append("\nChecksum test 2\n")
            .append((checkSum == result[6] ? "true" : "false"))
            .append(" := ")
            .append(QString::number(checkSum))
            .append(" == ")
            .append(QString::number(result[6]));
   return tmp;
}
