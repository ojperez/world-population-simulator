<?php

class World_Object { 
    public $id = null;
    public $enabled = false;

    public function __construct() {
        $this->id = uniqid();
        $this->enabled = true;

        global $world;
        $world->add($this);
    }

    public function __destruct() {
        $this->enabled = false;

        global $world;
        if (isset($world))
            $world->remove($this);
    }

    public function step_year() {
    }

    public function enabled($s = null) {
        if ($s !== null && is_bool($s))
            $this->enabled = $s;

        return $this->enabled;
    }
}

class Person extends World_Object {
    public $max_age = 100; 
    public $age = 0; 
    public $is_girl = false;

    public function __construct($age = 0) {
        parent::__construct();
        $this->age = $age;

        if ($this->age == 0)
            $this->is_girl = mt_rand(0, 1);
    }

    public function __destruct() {
        parent::__destruct();
    }

    public function step_year() {
        parent::step_year();
        if (!$this->enabled())
            return;

        $this->age++;
        if ($this->age >= $this->max_age) {
            $this->enabled(false);
        } else if ($this->is_girl && $this->age == 15) {
            $this->become_mother();
        }
    }

    public function become_mother() {
        global $world;
        new Mother($this);
        $this->enabled(false);
    }
}

class Mother extends Person {
    public $babies = 0;

    public function __construct($person) {
        parent::__construct($person->age);
        $this->is_girl = true;
    }

    public function __destruct() {
        parent::__destruct();
    }

    public function step_year() {
        if ($this->enabled()) {
            $this->give_birth();
            parent::step_year();
        }
    }

    public function give_birth() {
        global $world;
        new Person();
    }
}

class World {
    public $objects = null;
    public $age = 0;

    public function __construct() {
        $this->objects = array();
    }

    public function __destruct() {
        foreach ($this->objects as &$object) {
            unset($object);
        }
    }

    public function add($object) {
        $this->objects[$object->id] = $object;
    }

    public function remove($object) {
        unset($this->objects[$object->id]);
    }

    public function age($years, $update_frequency) {
        for ($i = 0; $i < $years; $i++) {
            $this->age++;

            foreach ($this->objects as &$object) {
                $object->step_year();

                if (!$object->enabled()) {
                    unset($object);
                }
            }

            if ($this->age % $update_frequency == 0)
                echo "World population in year " . $this->age . ': ' . $this->size() . "\n";
        }
    }

    public function size() {
        return count($this->objects);
    }

    public function populate($population) {
        $this->objects = array();
        $mothers = floor($population * .30);

        for ($i = 0; $i < $mothers; $i++) {
            $age = mt_rand(16, 70);
            $person = new Person($age);
            $person->become_mother();
            unset($person);
        }

        $population -= $mothers;
        
        for ($i = 0; $i < $population; $i++) {
            $age = mt_rand(1, 70);
            new Person($age);
        }
    }
}

function run($size, $years) {
    global $world;

    // Create the initial conditions.
    $world->populate($size);

    // Grow the population, and print the world population to screen every 10 years. 
    $world->age($years, 10);
}

$world = new World();
$initial_world_size = 70;
$total_years = 1000;

run($initial_world_size, $total_years);
