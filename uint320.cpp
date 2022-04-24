#ifndef uidMRDCVLSC_uint320_t_CPP
#define uidMRDCVLSC_uint320_t_CPP
#include <iostream>
#include <cstring>
#include <bitset>

#ifdef _MAKE_LIB
#include "uint320.hpp"
#endif

namespace rushed {
    
    uint320_t::uint320_t() {}

    uint320_t::uint320_t(uint64_t num) {
        limbs[0] = num;
        limbs[1] = 0UL;
        limbs[2] = 0UL;
        limbs[3] = 0UL;
        limbs[4] = 0UL;
    }

    uint320_t::uint320_t(const unsigned char *input_bytes, size_t bytes) {
        size_t byte_offset = UINT320BYTES - bytes;
        unsigned char *byte_form = (unsigned char*) limbs;

        memcpy(byte_form, input_bytes, bytes);
        memset(byte_form+bytes, 0x00, byte_offset);
    }

    uint320_t::uint320_t(
        uint64_t n4, uint64_t n3, uint64_t n2, uint64_t n1, uint64_t n0
    ) {
        limbs[0] = n0;
        limbs[1] = n1;
        limbs[2] = n2;
        limbs[3] = n3;
        limbs[4] = n4;
    }

    /// copy constructor
    uint320_t::uint320_t(const uint320_t& src) {
        memcpy(limbs, src.limbs, UINT320BYTES);
    }

    /// copy assignment
    uint320_t& uint320_t::operator=(const uint320_t& src) {
        memcpy(limbs, src.limbs, UINT320BYTES);
        return *this;
    }

    uint320_t::~uint320_t() {}

    /// @return returns; 0 : if uint320_t == 0, 1 : if uint320_t == 1, and -1 : if uint320_t != to 0 or 1.
    int uint320_t::one_or_zero() const {

        if(limbs[UINT320_LS_LIMB] > 1)
            return -1;

        for(size_t i=1; i<UINT320LIMBS; ++i) {
            if(limbs[i])
                return -1;
        }

        return limbs[UINT320_LS_LIMB];
    }

    /// @return returns; -1 : if less than, 0 : if equal, 1 : if greater than.
    int uint320_t::compare(const uint320_t& with) const {

        int value = 0;

        for(size_t i=0; i<UINT320LIMBS; ++i) {

            if(limbs[UINT320_MS_LIMB-i]<with.limbs[UINT320_MS_LIMB-i]) {
                value = -1;
                break;
            }

            if(limbs[UINT320_MS_LIMB-i]>with.limbs[UINT320_MS_LIMB-i]) {
                value = 1;
                break;
            }
        }
        return value;
    }

    bool uint320_t::operator==(const uint320_t& with) const {
        if(compare(with)==EQUAL)
            return true;
        return false;
    }

    bool uint320_t::operator!=(const uint320_t& with) const {
        return !(*this==with);
    }

    bool uint320_t::operator<(const uint320_t& with) const {
        if(compare(with)==LESS)
            return true;
        return false;
    }

    bool uint320_t::operator>(const uint320_t& with) const {
        if(compare(with)==GREAT)
            return true;
        return false;
    }

    bool uint320_t::operator<=(const uint320_t& with) const {
        int value = compare(with);
        if(value==LESS || value==EQUAL)
            return true;
        return false;
    }

    bool uint320_t::operator>=(const uint320_t& with) const {
        int value = compare(with);
        if(value==GREAT || value==EQUAL)
            return true;
        return false;
    }

    /// @return returns true if the uint320_t is not zero
    bool uint320_t::boolean() const {
        for(size_t i=0; i<UINT320LIMBS; ++i) {
            if(limbs[i])
                return true;
        }
        return false;
    }

    bool uint320_t::operator&&(const uint320_t& with) const {
        return boolean() && with.boolean();
    }

