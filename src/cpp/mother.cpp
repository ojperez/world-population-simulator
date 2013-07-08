#include <iostream>
#include <map>
#include "mother.h"

using namespace std;

Mother::Mother(Person* person) {
    this->babies = 0;
    Person(person->age);
    this->is_girl = true;
}

void Mother::step_year() {
    {
        lock_guard<recursive_mutex> l(this->m);

        if (!this->is_enabled())
            return;

        if (this->babies < 5 && this->age < 50) {
            this->give_birth();
        }
    }

    Person::step_year();
}

void Mother::give_birth() {
    new Person();
    this->babies++;
}
