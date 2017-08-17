// Some stubs for non-Arduino environments.

#ifndef ARDUINO_H
#define ARDUINO_H

#include <stdint.h>
#include <iostream>

#define HIGH 1
#define LOW 0
#define B11011111 223
#define B00100000 32

// Ideally, boarddefs.h should have a defined(SIL) or !defined(ARDUINO)
// setting up thing properly. Until then, use a work-around.
#define ESP32
#define SEND_PIN 999

// boolean is deprecated
typedef bool boolean;

extern uint8_t PORTB;

static inline uint8_t digitalRead(uint8_t pin __attribute__((unused))) { return 0; };

static inline void digitalWrite(uint8_t pin, uint8_t value) {
    std::cout << "digitalWrite(" << (int) pin << ", "
            << (value == 0 ? "LOW" : "HIGH") << ")" << std::endl;
};

extern void delay(unsigned int d);

#endif /* ARDUINO_H */

