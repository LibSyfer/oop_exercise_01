#include <iostream>
#include <fstream>
#include "bigString.hpp"

void separator()
{
    std::cout <<"==============";
    for(int i = 0; i < 128; ++i)
    {
        std::cout << "=";
    }
    std::cout << std::endl;
}

unsigned long long get_numfile(std::ifstream& fin)
{
    unsigned long long num = 0;
    char ch;
    while(fin.get(ch))
    {
        if (ch != ' ' && ch != '\n' && ch != EOF)
        {
            num = num * 10 + (ch - '0');
        }
        else
        {
            break;
        }
    }
    return num;
}

int main(int argc, char* argv[])
{
    unsigned long long n1;
    unsigned long long n2;

    if (argc < 2)
    {
        return 1;
    }

    std::ifstream fin(argv[1], std::ios_base::in);

    if (!fin.is_open())
    {
        std::cout << "Нельзя отрыть файл!\n";
        return 2;
    }

    n1 = get_numfile(fin);
    n2 = get_numfile(fin);
    BigString str1(n1, n2);

    n1 = get_numfile(fin);
    n2 = get_numfile(fin);
    BigString str2(n1, n2);

    separator();
    std::cout << "str1          ";
    str1.print_bits();
    std::cout << "str2          ";
    str2.print_bits();
    std::cout << "str1 and str2 ";
    str1.BS_and(str2).print_bits();
    separator();
    std::cout << "str1          ";
    str1.print_bits();
    std::cout << "str2          ";
    str2.print_bits();
    std::cout << "str1 or str2  ";
    str1.BS_or(str2).print_bits();
    separator();
    std::cout << "str1          ";
    str1.print_bits();
    std::cout << "str2          ";
    str2.print_bits();
    std::cout << "str1 xor str2 ";
    str1.BS_xor(str2).print_bits();
    separator();
    std::cout << "str1          ";
    str1.print_bits();
    std::cout << "not str1      ";
    str1.BS_not().print_bits();
    separator();
    std::cout << "str2          ";
    str2.print_bits();
    std::cout << "not str2      ";
    str2.BS_not().print_bits();
    separator();
    std::cout << "Num of units in str1: " << str1.numof_units() << std::endl;
    std::cout << "Num of units in str2: " << str2.numof_units() << std::endl;
    separator();
    BigString* p = str1.comparison(str2);
    std::cout << "Max in str1 and str2:\n";
    p->print_bits();

    fin.close();
    return 0;
}
