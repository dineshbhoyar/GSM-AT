//
// Created by dinesh on 5/2/18.
//

#ifndef GSM_MODEM_DEVICEOPERATION_H
#define GSM_MODEM_DEVICEOPERATION_H

extern "C" {
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <termios.h>
#include <string.h>
};

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

class devOps {
    int fd = -1;

    struct termios oldtio {   };
    bool restoreTIO = false;
public:
    /*initialization*/
    devOps(std::string name);
    /*write to device*/
    int32_t Write(std::string cmd);
    /*read to device*/
    int32_t Read(std::string & result);

    /*close down*/
    ~devOps();
};
#endif //GSM_MODEM_DEVICEOPERATION_H
