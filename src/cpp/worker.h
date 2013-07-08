#ifndef WORKER_H
#define WORKER_H 

#include <map>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;

class World;
class World_Object;
class Worker {
public:
    int batch_size;
    int seek;

    map<string, World_Object*> objects;
    World* world;
    static mutex begin_work_lock;
    static condition_variable begin_work;
    static atomic<int> copy_done;

    Worker(int _batch_size, int _seek, World* _world);
    void work();
    void complete();
    static void print(string s);
    static bool copy_done_test();

private:
    void age();
};

#endif
