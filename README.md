
Control code for a string of LEDS arranged around 2 sides of my bedroom.

The LEDS are arranged in roughly this shape:

```
o o o o o o o o o o o o o o o o o
                                o
                                o
                                o
                                o
                                o

```
There are 372 in total.

# Patterns

Various patterns can be shown. Each pattern is an implementation of `PatternRenderer`, stored in `src/patterns/`

The render method of the pattern renderer is called once every 20ms.

# Simulation

The `simulation/` folder contains python code to run a simulation of the real LED string. This is set up to use pipenv:

```
cd simulation
pipenv install
make && pipenv run python simulation.py
````

The simulated pattern is controlled in `simulation.cpp`.
