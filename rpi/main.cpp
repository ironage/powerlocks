
#include "gpioclass.h"
#include "serial.h"

#include <unistd.h>
#include <iostream>
#include <string>



int main(int argc, char *argv[]) {
    Serial btSerial("/dev/ttyAMA0", 115200);
    btSerial.writeString("hello world");
    std::string read = btSerial.readLine();
    std::cout << "we just read: " << read;

    GPIOClass pin4("4");    // 4, 17, 27, 22
    pin4.export_gpio();
    pin4.setdir_gpio("out");

    while (true) {
        pin4.setval_gpio("1");
        std::cout << "on";
        usleep(500000); //wait for 0.5 seconds
        pin4.setval_gpio("0");
        std::cout << "off";
        usleep(500000); //wait for 0.5 seconds
    }

    return 0;
}
