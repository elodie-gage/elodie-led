.DEFAULT_GOAL := compile

PROJ=/Users/tim/code/platformio-play/play1

compile:
	g++ -std=c++17 -shared -fPIC \
		-include simulation.h \
		-I${PROJ}/include  \
		-I${PROJ}/.pio/libdeps/lolin_d32/FastLED/src \
		-o simulation.so \
		${PROJ}/.pio/libdeps/lolin_d32/FastLED/src/hsv2rgb.cpp \
		${PROJ}/src/led_race.cpp \
		${PROJ}/src/test_pattern.cpp \
		${PROJ}/src/rainbow.cpp \
		simulation.cpp
		