    bool uint320_t::operator||(const uint320_t& with) const {
        return boolean() || with.boolean();
    }

    bool uint320_t::operator!() const {
        return !boolean();
    }

    uint320_t uint320_t::operator&(const uint320_t& with) const {
        uint320_t result(0,0,0,0,0);
        for(size_t i=0; i<UINT320LIMBS; ++i)
            result.limbs[i] = limbs[i] & with.limbs[i];
        return result;
    }

    uint320_t uint320_t::operator|(const uint320_t& with) const {
        uint320_t result(0,0,0,0,0);
        for(size_t i=0; i<UINT320LIMBS; ++i)
            result.limbs[i] = limbs[i] | with.limbs[i];
        return result;
    }

    uint320_t uint320_t::operator^(const uint320_t& with) const {
        uint320_t result(0,0,0,0,0);
        for(size_t i=0; i<UINT320LIMBS; ++i)
            result.limbs[i] = limbs[i] ^ with.limbs[i];
        return result;
    }

    uint320_t uint320_t::operator~() const {
        uint320_t result(0,0,0,0,0);
        for(size_t i=0; i<UINT320LIMBS; ++i)
            result.limbs[i] = ~limbs[i];
        return result;
    }

    uint320_t& uint320_t::operator&=(const uint320_t& with) {
        for(size_t i=0; i<UINT320LIMBS; ++i)
            limbs[i] &= with.limbs[i];
        return *this;
    }

    uint320_t& uint320_t::operator|=(const uint320_t& with) {
        for(size_t i=0; i<UINT320LIMBS; ++i)
            limbs[i] |= with.limbs[i];
        return *this;
    }

    uint320_t& uint320_t::operator^=(const uint320_t& with) {
        for(size_t i=0; i<UINT320LIMBS; ++i)
            limbs[i] ^= with.limbs[i];
        return *this;
    }

    uint320_t uint320_t::operator+(const uint320_t& add) const {
        
        uint320_t sum = *this;

    #if(__x86_64 || __x86_64__ || __amd64 || __amd64__ || __aarch64__)
    #if(_MSC_VER || _PURE_CPP)
        __uint128_t sum_uint128[UINT320LIMBS+1] = {0,0,0,0,0,0};

        for(size_t i=0; i<UINT320LIMBS; ++i) {
            sum_uint128[i] += (__uint128_t)sum.limbs[i] + (__uint128_t)add.limbs[i];
            
            // carry high part
            sum_uint128[i+1] += (sum_uint128[i] >> UINT64BITS);

            // zero-out high part
            sum_uint128[i] = (sum_uint128[i] << UINT64BITS) >> UINT64BITS;
        }

        for(size_t i=0; i<UINT320LIMBS; ++i) {
            sum.limbs[i] = sum_uint128[i];
        }
    #elif((__clang__ || __GNUC__ || __GNUG__ || __MINGW64__) && (__aarch64 || __aarch64__))
    #ifndef _HIDE_WARNING
    #warning using GCC inline asm, please enable optimization flag, recomended : -O2, to enable use C++ implementation instead, enable the -D_PURE_CPP flag.
    #endif
        __uint128_t sum_uint128[UINT320LIMBS+1] = {0,0,0,0,0,0};

        for(size_t i=0; i<UINT320LIMBS; ++i) {
            sum_uint128[i] += (__uint128_t)sum.limbs[i] + (__uint128_t)add.limbs[i];
            
            // carry high part
            sum_uint128[i+1] += (sum_uint128[i] >> UINT64BITS);

            // zero-out high part
            sum_uint128[i] = (sum_uint128[i] << UINT64BITS) >> UINT64BITS;
        }

        for(size_t i=0; i<UINT320LIMBS; ++i) {
            sum.limbs[i] = sum_uint128[i];
        }

    #elif(__clang__ || __GNUC__ || __GNUG__ || __MINGW64__)
    #ifndef _HIDE_WARNING
    #warning using GCC inline asm, please enable optimization flag, recomended : -O2, to enable use C++ implementation instead, enable the -D_PURE_CPP flag.
    #endif
        asm (
            "addq %[adn0], %[sum0]\n\t"
            "adcq %[adn1], %[sum1]\n\t"
            "adcq %[adn2], %[sum2]\n\t"
            "adcq %[adn3], %[sum3]\n\t"
            "adcq %[adn4], %[sum4]"
            :
            [sum0]"+r"(sum.limbs[0]),
            [sum1]"+r"(sum.limbs[1]),
            [sum2]"+r"(sum.limbs[2]),
            [sum3]"+r"(sum.limbs[3]),
            [sum4]"+r"(sum.limbs[4])
            :
            [adn0]"m"(add.limbs[0]),
            [adn1]"m"(add.limbs[1]),
            [adn2]"m"(add.limbs[2]),
            [adn3]"m"(add.limbs[3]),
            [adn4]"m"(add.limbs[4])
            : "cc"
        );
    #else
        #error uint320_t is not supported on this compiler
    #endif
    #else
    #error uint320_t is not supported on 32-bit computers (x86 architectures)
    #endif

        return sum;
    }

