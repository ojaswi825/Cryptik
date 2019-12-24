#include<iostream>
#include"Cryptik.h"

int main(void) {

    Cryptik Cr;

    std::string hash = Cr.encrypt("ojaswi");
    
    std::cout << "Compare with ojaswi: " << Cr.compare(hash, "ojaswi") << std::endl;
    std::cout << "Compare with vinays: " << Cr.compare(hash, "vinays") << std::endl;

    return 0;
}