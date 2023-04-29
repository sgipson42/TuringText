
#include "Delegator.h"
#include <iostream>
using namespace std;

void Delegator::handle_request(string phonenum, string msg) {
    cout << phonenum << ": " << msg << endl;
}
