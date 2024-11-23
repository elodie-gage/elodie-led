.DEFAULT_GOAL := compile

PROJ=/Users/tim/code/platformio-play/play1

compile:
	g++ -std=c++17 -shared -fPIC \
		-include simulation.h \
		-I${PROJ}/include  \
		-I${PROJ}/.pio/libdeps/lolin_d32/FastLED/src \
		-o simulation.so \
		${PROJ}/src/led_race.cpp \
		${PROJ}/src/test_pattern.cpp \
		simulation.cpp
		