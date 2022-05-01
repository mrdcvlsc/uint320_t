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
const static std::string TEST_NAME = "uint320_t base10 output "; 

void ASSERT_STRING(const std::string& A, const std::string& B, const std::string& TEST_MESSAGE);


uint320_t fib(size_t nth) {
    uint320_t base0(0,0,0,0,0), base1(0,0,0,0,1);
    uint320_t nthfib(0,0,0,0,0);
    for(size_t i=2; i<=nth; ++i) {
        nthfib = base0 + base1;
        base0 = base1;
        base1 = nthfib;
    }
    return nthfib;
}

uint320_t fac(size_t n) {
    uint320_t factorial(1);
    uint320_t iter = factorial;

    for(size_t i=1; i<=n; ++i, iter++) {
        factorial = factorial * iter;
    }

    return factorial;
}

int main() {
    std::cout << "\n---------------------------------\n";
    std::cout << TEST_NAME << "\n=================================\n";

    // TEST VARIABLES
    std::string CFAC67 = "36471110918188685288249859096605464427167635314049524593701628500267962436943872000000000000000";
    std::string CFIB250 = "7896325826131730509282738943634332893686268675876375";

    std::string CONE = "1";
    std::string CZERO = "0";
    std::string CTEN = "10";
    std::string CO125 = "125";

    // ANSWERS
    std::string FAC67 = fac(67).toBase10String();
    std::string FIB250 = uint320_t(0,0,0x151ae2a8207e, 0xf4425d98671de203, 0xbfb894e8f601e617).toBase10String();

    std::string ONE = uint320_t(1).toBase10String();
    std::string ZERO = uint320_t(0).toBase10String();
    std::string TEN = uint320_t(10).toBase10String();
    std::string O125 = uint320_t(125).toBase10String();

    // 3647111091818868528824985909660546442716763531404952459370162850026796243694387200000000000000
    // 3647111091818868528824985909660546442716763531404952459370162850026796243694387200000000000000
    // 36471110918188685288249859096605464427167635314049524593701628500267962436943872000000000000000

    std::cout << "ZERO = ("<< ZERO << ")\n";

    // TESTING ANSWER
    ASSERT_STRING(CFAC67,FAC67,"FAC67");
    ASSERT_STRING(CFIB250,FIB250,"FIB250");

    ASSERT_STRING(CONE,ONE,"ONE");
    ASSERT_STRING(CZERO,ZERO,"ZERO");
    ASSERT_STRING(CTEN,TEN,"TEN");
    ASSERT_STRING(CO125,O125,"125");



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


void ASSERT_STRING(const std::string& A, const std::string& B, const std::string& TEST_MESSAGE) {
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