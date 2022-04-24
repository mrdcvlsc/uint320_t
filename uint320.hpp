#ifndef idMRDCVLSC_ChaCha20_POLY1305_HP
#define idMRDCVLSC_ChaCha20_POLY1305_HP

#include <iostream>
#include <cstring>
#include <cmath>
#include <bitset>
#include <utility>

namespace rushed {
    //============================== uint320_t ==============================

    #define UINT128BITS 128
    #define UINT128BITS_2x 256
    #define UINT127BITS 127
    #define UINT128BYTES 16

    #if (__x86_64__ || __ia64__ ||__amd__64__)
    #define ULONGBITS 64
    #define ULONGBITS_2x 128
    #else
    #define ULONGBITS 32
    #define ULONGBITS_2x 64
    #endif

    // -----------------------------

    #define UINT64BYTES 8
    #define UINT64BITS 64

    #define UINT320LIMBS 5
    #define UINT320BYTES 40
    #define UINT319BITS 319
    #define UINT320BITS 320
    #define UINT320BITS_x2 640

    /// uint320_t least significant limb index.
    #define UINT320_LS_LIMB 0

    /// uint320_t most significant limb index.
    #define UINT320_MS_LIMB 4

    #define LESS -1
    #define EQUAL 0
    #define GREAT 1

    #if (__MINGW64__ || __MINGW64)
    #define PRINT_LIMBHEX "%016llx "
    #elif (__clang__ || __GNUC__ || __GNUG__)
    #define PRINT_LIMBHEX "%016lx "
    #else
    #error not supported
    #endif

    /// for intel & amd x86_64 & x64 architectures only.
    class uint320_t {
        public:

        /**least significant quadword starting from index 0
         * up to index 7 the most significant quadword.*/
        uint64_t limbs[5];

        uint320_t();
        uint320_t(uint64_t num);
        uint320_t(const unsigned char *input_bytes, size_t bytes);
        uint320_t(
            uint64_t n4, uint64_t n3, uint64_t n2, uint64_t n1, uint64_t n0
        );

        /// copy constructor.
        uint320_t(const uint320_t& src);

        /// copy assignment.
        uint320_t& operator=(const uint320_t& src);

        ~uint320_t();

        /// @return returns; 0 : if uint320_t == 0, 1 : if uint320_t == 1, and -1 : if uint320_t != to 0 or 1.
        int one_or_zero() const;

        /// @return returns; -1 : if less than, 0 : if equal, 1 : if greater than.
        int compare(const uint320_t& with) const;

        bool operator==(const uint320_t& with) const;
        bool operator!=(const uint320_t& with) const;
        bool operator<(const uint320_t& with) const;
        bool operator>(const uint320_t& with) const;
        bool operator<=(const uint320_t& with) const;
        bool operator>=(const uint320_t& with) const;

        /// @return returns true if the uint320_t is not zero.
        bool boolean() const;

        bool operator&&(const uint320_t& with) const;
        bool operator||(const uint320_t& with) const;
        bool operator!() const;

        uint320_t operator&(const uint320_t& with) const;
        uint320_t operator|(const uint320_t& with) const;
        uint320_t operator^(const uint320_t& with) const;
        uint320_t operator~() const;

        uint320_t& operator&=(const uint320_t& with);
        uint320_t& operator|=(const uint320_t& with);
        uint320_t& operator^=(const uint320_t& with);

        uint320_t operator+(const uint320_t& add) const;
        uint320_t& operator+=(const uint320_t& add);
        uint320_t& operator++();
        uint320_t operator++(int);

        uint320_t operator-(const uint320_t& sub) const;
        uint320_t& operator-=(const uint320_t& sub);
        uint320_t& operator--();
        uint320_t operator--(int);

        /// This is the ugly part.
        uint320_t operator*(const uint320_t& mr) const;
        uint320_t& operator*=(const uint320_t& mul);

        /** long division using bits, shifts and subtract. */
        uint320_t ss_div(const uint320_t& divisor) const;

        /** long division using bits, shifts and subtract. */
        uint320_t ss_mod(const uint320_t& divisor) const;

        uint320_t operator/(const uint320_t& divisor) const;
        uint320_t& operator/=(const uint320_t& divisor);

        uint320_t operator%(const uint320_t& divisor) const;
        uint320_t& operator%=(const uint320_t& divisor);

        // LEFT SHIFT
        
        uint320_t operator<<(size_t lshift) const;
        uint320_t& operator<<=(size_t lshift);

        // RIGHT SHIFT 

        uint320_t operator>>(size_t rshift) const;
        uint320_t& operator>>=(size_t rshift);

        /// the limb[7] will be printed first then 6,5, ..., the limb[0] will be printed last.
        void printHex() const;

        /// the limb[7] will be printed first then 6,5, ..., the limb[0] will be printed last.
        void printBits() const;
    };
}

#endif