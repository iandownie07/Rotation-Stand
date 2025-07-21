#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdint.h>

// Structure for each frequency option
typedef struct {
    float frequency_hz;
    float duty_cycle;     // 0.01 = 1%
} motor_freq_option_t;

// Define your frequency table (option B style)
#define NUM_FREQ_OPTIONS 20
static const motor_freq_option_t freq_table[NUM_FREQ_OPTIONS] = {
    {0.05f, 0.01f},
    {0.1f, 0.01f},
    {0.15f, 0.01f},
    {0.2f, 0.01f},
    {0.25f, 0.01f},
    {0.3f, 0.01f},
    {0.35f, 0.01f},
    {0.4f, 0.01f},
    {0.45f, 0.01f},
    {0.5f, 0.01f},
    {0.6f, 0.01f},
    {0.7f, 0.01f},
    {0.8f, 0.01f},
    {0.9f, 0.01f},
    {1.0f, 0.01f},
    {1.1f, 0.01f},
    {1.2f, 0.01f},
    {1.3f, 0.01f},
    {1.4f, 0.01f},
    {1.5f, 0.01f}
};

#endif // CONFIGURATION_H
