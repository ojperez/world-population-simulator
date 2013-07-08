#ifndef WORLD_H
#define WORLD_H 

#include <iostream>
#include <map>
#include <thread>
#include <mutex>

using namespace std;

class World_Object;
class Person;
class World {
public:
    long years;
    map<string, World_Object*> objects;
    static recursive_mutex objects_lock;
    static recursive_mutex year_lock;
    static recursive_mutex size_lock;

    World();
    ~World();

    void add(World_Object* obj);
    void remove(World_Object* obj);
    void age(long years, int update_frequency);
    size_t size();
    void populate(long population);
    void increase_year();
    int rand(int low, int high);
};

#endif
