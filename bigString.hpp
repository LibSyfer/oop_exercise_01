#ifndef BIGSTRING_HPP
#define BIGSTRING_HPP

struct BigString{
    BigString();
    BigString(unsigned long long n1, unsigned long long n2);
    ~BigString();

    unsigned long long get_lString() const;
    void set_lString(unsigned long long n);
    void set_rString(unsigned long long n);
    unsigned long long get_rString() const;

    void print_bits(); //вспомогательная функция для вывода побитово строки

    void shiftLeft(int shift); // сдвиг влево на shift бит
    void shiftRight(int shift); // сдвиг вправо на shift бит

    BigString AND(const BigString& s); //возвращает результат побитовгого и(&) для двух строк
    BigString OR(const BigString& s); //возвращает результат побитовгого или(|) для двух строк
    BigString XOR(const BigString& s); //возвращает результат исключающего или для двух строк
    BigString NOT(); //возвращает битовую инверсию

    int num_of_units() const; //вернет кол-во единиц в строке
    BigString* comparison(BigString& s); // вернет указатель на стрку с наибольшим кол-вом единиц
    int is_include(const BigString& s);

private:
    unsigned long long lString; //левое поле строки
    unsigned long long rString; //правиое поле строки
};

#endif
