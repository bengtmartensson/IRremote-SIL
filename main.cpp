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

#include "IRremote-SIL.h"
#include <iostream>
#include <strings.h>

#define STRINGEQUAL(a, b) (strcasecmp(a, b) == 0)

void testNec(uint32_t par) {
    std::cout << "NEC_0x" << std::hex << par << std::endl;
    irsend.sendNEC(par, 32);
    finalize();
}

void testAiwaRCT501(uint32_t par) {
    int16_t p = static_cast<int16_t>(par);
    std::cout << "AiwaRCT501_0x" << std::hex << p << std::endl;
    irsend.sendAiwaRCT501(p);
    finalize();
}

void testDenon(uint32_t par) {
    std::cout << "Denon_0x" << std::hex << par << std::endl;
    irsend.sendDenon(par, 14);
    finalize();
}

void testDish(uint32_t par) {
    std::cout << "Dish_0x" << std::hex << par << std::endl;
    irsend.sendDenon(par, 16);
    finalize();
}

void testJVC(uint32_t par, bool repeat) {
    std::cout << (repeat ? "JVCrepeat_0x" : "JVC_0x") << std::hex << par << std::endl;
    irsend.sendJVC(par, 16, repeat);
    finalize();

}

void testLG(uint32_t par) {
    std::cout << "LG_0x" << std::hex << par << std::endl;
    irsend.sendLG(par, 16);
    finalize();
}

void testLego(uint32_t par, bool repeat) {
    std::cout << "Lego_0x" << std::hex << par << std::endl;
    irsend.sendLegoPowerFunctions(par, repeat);
    finalize();
}

void testPanasonic(uint32_t par) {
    std::cout << "Panasonic_0x" << std::hex << par << std::endl;
    irsend.sendPanasonic(par << 16, par & 0xFFFF);
    finalize();
}

void testRc5(uint32_t par) {
    std::cout << "Rc5_0x" << std::hex << par << std::endl;
    irsend.sendRC5(par & 0xFFF, 12);
    finalize();
}

void testRc6(uint32_t par) {
    std::cout << "Rc6_0x" << std::hex << par << std::endl;
    irsend.sendRC6(par, 20);
    finalize();
}

void testSamsung(uint32_t par) {
    std::cout << "Samsung_0x" << std::hex << par << std::endl;
    irsend.sendSAMSUNG(par, 20);
    finalize();
}

void testSharp(uint32_t par) {
    std::cout << "Sharp_0x" << std::hex << par << std::endl;
    irsend.sendSharpRaw(par, 15);
    finalize();
}

void testSony20(uint32_t par) {
    std::cout << "Sony20_0x" << std::hex << par << std::endl;
    irsend.sendSony(par, 20);
    finalize();
}

void testWhynter(uint32_t par) {
    std::cout << "Whynter_0x" << std::hex << par << std::endl;
    irsend.sendWhynter(par, 32);
    finalize();
}

bool work(const char* protName, unsigned reps) {
    for (unsigned int i = 0; i < reps; i++) {
        uint32_t p = static_cast<uint32_t> (rand());
        if (STRINGEQUAL(protName, "aiwa"))
            testAiwaRCT501(p); // NOK
        else if (STRINGEQUAL(protName, "denon"))
            testDenon(p); // OK?
        else if (STRINGEQUAL(protName, "dish"))
            testDish(p); // NOK
        else if (STRINGEQUAL(protName, "jvc"))
            testJVC(p, false); // OK
        else if (STRINGEQUAL(protName, "jvc-repeat"))
            testJVC(p, true); // NOK
        else if (STRINGEQUAL(protName, "lg"))
            testLG(p); // = JVC
        else if (STRINGEQUAL(protName, "lego"))
            testLego(p, false); // ??
        else if (STRINGEQUAL(protName, "lego-repeat"))
            testLego(p, true); // ??
        else if (STRINGEQUAL(protName, "nec"))
            testNec(p); // OK
        else if (STRINGEQUAL(protName, "panasonic"))
            testPanasonic(p); // NOK
        else if (STRINGEQUAL(protName, "rc5"))
            testRc5(p); // OK
        else if (STRINGEQUAL(protName, "rc6"))
            testRc6(p); // OK
        else if (STRINGEQUAL(protName, "samsung"))
            testSamsung(p); // OK
        else if (STRINGEQUAL(protName, "sharp"))
            testSharp(p); // ?
        else if (STRINGEQUAL(protName, "sony20"))
            testSony20(p); // OK
        else if (STRINGEQUAL(protName, "whynter"))
            testWhynter(p); // OK?
        else {
            std::cerr << "Unknown protocol requested: " << protName << std::endl;
            return false;
        }
    }
    return true;
}

void usage(const char* progname) {
    std::cerr << "Usage:" << std::endl
            << "\t" << progname << " protocol [repeats]" << std::endl;
    exit(1);
}

int main(int argc, char** argv) {
    if (argc < 2)
        usage(argv[0]);
    unsigned reps = argc > 2 ? atoi(argv[2]) : 1;
    bool status = work(argv[1], reps);
    return status ? 0 : 2;
}
