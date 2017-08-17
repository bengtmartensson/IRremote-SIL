// Some stubs for non-Arduino environments.

// For the bizarre file name, see https://github.com/z3t0/Arduino-IRremote/issues/463

#ifndef WPROGRAM_H
#define WPROGRAM_H

#include <stdint.h>
#include <iostream>

#define HIGH 1
#define LOW 0
#define B11011111 223
#define B00100000 32

#define IR_TIMER_USE_ESP32

typedef bool boolean;

extern uint8_t PORTB;

static inline uint8_t digitalRead(uint8_t pin __attribute__((unused))) { return 0; };

static inline void digitalWrite(uint8_t pin, uint8_t value) {
    std::cout << "digitalWrite(" << (int) pin << ", "
            << (value == 0 ? "LOW" : "HIGH") << ")" << std::endl;
};

extern void delay(unsigned int d);

#endif /* WPROGRAM_H */

