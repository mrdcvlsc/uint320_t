#include <iostream>
#include <utility>
#include <vector>

#ifndef _MAKE_LIB
#include "../Header-Mode-uint320.hpp"
#else
#include <uint320.hpp>
#endif

using namespace rushed;

std::vector<bool> TEST_RESULTS;
const static std::string TEST_NAME = "Left Shifts";

void ASSERT_UINT512(const uint320_t& A, const uint320_t& B, const std::string& TEST_MESSAGE);

template<typename T>
void ASSERT_ARRAY(T* A, T* B, size_t length, std::string TEST_MESSAGE, std::vector<bool>& RESULTS);

void printBytes(unsigned char* bytearray, size_t len) {
    for(size_t i=0; i<len; ++i) {
        printf("%02x ", bytearray[i]);
    }
    std::cout << "\n";
}

int main() {
    std::cout << "\n---------------------------------\n";
    std::cout << TEST_NAME << "\n=================================\n";

    // TEST VARIABLES
    uint64_t max = 0xffffffffffffffff;
    uint320_t MAX(max,max,max,max,max);
    uint320_t ZERO(0,0,0,0,0);
    uint320_t CLS032(max,max,max,max,0xffffffff00000000);
    uint320_t CLS064(max,max,max,max,0);
    uint320_t CLS096(max,max,max,0xffffffff00000000, 0);
    uint320_t CLS128(max,max,max,0,0);
    uint320_t CLS160(max,max,0xffffffff00000000,0,0);
    uint320_t CLS192(max,max,0,0,0);
    uint320_t CLS256(max,0,0,0,0);
    uint320_t CLS500(0,0,0,0,0);

    // uint320_t CLS000 = 

    // ANSWERS
    uint320_t LS000 = MAX << 0;
    uint320_t LS032 = MAX << 32;
    uint320_t LS064 = MAX << 64;
    uint320_t LS096 = MAX << 96;
    uint320_t LS128 = MAX << 128;
    uint320_t LS160 = MAX << 160;
    uint320_t LS192 = MAX << 192;
    uint320_t LS256 = MAX << 256;
    uint320_t LS500 = MAX << 500;
    uint320_t LS512 = MAX << 512;
    uint320_t LS600 = MAX << 600;

    // TESTING ANSWER
    ASSERT_UINT512(LS000, MAX,    "MAX <<   0");
    ASSERT_UINT512(LS032, CLS032, "MAX <<  32");
    ASSERT_UINT512(LS064, CLS064, "MAX <<  64");
    ASSERT_UINT512(LS096, CLS096, "MAX <<  96");
    ASSERT_UINT512(LS128, CLS128, "MAX << 128");
    ASSERT_UINT512(LS160, CLS160, "MAX << 160");
    ASSERT_UINT512(LS192, CLS192, "MAX << 192");
    ASSERT_UINT512(LS256, CLS256, "MAX << 256");
    ASSERT_UINT512(LS500, CLS500, "MAX << 500");
    ASSERT_UINT512(LS512, ZERO, "MAX << 512");
    ASSERT_UINT512(LS600, ZERO, "MAX << 600");

    // SUMMARY OF RESULTS
    
    size_t failed_cnt = 0;
    for(auto e : TEST_RESULTS) {     
        if(!e) failed_cnt++;
    }

    if(TEST_RESULTS.size()) {
        std::cout << "---------------------------------\n";
        std::cout << TEST_NAME << " RESULT:" << "\n";
        if(!failed_cnt) {
            std::cout << "\tALL test PASSED\n";
            std::cout << "---------------------------------\n";
            return 0;
        }
        else {
            std::cout << "\tSOME test FAILED\n";
            std::cout << "---------------------------------\n";
            return 1;
        }
    }
}


void ASSERT_UINT512(const uint320_t& A, const uint320_t& B, const std::string& TEST_MESSAGE) {
    std::cout << TEST_NAME << ":" << TEST_MESSAGE << " : ";
    if(A!=B) {
        std::cout << "FAILED\n";
        TEST_RESULTS.push_back(false);
    }
    else {
        std::cout << "PASSED\n";
        TEST_RESULTS.push_back(true);
    }
}

template<typename T>
void ASSERT_ARRAY(T* A, T* B, size_t length, std::string TEST_MESSAGE, std::vector<bool>& RESULTS) {
    std::cout << ":" << TEST_MESSAGE << " : ";
    bool result_passed = true;
    for(size_t i=0; i<length; ++i) {
        if(A[i]!=B[i]) {
            result_passed = false;
            break;
        }
    }

    if(!result_passed) {
        std::cout << "FAILED\n";
    }
    else {
        std::cout << "PASSED\n";
    }
    RESULTS.push_back(result_passed);
}