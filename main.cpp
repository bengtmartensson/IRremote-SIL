#include "IRremote.h"
#include <iostream>
#include <cstdlib>

uint8_t PORTB;
static IRsend irsend;

extern void finalize(); // in our IRsend.cpp

void delay(unsigned int ms) {
    irsend.space(1000*ms);
} 

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

void work(unsigned n, unsigned reps) {
    for (unsigned int i = 0; i < reps; i++) {
        uint32_t p = static_cast<uint32_t> (rand());
        switch (n) {
            case 0:
                testAiwaRCT501(p); // NOK
                break;
            case 1:
                testDenon(p); // OK?
                break;
            case 2:
                testDish(p); // NOK
                break;
            case 3:
                testJVC(p, false); // OK
                break;
            case 4:
                testJVC(p, true); // NOK
                break;
            case 5:
                testLG(p); // = JVC
                break;
            case 6:
                testLego(p, false); // ??
                break;
            case 7:
                testLego(p, true); // ??
                break;
            case 8:
                testNec(p); // OK
                break;
            case 9:
                testPanasonic(p); // NOK
                break;
            case 10:
                testRc5(p); // OK
                break;
            case 11:
                testRc6(p); // OK
                break;
            case 12:
                testSamsung(p); // OK
                break;
            case 13:
                testSharp(p); // ?
                break;
            case 14:
                testSony20(p);  // OK
                break;
            case 15:
                testWhynter(p); // OK?
                break;
            default:
                break;
        }
    }
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        for (unsigned int i = 0; i <= 15; i++)
            work(i, 4);
    } else {
        unsigned n = atoi(argv[1]);
        unsigned reps = argc > 2 ? atoi(argv[2]) : 1;
        work(n, reps);
    }
    return 0;
}