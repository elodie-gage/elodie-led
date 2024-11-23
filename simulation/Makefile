.DEFAULT_GOAL := compile

PROJ=/Users/tim/code/platformio-play/play1

compile:
	gcc -std=c++17 -shared -fPIC \
		-include simulation.h \
		-I${PROJ}/include  \
		-I${PROJ}/.pio/libdeps/lolin_d32/FastLED/src \
		-o led_race.so \
		${PROJ}/src/led_race.cpp
		