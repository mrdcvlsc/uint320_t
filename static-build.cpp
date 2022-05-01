#include <iostream>
#include <uint320.hpp>

using namespace rushed;

uint320_t fac(size_t n) {
    uint320_t factorial(1);
    uint320_t iter = factorial;

    for(size_t i=1; i<=n; ++i) {
        factorial = factorial * iter;
        ++iter;
    }

    return factorial;
}

int main() {
    uint320_t a(23218713);
    uint320_t b(0x073243, 0xa5b6c6d, 0xa00fffff, 0xaaffedb217, 0x88affcef);

    uint320_t
        add = a+b,
        sub = a-b,
        mul = a*b,
        div = a/b,
        mod = a%b,
        rsf = a >> 20,
        lsf = b << 130,
        AND = a & b,
        OR  = a | b,
        NOT = ~a,
        XOR = a ^ b;

        bool
            booland = a && b,
            boolor  = a || b,
            boolnot = !a;

    std::cout << "Factorial of 67 :\n";
    uint320_t fac67 = fac(67);
    
    fac67.printHex();
    fac67.printBase10();

    return 0;
}