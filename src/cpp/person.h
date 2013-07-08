#ifndef PERSON_H
#define PERSON_H 

#include <mutex>
#include "world_object.h"
using namespace std;

class Person: public World_Object {
public:
    int max_age;
    int age;
    bool is_girl;

    Person(int age = 0);
    void step_year();
    void become_mother();
};

#endif
