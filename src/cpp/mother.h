#ifndef WORLD_H
#define WORLD_H 

#include "person.h"

using namespace std;

class Mother: public Person {
public:
    Mother(Person* person);
    void step_year();

private:
    long babies;
    void give_birth();
};

#endif
