/*
 * Copyright 2019 nils
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
#include "bluetoothutil.h"

char haevn::esp::bluetooth::util::calcCheckSum(char* data){

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
char haevn::esp::bluetooth::util::calcCheckSum(commands command, char* dataIn){

    char data[5];
    data[0] = command;
    for(int i = 0; i < 4; ++i){
        data[i + 1] = dataIn[i];
    }
    return haevn::esp::bluetooth::util::calcCheckSum(data);
}

char* haevn::esp::bluetooth::util::createFullCommand(commands command, char* dataIn){
    char* dataOut = static_cast<char*>(malloc(sizeof (char) * 8));
    if(nullptr == dataOut){
        return nullptr;
    }
    dataOut[0] = START_BYTE;
    dataOut[1] = command;
    for(int i = 0; i < 4; i++){
        dataOut[2 + i] = dataIn[i];
    }
    dataOut[6] = haevn::esp::bluetooth::util::calcCheckSum(command, dataIn);
    dataOut[7] = END_BYTE;
    return dataOut;
}

QString haevn::esp::bluetooth::util::test(){

    char data[] = {'A', 'B', 'C', 'D'};
    char* result = bluetooth::util::createFullCommand(bluetooth::util::commands::sck, data);
    QString tmp = "Dummy commands\n";
    for(int i = 0; i < 8; i++){
        tmp.append(QString::number(result[i])).append(" ");
    }
    tmp.append("\n");

    result = bluetooth::util::createFullCommand(bluetooth::util::commands::dout, data);

    for(int i = 0; i < 8; i++){
        tmp.append(QString::number(result[i])).append(" ");
    }

    tmp.append("\n");
    data[2] = 'B';
    result = bluetooth::util::createFullCommand(bluetooth::util::commands::dout, data);

    for(int i = 0; i < 8; i++){
        tmp.append(QString::number(result[i])).append(" ");
    }
    tmp.append("\n");
    data[2] = 0;
    result = bluetooth::util::createFullCommand(bluetooth::util::commands::dout, data);

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
    char checkSum = bluetooth::util::calcCheckSum(tmp2);

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

    checkSum = bluetooth::util::calcCheckSum(tmp2);

    tmp.append("\nChecksum test 2\n")
            .append((checkSum == result[6] ? "true" : "false"))
            .append(" := ")
            .append(QString::number(checkSum))
            .append(" == ")
            .append(QString::number(result[6]));
   return tmp;
}
