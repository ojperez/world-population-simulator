#include <iostream>
#include <fstream>
#include <thread>
#include "world.h"

using namespace std;

// Global world variable, accessed by other classes.
World* world = new World();

int main() {
    int initial_world_size = 70;
    int total_years = 1000;

    // Create the initial conditions.
    world->populate(initial_world_size);

    // Grow the population, and print the world population to screen every 10 years. 
    world->age(total_years, 10);

    cout << "Total human population: " << world->size() << endl;
}
