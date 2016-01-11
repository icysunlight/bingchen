#include "TimeStamp.h"
#include <iostream>

using namespace std;

int main() {
    cout << bingchen::TimeStamp::now().toFormattedString(true) << endl;
    return 0;
}
