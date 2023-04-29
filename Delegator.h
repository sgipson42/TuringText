#ifndef DELEGATOR_H
#define DELEGATOR_H

#include <string>
using namespace std;

class Delegator {
public:
    void handle_request(string phonenum, string msg);
};

#endif