    uint320_t& uint320_t::operator+=(const uint320_t& add) {
        return *this = *this + add;
    }

    uint320_t& uint320_t::operator++() {
        return *this = *this + uint320_t(1);
    }

    uint320_t uint320_t::operator++(int) {
        uint320_t pre = *this;
        ++*this;
        return pre;
    }


    uint320_t uint320_t::operator-(const uint320_t& sub) const {
        
        uint320_t dif = *this;

        uint64_t carry = 0, prev;

        for(size_t i=0; i<UINT320LIMBS; ++i) {
            prev = dif.limbs[i];
            dif.limbs[i] -= carry;
            dif.limbs[i] -= sub.limbs[i];

            if(prev<sub.limbs[i]){
                carry = 1;
            }
            else if(sub.limbs[i]==UINT64_MAX && carry) {
                carry = 1;
            }
            else {
                carry = 0;
            }
        }

        return dif;
    }

    uint320_t& uint320_t::operator-=(const uint320_t& sub) {
        return *this = *this - sub;
    }

    uint320_t& uint320_t::operator--() {
        return *this = *this - uint320_t(1);
    }

    uint320_t uint320_t::operator--(int) {
        uint320_t pre = *this;
        --*this;
        return pre;
    }

    /// This is the ugly part
    uint320_t uint320_t::operator*(const uint320_t& mr) const {
        
        uint320_t pd(0);

    #if(__x86_64 || __x86_64__ || __amd64 || __amd64__ || __aarch64__ || __aarch64)
    #if(_MSC_VER || _PURE_CPP)

        __uint128_t __uint128_product[UINT320LIMBS+1] = {0,0,0,0,0,0};

        for(size_t i=0; i<UINT320LIMBS; ++i) {
            for(size_t j=0; j<UINT320LIMBS-i; ++j) {

                // new implementation
                __uint128_product[i+j] += (__uint128_t)limbs[j] * (__uint128_t)mr.limbs[i];
                uint64_t carry = __uint128_product[i+j] >> 64;
                
                if(carry) {
                    __uint128_product[i+j] = (uint64_t) __uint128_product[i+j];
                    __uint128_product[i+j+1] += carry;
                }
            }
        }

        for(size_t i=0; i<UINT320LIMBS; ++i) {
            pd.limbs[i] = __uint128_product[i];
        }
        
    #elif ((__clang__ || __GNUC__ || __GNUG__ || __MINGW64__) && (__aarch64__ || __aarch64))
    #ifndef _HIDE_WARNING
    #warning using GCC inline asm, please enable optimization flag, recomended : -O2, to enable use C++ implementation instead, enable the -D_PURE_CPP flag.
    #endif

        __uint128_t __uint128_product[UINT320LIMBS+1] = {0,0,0,0,0,0};

        for(size_t i=0; i<UINT320LIMBS; ++i) {
            for(size_t j=0; j<UINT320LIMBS-i; ++j) {

                // new implementation
                __uint128_product[i+j] += (__uint128_t)limbs[j] * (__uint128_t)mr.limbs[i];
                uint64_t carry = __uint128_product[i+j] >> 64;
                
                if(carry) {
                    __uint128_product[i+j] = (uint64_t) __uint128_product[i+j];
                    __uint128_product[i+j+1] += carry;
                }
            }
        }

        for(size_t i=0; i<UINT320LIMBS; ++i) {
            pd.limbs[i] = __uint128_product[i];
        }

    #elif (__clang__ || __GNUC__ || __GNUG__ || __MINGW64__)
    #ifndef _HIDE_WARNING
    #warning using GCC inline asm, please enable optimization flag, recomended : -O2, to enable use C++ implementation instead, enable the -D_PURE_CPP flag.
    #endif
        asm volatile (
            // ------------------- 1
            "movq %[mc0], %%rax\n\t"
            "mulq %[mr0]\n\t"
            "movq %%rax, %[pd0]\n\t"
            "movq %%rdx, %[pd1]\n\t"

            "movq %[mc1], %%rax\n\t"
            "mulq %[mr0]\n\t"
            "addq %%rax, %[pd1]\n\t"
            "adcq %%rdx, %[pd2]\n\t"

            "movq %[mc2], %%rax\n\t"
            "mulq %[mr0]\n\t"
            "addq %%rax, %[pd2]\n\t"
            "adcq %%rdx, %[pd3]\n\t"

            "movq %[mc3], %%rax\n\t"
            "mulq %[mr0]\n\t"
            "addq %%rax, %[pd3]\n\t"
            "adcq %%rdx, %[pd4]\n\t"

            "movq %[mc4], %%rax\n\t"
            "mulq %[mr0]\n\t"
            "addq %%rax, %[pd4]\n\t"

            // ------------------- 2

            "movq %[mc0], %%rax\n\t"
            "mulq %[mr1]\n\t"
            "addq %%rax, %[pd1]\n\t"
            "adcq %%rdx, %[pd2]\n\t"
            "adcq $0, %[pd3]\n\t"
            "adcq $0, %[pd4]\n\t"

            "movq %[mc1], %%rax\n\t"
            "mulq %[mr1]\n\t"
            "addq %%rax, %[pd2]\n\t"
            "adcq %%rdx, %[pd3]\n\t"
            "adcq $0, %[pd4]\n\t"

            "movq %[mc2], %%rax\n\t"
            "mulq %[mr1]\n\t"
            "addq %%rax, %[pd3]\n\t"
            "adcq %%rdx, %[pd4]\n\t"

            "movq %[mc3], %%rax\n\t"
            "mulq %[mr1]\n\t"
            "addq %%rax, %[pd4]\n\t"

            // -------------------- 3

            "movq %[mc0], %%rax\n\t"
            "mulq %[mr2]\n\t"
            "addq %%rax, %[pd2]\n\t"
            "adcq %%rdx, %[pd3]\n\t"
            "adcq $0, %[pd4]\n\t"

            "movq %[mc1], %%rax\n\t"
            "mulq %[mr2]\n\t"
            "addq %%rax, %[pd3]\n\t"
            "adcq %%rdx, %[pd4]\n\t"

            "movq %[mc2], %%rax\n\t"
            "mulq %[mr2]\n\t"
            "addq %%rax, %[pd4]\n\t"

            // -------------------- 4

            "movq %[mc0], %%rax\n\t"
            "mulq %[mr3]\n\t"
            "addq %%rax, %[pd3]\n\t"
            "adcq %%rdx, %[pd4]\n\t"

            "movq %[mc1], %%rax\n\t"
            "mulq %[mr3]\n\t"
            "addq %%rax, %[pd4]\n\t"

            // ------------------- 5

            "movq %[mc0], %%rax\n\t"
            "mulq %[mr4]\n\t"
            "addq %%rax, %[pd4]\n\t"

            :
            [pd0]"+r"(pd.limbs[0]),
            [pd1]"+r"(pd.limbs[1]),
            [pd2]"+r"(pd.limbs[2]),
            [pd3]"+r"(pd.limbs[3]),
            [pd4]"+r"(pd.limbs[4])
            :
            [mr0]"m"(mr.limbs[0]),
            [mr1]"m"(mr.limbs[1]),
            [mr2]"m"(mr.limbs[2]),
            [mr3]"m"(mr.limbs[3]),
            [mr4]"m"(mr.limbs[4]),

            [mc0]"m"(limbs[0]),
            [mc1]"m"(limbs[1]),
            [mc2]"m"(limbs[2]),
            [mc3]"m"(limbs[3]),
            [mc4]"m"(limbs[4])
            : "rax","rdx","cc"
        );
    #else
    #error uint320_t is not supported on this compiler
    #endif
    #else
    #error uint320_t is not supported on 32-bit computers (x86 architectures)
    #endif

        return pd;
    }

