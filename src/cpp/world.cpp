#include <map>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <vector>
#include <condition_variable>
#include "world.h"
#include "world_object.h"
#include "worker.h"
#include "person.h"
#include "debug.h"

// Static variables
recursive_mutex World::objects_lock;
recursive_mutex World::year_lock;
recursive_mutex World::size_lock;

World::World() {
    srand(time(NULL));
    this->years = 0;
}

World::~World() {
    this->objects.clear();
}

void World::add(World_Object* obj) {
    lock_guard<recursive_mutex> lck(World::objects_lock); 
    this->objects[obj->id] = obj;
}

void World::remove(World_Object* obj) {
    lock_guard<recursive_mutex> lck(World::objects_lock); 
    this->objects.erase(obj->id);
}

void World::increase_year() {
    lock_guard<recursive_mutex> lck(World::year_lock); 
    this->years++;
}

void World::age(long years, int update_frequency) {
    int max_threads = thread::hardware_concurrency();
    int batch_size;
    vector<Worker*> workers;
    vector<thread> threads;

    for (long i = 0; i < years; i++) {
        this->increase_year();
        batch_size = floor(this->size() / max_threads); // TODO: include remainder in the last thread

        Worker::copy_done.store(0);
        for (int i = 0; i < max_threads; i++) {
            Worker* worker = new Worker(batch_size, i, this);
            workers.push_back(worker);
            thread t(&Worker::work, worker);
            threads.push_back(move(t));
        }

        //cout << Debug() << "================================== Begin wait, Year " << this->years << endl;
        for (auto& t: threads) {
            t.join();
        }

        //cout << Debug() << "================================== End wait, Year " << this->years << endl;

        for (auto worker: workers) {
            if (worker)
                delete worker;
        }

        workers.clear();
        threads.clear();

        if (this->years % update_frequency == 0)
            cout << Debug() << "World population in year " << this->years << ": " << this->size() << endl;
    }
}

size_t World::size() {
    lock_guard<recursive_mutex> lck(World::size_lock); 
    return this->objects.size();
}

int World::rand(int low, int high) {
   return std::rand() % (high - low + 1) + low;
}

void World::populate(long population) {
    this->objects.clear();
    long mothers = floor(population * .30);
    long age;
    Person* person;

    //cout << Debug() << "Initial population: " << population << endl;
    //cout << Debug() << "Create mothers (" << mothers << ")" << endl;
    for (long i = 0; i < mothers; i++) {
        age = this->rand(16, 50);    // 16 years old - 50 years old
        person = new Person(age);
        person->become_mother();
        delete person;
    }

    population -= mothers;

    //cout << Debug() << "Create everyone else" << endl;
    for (long i = 0; i < population; i++) {
        age = this->rand(1, 70);     // 1 year old - 70 years old
        new Person(age);
    }
}
