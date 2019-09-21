#ifndef BIGSTRING_HPP
#define BIGSTRING_HPP

struct BigString{
    BigString();
    BigString(unsigned long long n1, unsigned long long n2);
    ~BigString();

    void shiftLeft(int shift);
    void shiftRight(int shift);
    void print_bits(); //вспомогательная функция для вывода побитово строки

    BigString BS_and(const BigString& s2); //возвращает результат побитовгого и(&) для двух строк
    BigString BS_or(const BigString& s2); //возвращает результат побитовгого или(|) для двух строк
    BigString BS_xor(const BigString& s2); //возвращает результат исключающего или для двух строк
    BigString BS_not(); //возвращает битовую инверсию

    int numof_units(); //вернет кол-во единиц в строке
    BigString* comparison(BigString& s2); // вернет указатель на стрку с наибольшим кол-вом единиц

private:
    unsigned long long lString; //левое поле строки
    unsigned long long rString; //правиое поле строки
};

#endif
