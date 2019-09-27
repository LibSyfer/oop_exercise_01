#ifndef BIGSTRING_HPP
#define BIGSTRING_HPP

struct BigString{
    BigString();
    BigString(unsigned long long n1, unsigned long long n2);
    ~BigString();

    void set_lString(unsigned long long n);
    void set_rString(unsigned long long n);
    unsigned long long get_lString() const;
    unsigned long long get_rString() const;

    void print_bits();

    void shiftLeft(int shift);
    void shiftRight(int shift);

    BigString AND(const BigString& s);
    BigString OR(const BigString& s);
    BigString XOR(const BigString& s);
    BigString NOT();

    int num_of_units() const;
    BigString* comparison(BigString& s);
    int is_include(const BigString& s);

private:
    unsigned long long lString;
    unsigned long long rString;
};

#endif
