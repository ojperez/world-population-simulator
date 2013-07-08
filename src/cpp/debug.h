#ifndef DEBUG_H
#define DEBUG_H 

#include <mutex>

using namespace std;

class Debug {
public:
    static recursive_mutex print_lock;
    lock_guard<recursive_mutex> l;

    Debug();
    friend ostream &operator<<(ostream &os, Debug const &l);
};

#endif
