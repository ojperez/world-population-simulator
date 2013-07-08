#ifndef WORLD_OBJECT_H
#define WORLD_OBJECT_H 

#include <mutex>

using namespace std;

class World_Object { 
public:
    string id = "";
    bool enabled = false;
    recursive_mutex m;
    static recursive_mutex id_lock;

    World_Object();
    ~World_Object();

    string uniqid();
    bool is_enabled(int s = -1);
    virtual void step_year();
};

#endif
