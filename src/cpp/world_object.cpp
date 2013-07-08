#include <iostream>
#include <fstream>
#include <mutex>
#include "world_object.h"
#include "world.h"
#include "debug.h"

class World;
extern World* world;

World_Object::World_Object() {
    this->id = this->uniqid();
    this->enabled = true;

    world->add(this);
}

World_Object::~World_Object() {
    this->enabled = false;

    if (world)
        world->remove(this);
}

string World_Object::uniqid() {
    ifstream file;
    string uuid;

    file.open("/proc/sys/kernel/random/uuid");
    if (file.is_open()) {
        while (!file.eof()) {
            file >> uuid;
        }
    }

    file.close();
    return uuid;
}

void World_Object::step_year() {
}

bool World_Object::is_enabled(int s) {
    lock_guard<recursive_mutex> l(this->m);

    if (s >= 0 && s <= 1)
        this->enabled = (bool)s;

    return this->enabled;
}
