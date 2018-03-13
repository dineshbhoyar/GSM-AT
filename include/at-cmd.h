//
// Created by dinesh on 5/2/18.
//

#ifndef GSM_MODEM_AT_CMD_H
#define GSM_MODEM_AT_CMD_H

#include <chrono>
#include <thread>
#include <iostream>
#include <memory>

#include "deviceOperation.h"

class at_cmd {
public:
    //virtual at_cmd& operator()(std::string cmd) = 0;
    virtual std::string responce() = 0;

    virtual void wait(uint32_t second) {
        std::this_thread::sleep_for(std::chrono::seconds(second));
    }

    virtual ~at_cmd() {
    };
};

class miscCmd : public at_cmd {
    std::string cmd{};
    std::string device{};
    std::string result{};
    std::unique_ptr<devOps> modem;
public:
    miscCmd(std::string device);
    //miscCmd& operator()(std::string cmd);
    miscCmd& exec(std::string cmd);
    std::string responce();
    ~miscCmd();
};

#endif //GSM_MODEM_AT_CMD_H
