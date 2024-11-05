#include <cstdio>
#include <cstring>
#include <gpio_controller.h>
#include <lgpio.h>

GPIOController::GPIOController(int chip_num, int *OUTPUTS, int num_outputs) {
    this->h = lgGpiochipOpen(chip_num);
    int rc;

    if (this->h < 0) {
        printf("Error opening %dth chip: %d\n", chip_num, h);
        goto error;
    }
    rc = lgGroupClaimOutput(h, 0, num_outputs, OUTPUTS, ZEROS);
    if (rc < 0) {
        printf("error claming outputs: %d\n", rc);
    }
    this->ZEROS = new int[num_outputs];
    memset(this->ZEROS, 0, num_outputs);
    return;
error:
    if (this->h >= 0) {
        rc = lgGpiochipClose(this->h);
    }
    fprintf(stderr, "Error constructing GPIOController\n");
}

GPIOController::~GPIOController() {}
