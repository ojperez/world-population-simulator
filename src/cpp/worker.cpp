#include <iostream>
#include <map>
#include <thread>
#include <mutex>
#include <atomic>
#include <map>

#include "worker.h"
#include "world.h"
#include "world_object.h"
#include "debug.h"

using namespace std;

atomic<int> Worker::copy_done(0);
mutex Worker::begin_work_lock;
condition_variable Worker::begin_work;

Worker::Worker(int _batch_size, int _seek, World* _world) {
    this->batch_size = _batch_size;
    this->seek = _seek;
    this->world = _world;
}

void Worker::work() {
    //cout << Debug() << "work()" << " [Thread " << this->seek << "]" << endl;

    // get a copy of the world objects
    this->objects = this->world->objects;
    Worker::copy_done++;

    if (Worker::copy_done_test()) {
        //cout << Debug() << "============================= work() release" << " [Thread " << this->seek << "]" << endl;

        // wake up
        Worker::begin_work.notify_all();
    }
    else {
        //cout << Debug() << "work() waiting" << " [Thread " << this->seek << "]" << endl;

        // wait until we're allowed to start
        unique_lock<mutex> l(Worker::begin_work_lock);
        Worker::begin_work.wait(l, Worker::copy_done_test);

        // wake up
        Worker::begin_work.notify_all();
    }

    this->age();
}

bool Worker::copy_done_test() {
    return Worker::copy_done.load() == thread::hardware_concurrency();
}

void Worker::age() {
    //cout << Debug() << "Start of work. Year = " << this->world->years << ", Size = " << this->world->size() << " [Thread " << this->seek << "]" << endl;

    int count;
    map<string, World_Object*>::iterator it;

    // Seek ahead
    for (count = 0, it = this->objects.begin(); it != this->objects.end() && count < this->batch_size * this->seek; ++it, count++);

    // Process
    for (count = 0; it != this->objects.end() && count < this->batch_size; ++it, count++) {
        World_Object* obj = it->second;

        if (!obj)
            continue;

        if (obj->is_enabled()) {
            obj->step_year();
        }
        else {
            this->world->remove(obj);
            delete obj;
        }
    }

    //cout << Debug() << "End of work. Year = " << this->world->years << ", Size = " << this->world->size() << " [Thread " << this->seek << "]" << endl;
}
