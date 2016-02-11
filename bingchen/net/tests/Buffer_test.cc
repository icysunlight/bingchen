#include "Buffer.cc"

#include <iostream>
#include <string>

using namespace bingchen;

int main() {

    Buffer buf;

    while (1) {
        std::string tmp;
        std::cin >> tmp;
        buf.append(tmp.c_str(),tmp.size());
        std::cout << buf.retrieveAsString() << std::endl; 
    }

    return 0;
}
