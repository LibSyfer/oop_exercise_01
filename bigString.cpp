#include <iostream>
#include "bigString.hpp"

BigString::BigString():lString(0), rString(0){}

BigString::BigString(unsigned long long n1, unsigned long long n2):lString(n1), rString(n2){}

BigString::~BigString(){}

void BigString::shiftLeft(int shift)
{
    unsigned long long Mask_firstBit = 0x8000000000000000; // первый бит 1 остальные 0
    int bit;
    for(int i = 0; i < shift; ++i)
    {
        if(this->rString&Mask_firstBit)
            bit = 1;
        else
            bit  = 0;

        this->rString = this->rString << 1;
        this->lString = this->lString << 1;
        this->lString = this->lString | bit;
    }
}

void BigString::shiftRight(int shift){
    unsigned long long Mask_lastBit = 1; // последний бит 1 остальные 0
    int bit;
    for(int i = 0; i < shift; ++i)
    {
        if (this->lString&Mask_lastBit)
        {
            bit = 1;
        }
        else
        {
            bit = 0;
        }
        this->lString = this->lString >> 1;
        this->rString = this->rString >> 1;
        if (bit)
        {
            this->rString= this->rString | 0x8000000000000000;
        }
    }
}

BigString BigString::BS_and(const BigString& s2)
{
    BigString res(0, 0);
    unsigned long long value;
    unsigned long long mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i)
    {
        value = (this->lString & s2.lString) & mask;
        if (value)
        {
            res.lString = res.lString | value;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i)
    {
        value = (this->rString & s2.rString) & mask;
        if (value)
        {
            res.rString = res.rString | value;
        }
        mask = mask >> 1;
    }
    return res;
}

BigString BigString::BS_or(const BigString& s2)
{
    BigString res(0, 0);
    unsigned long long mask = 0x8000000000000000;
    unsigned long long value;

    for(int i = 0; i < 64; ++i)
    {
        value = (this->lString | s2.lString) & mask;
        if (value)
        {
            res.lString = res.lString | value;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i)
    {
        value = (this->rString | s2.rString) & mask;
        if (value)
        {
            res.rString = res.rString | value;
        }
        mask = mask >> 1;
    }
    return res;
}

BigString BigString::BS_xor(const BigString& s2)
{
    BigString res(0, 0);
    unsigned long long mask = 0x8000000000000000;
    unsigned long long value1;
    unsigned long long value2;
    for(int i = 0; i < 64; ++i)
    {
        value1 = this->lString & mask;
        value2 = s2.lString & mask;
        if ((value1 != 0 && value2 == 0) || (value1 == 0 && value2 != 0))
        {
            res.lString = res.lString | mask;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i)
    {
        value1 = this->rString & mask;
        value2 = s2.rString & mask;
        if ((value1 != 0 && value2 == 0) || (value1 == 0 && value2 != 0))
        {
            res.rString = res.rString | mask;
        }
        mask = mask >> 1;
    }
    return res;
}

BigString BigString::BS_not()
{
    BigString res(0, 0);
    unsigned long long mask = 0x8000000000000000;
    unsigned long long value;

    for(int i = 0; i < 64; ++i)
    {
        value = this->lString & mask;
        if (!value)
        {
            res.lString = res.lString | mask;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i)
    {
        value = this->rString & mask;
        if (!value)
        {
            res.rString = res.rString | mask;
        }
        mask = mask >> 1;
    }
    return res;
}

int BigString::numof_units()
{
    unsigned long long mask = 0x8000000000000000;
    int counter = 0;
    for(int i = 0; i < 64; ++i)
    {
        if (this->lString & mask)
        {
            counter++;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i)
    {
        if (this->rString & mask)
        {
            counter++;
        }
        mask = mask >> 1;
    }
    return counter;
}

BigString* BigString::comparison(BigString& s2)
{
    int value1 = this->numof_units();
    int value2 = s2.numof_units();
    if (value1 >= value2)
    {
        return this;
    }
    else
    {
        return &s2;
    }
}

void BigString::print_bits()
{
    unsigned long long Mask_firstBit = 0x8000000000000000; // первый бит 1 остальные 0
    unsigned long long num = this->lString;
    for(int i = 0; i < 64; ++i)
    {
        if (num&Mask_firstBit)
        {
            std::cout << "1";
        }
        else
        {
            std::cout << "0";
        }
        num = num << 1;
    }
    num = this->rString;
    for(int i = 0; i < 64; ++i)
    {
        if (num&Mask_firstBit)
        {
            std::cout << "1";
        }
        else
        {
            std::cout << "0";
        }
        num = num << 1;
    }
    std::cout << "\n";
}
