.DEFAULT_GOAL := compile

PROJ=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))..

compile:
	g++ -std=c++17 -shared -fPIC \
		-include simulation.h \
		-I${PROJ}/include  \
		-I${PROJ}/.pio/libdeps/seeed_xiao_esp32c3/FastLED/src \
		-o simulation.so \
		${PROJ}/.pio/libdeps/seeed_xiao_esp32c3/FastLED/src/hsv2rgb.cpp \
		${PROJ}/.pio/libdeps/seeed_xiao_esp32c3/FastLED/src/colorutils.cpp \
		${PROJ}/src/patterns/*.cpp \
		simulation.cpp

clean:
	rm simulation.so
