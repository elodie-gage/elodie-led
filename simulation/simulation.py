import ctypes
import pygame
import time
import sys

# Load the compiled C library
led_race = ctypes.CDLL('./led_race.so')

# Constants
LEDS_SIDE = 100
LEDS_ARCH = 50
LED_SIZE = 4
SPACING = 1
R2O2 = 0.70710678
NUM_LEDS = LEDS_SIDE * 2 + LEDS_ARCH * 2
WINDOW_WIDTH = LEDS_ARCH * 2 * (LED_SIZE+SPACING)
WINDOW_HEIGHT = LEDS_ARCH *  (LED_SIZE+SPACING) + LEDS_SIDE * (LED_SIZE+SPACING)
BACKGROUND_COLOR = (0, 0, 0)
LED_OFF_COLOR = (0, 0, 0)

# Initialize pygame
pygame.init()
screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption("LED Simulator")

# LED buffer to hold RGB values
ledsArray = (ctypes.c_uint8 * (NUM_LEDS * 3))()
offsetPattern = ctypes.c_int(0)
lastUpdate = ctypes.c_ulong(0)

# Function to draw LEDs
def draw_leds():
    screen.fill(BACKGROUND_COLOR)

    position = (10.0, 10.0)

    for i in range(0, NUM_LEDS):
        r = ledsArray[i * 3 + 0]
        g = ledsArray[i * 3 + 1]
        b = ledsArray[i * 3 + 2]
        color = (r, g, b)

        if i < 100:
            position = (position[0], position[1]+1)
        elif i < 150:
            position = (position[0]+R2O2, position[1]+R2O2)
        elif i < 200:
            position = (position[0]+R2O2, position[1]-R2O2)
        else:
            position = (position[0], position[1]-1)

        x = round(position[0] * (LED_SIZE + SPACING))
        y = WINDOW_HEIGHT - round(position[1] * (LED_SIZE + SPACING))

        pygame.draw.circle(screen, color, (x + LED_SIZE // 2, y + LED_SIZE // 2), LED_SIZE // 2)
        
    pygame.display.flip()

try:
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        led_race.led_race_loop(ledsArray)
        draw_leds()
        time.sleep(0.01)  # Match the 10 ms update interval

except KeyboardInterrupt:
    pygame.quit()
    sys.exit()
