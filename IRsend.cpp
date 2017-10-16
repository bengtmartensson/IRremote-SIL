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

#include "IRremote.h"
#include <iostream>

static const int DUMMYENDING = 25000;
static unsigned int pending;
static bool pendingIsMark;

unsigned long frequency;

IRsend irsend;

void delay(unsigned int ms) {
    irsend.space(1000*ms);
}

static void flush() {
    if (pending > 0)
        std::cout << (pendingIsMark ? "+" : "-") << pending << " ";
    pending = 0;
}

void finalize() {
    flush();
    std::cout << std::endl << std::endl;
}

void IRsend::enableIROut(int khz) {
    std::cout << std::dec;
    pending = 0;
    pendingIsMark = false;
    frequency = 1000 * khz;
}

void IRsend::mark(unsigned time) {
    if (pendingIsMark)
        pending += time;
    else {
        flush();
        pending = time;
        pendingIsMark = true;
    }
}

void IRsend::space(unsigned time) {
    unsigned t = time > 0 ? time : DUMMYENDING;
    if (!pendingIsMark)
        pending += t;
    else {
        flush();
        pending = t;
        pendingIsMark = false;
    }
}
