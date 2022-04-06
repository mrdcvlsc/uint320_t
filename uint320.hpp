#ifndef idMRDCVLSC_ChaCha20_POLY1305_HP
#define idMRDCVLSC_ChaCha20_POLY1305_HP

#include <iostream>
#include <cstring>
#include <cmath>
#include <bitset>
#include <utility>

//============================== uint320 ==============================

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

/// uint320 least significant limb index.
#define UINT320_LS_LIMB 0

/// uint320 most significant limb index.
#define UINT320_MS_LIMB 4

#define LESS -1
#define EQUAL 0
#define GREAT 1

#if (__MINGW64__ || __MINGW64)
typedef unsigned long long ulongint;
#define PRINT_LIMBHEX "%016llx "
#elif (__clang__ || __GNUC__ || __GNUG__)
typedef unsigned long ulongint;
#define PRINT_LIMBHEX "%016lx "
#else
#error not supported
#endif

/// for intel & amd x86_64 & x64 architectures only.
class uint320 {
    public:

    /**least significant quadword starting from index 0
     * up to index 7 the most significant quadword.*/
    ulongint *limbs;

    uint320();
    uint320(ulongint num);
    uint320(const unsigned char *input_bytes, size_t bytes);
    uint320(
        ulongint n4, ulongint n3, ulongint n2, ulongint n1, ulongint n0
    );

    /// copy constructor.
    uint320(const uint320& src);

    /// move constructor.
    uint320(uint320&& src) noexcept;

    /// copy assignment.
    uint320& operator=(const uint320& src);

    /// move assignment.
    uint320& operator=(uint320&& src);

    ~uint320();

    /// @return returns; 0 : if uint320 == 0, 1 : if uint320 == 1, and -1 : if uint320 != to 0 or 1.
    int one_or_zero() const;

    /// @return returns; -1 : if less than, 0 : if equal, 1 : if greater than.
    int compare(const uint320& with) const;

    bool operator==(const uint320& with) const;
    bool operator!=(const uint320& with) const;
    bool operator<(const uint320& with) const;
    bool operator>(const uint320& with) const;
    bool operator<=(const uint320& with) const;
    bool operator>=(const uint320& with) const;

    /// @return returns true if the uint320 is not zero.
    bool boolean() const;

    bool operator&&(const uint320& with) const;
    bool operator||(const uint320& with) const;
    bool operator!() const;

    uint320 operator&(const uint320& with) const;
    uint320 operator|(const uint320& with) const;
    uint320 operator^(const uint320& with) const;
    uint320 operator~() const;

    uint320& operator&=(const uint320& with);
    uint320& operator|=(const uint320& with);
    uint320& operator^=(const uint320& with);

    uint320 operator+(const uint320& add) const;
    uint320& operator+=(const uint320& add);
    uint320& operator++();
    uint320 operator++(int);

    uint320 operator-(const uint320& sub) const;
    uint320& operator-=(const uint320& sub);
    uint320& operator--();
    uint320 operator--(int);

    /// This is the ugly part.
    uint320 operator*(const uint320& mr) const;
    uint320& operator*=(const uint320& mul);

    /** long division using bits, shifts and subtract. */
    uint320 ss_div(const uint320& divisor) const;

    /** long division using bits, shifts and subtract. */
    uint320 ss_mod(const uint320& divisor) const;

    uint320 operator/(const uint320& divisor) const;
    uint320& operator/=(const uint320& divisor);

    uint320 operator%(const uint320& divisor) const;
    uint320& operator%=(const uint320& divisor);

    // LEFT SHIFT
    
    uint320 operator<<(size_t lshift) const;
    uint320& operator<<=(size_t lshift);

    // RIGHT SHIFT 

    uint320 operator>>(size_t rshift) const;
    uint320& operator>>=(size_t rshift);

    /// the limb[7] will be printed first then 6,5, ..., the limb[0] will be printed last.
    void printHex() const;

    /// the limb[7] will be printed first then 6,5, ..., the limb[0] will be printed last.
    void printBits() const;
};

#endif