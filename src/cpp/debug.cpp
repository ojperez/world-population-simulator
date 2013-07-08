#include <iostream>
#include <mutex>

#include "debug.h"

recursive_mutex Debug::print_lock;

Debug::Debug() : l(Debug::print_lock) {}

ostream &operator<<(ostream &os, Debug const &l) {
    return os;
}