    uint320_t& uint320_t::operator*=(const uint320_t& mul) {
        *this = *this * mul;
        return *this;
    }

    /** long division using bits, shifts and subtract */
    uint320_t uint320_t::ss_div(const uint320_t& divisor) const {

        uint320_t
            quotient(0),
            pdvn(0);
        
        uint64_t bit = 0, one = 1, current_index, current_shitval;

        for(size_t i=0; i<UINT320BITS; ++i) {

            current_index = UINT320_MS_LIMB-i/64, current_shitval = i%64;

            pdvn = pdvn << 1;

            bit = limbs[current_index] << current_shitval;
            bit >>= 63;

            pdvn.limbs[UINT320_LS_LIMB] |= bit;

            if(pdvn>=divisor) {
                pdvn -= divisor;
                quotient.limbs[current_index] |= (one << (63-current_shitval));
            }
        }

        return quotient;
    }

    /** long division using bits, shifts and subtract */
    uint320_t uint320_t::ss_mod(const uint320_t& divisor) const {
        
        uint320_t pdvn(0);

        uint64_t bit = 0;

        for(size_t i=0; i<UINT320BITS; ++i) {

            pdvn = pdvn << 1;

            bit = limbs[UINT320_MS_LIMB-i/64] << i%64;
            bit >>= 63;
            
            pdvn.limbs[UINT320_LS_LIMB] |= bit;

            if(pdvn>=divisor) {
                pdvn -= divisor;
            }
        }

        return pdvn;
    }

