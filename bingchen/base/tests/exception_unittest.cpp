#include "exception.h"
#include "stdio.h"


class bar {
public :
        int foo() {
        throw bingchen::exception("foo");
    }
};

void test() {
    bar b;
    b.foo();
}

int main() {
    try {
        test();
    }
    catch (const bingchen::exception& exp) {
        printf("%s\n",exp.what());
        printf("%s\n",exp.getBackTrace());
    }
}
