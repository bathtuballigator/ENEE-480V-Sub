#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <thread>

#include <lgpio.h>
#include <libcamera/libcamera.h>

#include <gpio_controller.h>

using namespace libcamera;
using namespace std::chrono_literals;

int OUTPUTS[] = {17, 22, 9, 5};
int BACK[] = {27, 10, 11, 5};
int num_outputs = sizeof(OUTPUTS) / sizeof(int);
int ZEROS[] = {0, 0, 0, 0};

// cleans up declared gpios for given gpio handle
int cleanup(int gpio_handle);

int main(int argc, char *argv[]) {
    int rc;
    float power;
    float power_arr[4];
    if (argc == 2) {
        power = atof(argv[1]);

    } else if (argc == 3) {
        // if (argv[1] < 0) {
        //     OUTPUTS[1] = BACK[1];
        // }
        power_arr[0] = atof(argv[1]);
        power_arr[1] = atof(argv[2]);
        power_arr[2] = 0;
        power_arr[3] = 0;
    } else if (argc == 5) {
        for (int i = 1; i < argc; i++) {
            power_arr[i - 1] = atof(argv[i]);
        }
    } else {
        fprintf(stderr, "Error with number of args\n");
        fprintf(stderr, "Usage: %s <pwm power percent>\n", argv[0]);
        fprintf(stderr, "Or %s <power> <power> <power> <power>\n", argv[0]);
        return -1;
    }
    int h = lgGpiochipOpen(0);
    if (h < 0) {
        printf("Error opening 0th chip: %d\n", h);
    }
    if (num_outputs != sizeof(ZEROS) / sizeof(int)) {
        printf("fix zeros array dummy\n");
        return -1;
    }
    rc = lgGroupClaimOutput(h, 0, num_outputs, OUTPUTS, ZEROS);
    if (rc < 0) {
        printf("error claming outputs: %d\n", rc);
        return cleanup(h);
    }

    printf("Turning on gpio\n");
    if (argc == 2) {
        printf("in if statement, 2\n");
        lgTxPwm(h, OUTPUTS[2], 1000, power, 0, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        lgGpioWrite(h, OUTPUTS[2], 0);
    } else if (argc == 5 || argc == 3) {
        for (int i = 0; i < num_outputs; i++) {
            lgTxPwm(h, OUTPUTS[i], 1000, power_arr[i], 0, 0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(12000));
        for (int i = 0; i < 4; i++) {
            if (i == 3) {
                lgGpioWrite(h, OUTPUTS[i], 0);
            } else {
                lgGpioWrite(h, OUTPUTS[i], 0);
            }
        }
    }
    printf("Turning off gpio\n");

    return cleanup(h);
}

int cleanup(int gpio_handle) {
    int rc = 0;
    rc = lgGroupFree(gpio_handle, OUTPUTS[0]);
    if (rc < 0)
        printf("Error freeing, return code %d\n", rc);

    rc = lgGpiochipClose(gpio_handle);
    if (rc < 0)
        printf("Error closing chip, return code %d\n", rc);
    return rc;
}