    uint320_t uint320_t::operator/(const uint320_t& divisor) const {

        int value = divisor.one_or_zero();
        if(value == 0) {
            std::cout << "\nError!!!\nuint320_t operands:\n";
            std::cout << "Dividen = "; printHex();
            std::cout << "Divisor = "; divisor.printHex();
            throw std::domain_error("division by zero is not possible");
        }
        else if(*this == divisor) {
            return uint320_t(1); // remainder zero
        }
        else if(*this < divisor) {
            return uint320_t(0); // remainder *this (dividen)
        }
        else if(value == 1) {
            return *this;
        }
        return this->ss_div(divisor);
    }

    uint320_t& uint320_t::operator/=(const uint320_t& divisor) {
        *this = *this / divisor;
        return *this;
    }

    uint320_t uint320_t::operator%(const uint320_t& divisor) const {

        int value = divisor.one_or_zero();
        if(value == 0) {
            std::cout << "\nError!!!\nuint320_t operands:\n";
            std::cout << "Dividen = "; printHex();
            std::cout << "Divisor = "; divisor.printHex();
            throw std::domain_error("% mod:division by zero is not possible");
        }
        else if(*this == divisor) {
            return uint320_t(0);
        }
        else if(*this < divisor) {
            return *this;
        }
        else if(value == 1) {
            return uint320_t(0);
        }
        return this->ss_mod(divisor);
    }

