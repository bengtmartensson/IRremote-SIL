/*
Copyright (C) 2017 Bengt Martensson.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see http://www.gnu.org/licenses/.
*/

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

