#include <iostream>
#include <map>
#include <mutex>
#include <cstdlib>
#include "person.h"
#include "mother.h"

Person::Person(int age) {
    this->max_age = 100; 
    this->is_girl = false;
    World_Object();
    this->age = age;

    if (this->age == 0)
        this->is_girl = (bool)(rand() % 2);
}

void Person::step_year() {
    lock_guard<recursive_mutex> lck(this->m); 

    World_Object::step_year();
    if (!this->is_enabled())
        return;

    this->age++;
    if (this->age >= this->max_age) {
        this->is_enabled(0);
    } else if (this->is_girl && this->age == 15) {
        this->become_mother();
    }
}

void Person::become_mother() {
    new Mother(this);
    this->is_enabled(0);
}