    uint320_t& uint320_t::operator%=(const uint320_t& divisor) {
        *this = *this % divisor;
        return *this;
    }

    // LEFT SHIFT

    uint320_t uint320_t::operator<<(size_t lshift) const {

        uint320_t result(0,0,0,0,0);

        if(lshift>UINT320BITS)
            return result;

        size_t limb_shifts = lshift / UINT64BITS;
        size_t bit_shifts = lshift % UINT64BITS;

        // shift limbs
        if(limb_shifts) {
            for(int i=limb_shifts; i<UINT320LIMBS; ++i) {
                result.limbs[i] = limbs[(i-limb_shifts)%UINT320LIMBS];
            }
        }
        else {
            result = *this;
        }

        if(bit_shifts) {
            // compute carries.
            uint64_t carries[UINT320_MS_LIMB];
            for(size_t i=0; i<UINT320_MS_LIMB; ++i) {
                carries[i] = result.limbs[i] >> (UINT64BITS-bit_shifts);
            }

            // apply shift to first index.
            result.limbs[UINT320_LS_LIMB] <<= bit_shifts;

            // apply shifts and the carry over to the procceding indecies.
            for(size_t i=1; i<UINT320LIMBS; ++i) {
                result.limbs[i] <<= bit_shifts;
                result.limbs[i] |= carries[i-1];
            }
        }

        return result;
    }

    uint320_t& uint320_t::operator<<=(size_t lshift) {
        return (*this = *this << lshift);
    }

    // RIGHT SHIFT 

    uint320_t uint320_t::operator>>(size_t rshift) const {

        uint320_t result(0,0,0,0,0);

        if(rshift>UINT320BITS)
            return result;

        size_t limb_shifts = rshift / UINT64BITS;
        size_t bit_shifts = rshift % UINT64BITS;

        // shift limbs
        if(limb_shifts) {
            for(size_t i=0; i<(UINT320LIMBS-limb_shifts); ++i) {
                result.limbs[i] = limbs[(i+limb_shifts)%UINT320LIMBS];
            }
        }
        else {
            result = *this;
        }

        if(bit_shifts) {
            // compute carries.
            uint64_t carries[UINT320_MS_LIMB];
            for(size_t i=0; i<UINT320_MS_LIMB; ++i) {
                carries[i] = result.limbs[i+1] << (UINT64BITS-bit_shifts);
            }

            // apply shift to last index.
            result.limbs[UINT320_MS_LIMB] >>= bit_shifts;

            // apply shifts and the carry over to the procceding indecies.
            for(size_t i=0; i<UINT320_MS_LIMB; ++i) {
                result.limbs[i] >>= bit_shifts;
                result.limbs[i] |= carries[i];
            }
        }

        return result;
    }

    uint320_t& uint320_t::operator>>=(size_t rshift) {
        return (*this = *this >> rshift);
    }

    /// the limb[7] will be printed first then 6,5, ..., the limb[0] will be printed last.
    void uint320_t::printHex() const {
        std::cout << "0x";
        for(size_t i=0; i<UINT320LIMBS; ++i)
            printf(PRINT_LIMBHEX,limbs[UINT320_MS_LIMB-i]);
        std::cout << "\n";
    }

    /// the limb[7] will be printed first then 6,5, ..., the limb[0] will be printed last.
    void uint320_t::printBits() const {
        for(size_t i=0; i<UINT320LIMBS; ++i) {
            std::cout << std::bitset<UINT64BITS>(limbs[UINT320_MS_LIMB-i]) ;
        }
        std::cout << "\n";
    }
}

#endif
