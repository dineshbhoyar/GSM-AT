//
// Created by dinesh on 5/2/18.
//
#include "deviceOperation.h"

devOps::devOps(std::string path) {
    if (fd == -1) {
        fd = open(path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (fd != -1) {
            if (0 == tcgetattr(fd, &oldtio)) {
                restoreTIO = true;
                termios newtios{};
                newtios.c_cflag |= CLOCAL | CREAD;
                newtios.c_cflag &= ~CSIZE;
                int speed = 115200;
                int bits = 8;
                char event = 'N';
                int stop = 1;

                switch (bits) {
                    case 7:
                        newtios.c_cflag |= CS7;
                        break;
                    case 8:
                        newtios.c_cflag |= CS8;
                        break;
                }
                switch (event) {
                    case 'O':
                        newtios.c_cflag |= PARENB;
                        newtios.c_cflag |= PARODD;
                        newtios.c_iflag |= (INPCK | ISTRIP);
                        break;
                    case 'E':
                        newtios.c_iflag |= (INPCK | ISTRIP);
                        newtios.c_cflag |= PARENB;
                        newtios.c_cflag &= ~PARODD;
                        break;
                    case 'N':
                        newtios.c_cflag &= ~PARENB;
                        break;
                }

                switch (speed) {
                    case 2400:
                        cfsetispeed(&newtios, B2400);
                        cfsetospeed(&newtios, B2400);
                        break;
                    case 4800:
                        cfsetispeed(&newtios, B4800);
                        cfsetospeed(&newtios, B4800);
                        break;
                    case 9600:
                        cfsetispeed(&newtios, B9600);
                        cfsetospeed(&newtios, B9600);
                        break;
                    case 115200:
                        cfsetispeed(&newtios, B115200);
                        cfsetospeed(&newtios, B115200);
                        break;
                    default:
                        cfsetispeed(&newtios, B9600);
                        cfsetospeed(&newtios, B9600);
                        break;
                }
                if (stop == 1)
                    newtios.c_cflag &= ~CSTOPB;
                else if (stop == 2)
                    newtios.c_cflag |= CSTOPB;

                newtios.c_cc[VTIME] = 0;
                newtios.c_cc[VMIN] = 0;

                tcflush(fd, TCIOFLUSH);
                if (tcsetattr(fd, TCSANOW, &newtios) != 0) {
                    perror("tcsetattr:");
                }

            } else {
                perror("tcgetattr:");
            }
        } else {
            perror("open:");
        }
    } else {
        std::cout << " device already open " << std::endl;
    }
}

int32_t devOps::Read(std::string & result) {
    result.clear();
    int32_t res = -1;
    char buff[1024];
    size_t count = 1024;
    uint32_t retry = 5, timeout = 5;
    memset(buff, '\0', count - 1);
    tcflush(fd, TCOFLUSH);
    while (retry <= timeout) {
        do {
            res = read(fd, buff, count - 1);
        } while (res < 0 && res == EINTR);
        buff[count - 1] = '\0';

        // std::cout << std::hex << buff << std::endl;
        if ((res <= 0)
                || (strstr(buff, "ERROR") == NULL
                && strstr(buff, "\r\nOK\r\n") == NULL)) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            retry++;
        } else
            break;
    }
    if (res > 0)
        result.append(buff, res);
    //std::cout << result << "of len " << result.length() << std::endl;
    tcflush(fd, TCIOFLUSH);
    return res;
}

int32_t devOps::Write(std::string cmd) {
    int32_t byte = 0;

    // std::cout << "writing command " << cmd << " of len " << cmd.length() << std::endl;
    do {
        byte = write(fd, cmd.c_str(), cmd.length());
    } while (byte < 0 && errno == EINTR);
    return byte;
}

devOps::~devOps() {
    if (fd != -1) {
        if (restoreTIO) {
            tcflush(fd, TCIOFLUSH);
            tcsetattr(fd, TCSANOW, &oldtio);
        }
        close(fd);
    }
}