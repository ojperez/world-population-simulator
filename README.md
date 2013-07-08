World Population Simulator
==========================

The World Population Simulator is a program that calculates population growth. You can specify:

- total number of years
- initial conditions (eg. number of males, females, mothers, etc).
- maximum life expectancy
- average death rate
- probability of being male or female
- average number of children per mother
- lower and upper bounds on the age of mothers

The program will output the total world population for each year.


Plugins
--------------
Plugins can be written to add new features to the simulator, such as:

- families: tracking family trees through hundreds or thousands of generations
- economies: compare different economies to see which most greatly influences world population growth
- countries: compare the effect of various government policies (immigration, foreign policy, etc) on world population growth
- natural disasters: compare how different types affect world population growth
- human diseases: compare how diseases that affect certain people affect world population growth


Online Demo
----------------

Coming soon! Please send me an email (yonas at fizk.net) if you'd like to help design the demo website.



Source Code
--------------

You can find a multi-threaded C++ version in the "src/cpp" directory, and a PHP version under "src/php". The PHP version was first written as a quick prototype. The C++ version was written to make use of all available CPU cores.


License
--------------

This software is licensed under the The GNU General Public License v3.0. 
