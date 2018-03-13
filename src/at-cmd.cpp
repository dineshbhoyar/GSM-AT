#include "at-cmd.h"
#include "deviceOperation.h"

miscCmd::miscCmd(std::string device) : device {
    device
}, modem{new devOps(device)}
{

}

miscCmd::~miscCmd() {
    modem.reset();
}

miscCmd& miscCmd::exec(std::string cmd) {

    if (-1 != modem->Write(cmd)) {
        wait(2);
        if (0 != modem->Read(result))
            std::cout << result.c_str() << std::endl;
    } else {
        result = "ERROR";
    }
    return *this;
}

std::string miscCmd::responce() {

    return result;
}