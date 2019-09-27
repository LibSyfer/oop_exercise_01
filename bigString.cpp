#include <iostream>
#include "bigString.hpp"

BigString::BigString():lString(0), rString(0){}

BigString::BigString(unsigned long long n1, unsigned long long n2):lString(n1), rString(n2){}

BigString::~BigString(){}

void BigString::set_lString(unsigned long long n) {
    this->lString = n;
}

void BigString::set_rString(unsigned long long n) {
    this->rString = n;
}

unsigned long long BigString::get_lString() const {
    return this->lString;
}

unsigned long long BigString::get_rString() const {
    return this->rString;
}

void BigString::print_bits() {
    unsigned long long Mask_firstBit = 0x8000000000000000; // первый бит 1 остальные 0
    unsigned long long num = this->lString;
    for(int i = 0; i < 64; ++i) {
        if (num&Mask_firstBit) {
            std::cout << "1";
        }
        else {
            std::cout << "0";
        }
        num = num << 1;
    }
    num = this->rString;
    for(int i = 0; i < 64; ++i) {
        if (num&Mask_firstBit) {
            std::cout << "1";
        }
        else {
            std::cout << "0";
        }
        num = num << 1;
    }
    std::cout << "\n";
}

void BigString::shiftLeft(int shift) {
    unsigned long long Mask_firstBit = 0x8000000000000000; // первый бит 1 остальные 0
    int bit;
    for(int i = 0; i < shift; ++i) {
        if(this->rString & Mask_firstBit) {
            bit = 1;
        }
        else {
            bit  = 0;
        }
        this->rString = this->rString << 1;
        this->lString = this->lString << 1;
        this->lString = this->lString | bit;
    }
}

void BigString::shiftRight(int shift) {
    unsigned long long Mask_lastBit = 1; // последний бит 1 остальные 0
    int bit;
    for(int i = 0; i < shift; ++i) {
        if (this->lString & Mask_lastBit) {
            bit = 1;
        }
        else {
            bit = 0;
        }
        this->lString = this->lString >> 1;
        this->rString = this->rString >> 1;
        if (bit) {
            this->rString= this->rString | 0x8000000000000000;
        }
    }
}

BigString BigString::AND(const BigString& s) {
    BigString res;
    unsigned long long mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i) {
        if ((this->lString & s.get_lString()) & mask) {
            res.lString = res.lString | mask;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i) {
        if ((this->rString & s.get_rString()) & mask) {
            res.rString = res.rString | mask;
        }
        mask = mask >> 1;
    }
    return res;
}

BigString BigString::OR(const BigString& s) {
    BigString res;
    unsigned long long mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i) {
        if ((this->lString | s.get_lString()) & mask) {
            res.lString = res.lString | mask;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i) {
        if ((this->rString | s.get_rString()) & mask) {
            res.rString = res.rString | mask;
        }
        mask = mask >> 1;
    }
    return res;
}

BigString BigString::XOR(const BigString& s) {
    BigString res;
    unsigned long long mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i) {
        if ((!(this->lString & mask) && (s.get_lString() & mask)) ||
              ((this->lString & mask) && !(s.get_lString() & mask))) {
            res.lString = res.lString | mask;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i) {
        if ((!(this->rString & mask) && (s.get_rString() & mask)) ||
              ((this->rString & mask) && !(s.get_rString() & mask))) {
            res.rString = res.rString | mask;
        }
        mask = mask >> 1;
    }
    return res;
}

BigString BigString::NOT() {
    BigString res;
    unsigned long long mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i) {
        if (!(this->lString & mask)) {
            res.lString = res.lString | mask;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i) {
        if (!(this->rString & mask)) {
            res.rString = res.rString | mask;
        }
        mask = mask >> 1;
    }
    return res;
}

int BigString::num_of_units() const {
    unsigned long long mask = 0x8000000000000000;
    int counter = 0;
    for(int i = 0; i < 64; ++i) {
        if (this->lString & mask) {
            counter++;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i) {
        if (this->rString & mask) {
            counter++;
        }
        mask = mask >> 1;
    }
    return counter;
}

BigString* BigString::comparison(BigString& s) {
    int value1 = this->num_of_units();
    int value2 = s.num_of_units();
    if (value1 >= value2) {
        return this;
    }
    else {
        return &s;
    }
}

int BigString::is_include(const BigString& s) {
    if(((this->lString & s.get_lString()) == this->get_lString()) || ((this->rString & s.get_rString()) == this->get_rString())) {
        return 1;
    }
    else {
        return 0;
    }
}
