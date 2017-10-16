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
    if (pendingIsMark)
        std::cout << -DUMMYENDING << std::endl << std::endl;
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
    //unsigned t = time > 0 ? time : DUMMYENDING;
    if (!pendingIsMark)
        pending += time;
    else {
        flush();
        pending = time;
        pendingIsMark = false;
    }
}
