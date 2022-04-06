#include <iostream>
#include <uint320.hpp>

uint320 fac(size_t n) {
    uint320 factorial(1);
    uint320 iter = factorial;

    for(size_t i=1; i<=n; ++i) {
        factorial = factorial * iter;
        ++iter;
    }

    return factorial;
}

int main() {
    uint320 a(23218713);
    uint320 b(0x073243, 0xa5b6c6d, 0xa00fffff, 0xaaffedb217, 0x88affcef);

    uint320
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
    fac(67).printHex();
    
    return 0;
}