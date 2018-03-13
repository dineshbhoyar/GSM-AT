//
// Created by dinesh on 5/2/18.
//
#include "gsm.h"
#include "at-cmd.h"

gsm::gsm() {
    searchUSBModems();
}

gsm::~gsm() {

}

void gsm::searchUSBModems() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    struct dirent **namelist = nullptr;
    auto filter = [&] (const struct dirent * dir) {
        return (nullptr != strstr(dir->d_name, "ttyUSB")) ? 1 : 0;
    };
    //    auto compare = [&](const struct dirent ** dir1, const struct dirent **dir2) {
    //        std::cout << "compare" << (*dir1)->d_name << " with " << (*dir2)->d_name << std::endl;
    //        return 0;
    //    };
    uint32_t count = scandir("/dev/", &namelist, filter, alphasort);
    for (uint32_t i = 0; i < count; i++) {
        std::cout << " device : " << namelist[i]->d_name << std::endl;
        std::string device{"/dev/" + std::string(namelist[i]->d_name)};
        miscCmd cmd(device);
        cmd.exec("ATZ\r\n").exec("ATE0\r\n").exec("AT\r\n").exec("AT+CMEE?\r\n").exec("AT+CMEE=1\r\n").exec("AT+CGMI\r\n").exec("AT+CGMM\r\n").exec("AT+CPIN?\r\n");
        if (!cmd.responce().compare("OK")) {
            modemList.push_back(device);
        }
        free(namelist[i]);
    }
    free(namelist);
    std::cout << "got total " << count << " devices " << std::endl;
    return;
}

void gsm::setModemParams() {

}

    void gsm::readSMS() {

}

void gsm::MarkSMSRead() {

}

bool gsm::UnReadSMSAvailable() {
    return true;
}

void gsm::DeleteSMS() {

}