#include <cstdio>
class GPIOController {
    public:
        GPIOController(int *OUTPUTS, int num_outputs)
            : GPIOController(0, OUTPUTS, num_outputs) {};
        GPIOController(int chip_num, int *OUTPUTS, int num_outputs);

        ~GPIOController();

    private:
        int *OUTPUTS;
        int num_outputs;

        int *ZEROS;

        int h;
};
