//
// Created by dinesh on 5/2/18.
//

#ifndef GSM_MODEM_GSM_H
#define GSM_MODEM_GSM_H

#include <vector>
#include <string>
#include <iostream>

extern "C" {
#include <dirent.h>
#include <string.h>
}

class gsm {
    std::vector<std::string> modemList;
    uint32_t pcuiIdx = 0;
    void searchUSBModems(); //check for /dev/ttyUSB* and ececute AT Coomands
    void setModemParams(); //baud rate.speed etc..
public:
     gsm();
    //9. deinit card.
    ~gsm();

    //5. check for unread sms
    bool UnReadSMSAvailable();
    //6. read received sms
    void readSMS();
    //7  mark sms as read.
    void MarkSMSRead();
    //8. delete sms one by one.
    void DeleteSMS();

};
#endif //GSM_MODEM_GSM_H
