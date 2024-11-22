import ctypes
import pygame
import time
import sys

# Load the compiled C library
led_race = ctypes.CDLL('./led_race.so')

# Constants
NUM_LEDS = 480
LED_SIZE = 5
SPACING = 2
WINDOW_WIDTH = NUM_LEDS * (LED_SIZE + SPACING)
WINDOW_HEIGHT = 100
BACKGROUND_COLOR = (0, 0, 0)
LED_OFF_COLOR = (0, 0, 0)

# Initialize pygame
pygame.init()
screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption("LED Race Simulator (C Integration)")

# LED buffer to hold RGB values
ledsArray = (ctypes.c_uint8 * (NUM_LEDS * 3))()
offsetPattern = ctypes.c_int(0)
lastUpdate = ctypes.c_ulong(0)

# Function to draw LEDs
def draw_leds():
    screen.fill(BACKGROUND_COLOR)
    for i in range(NUM_LEDS):
        r = ledsArray[i * 3 + 0]
        g = ledsArray[i * 3 + 1]
        b = ledsArray[i * 3 + 2]
        color = (r, g, b)
        x = i * (LED_SIZE + SPACING)
        y = (WINDOW_HEIGHT - LED_SIZE) // 2
        pygame.draw.circle(screen, color, (x + LED_SIZE // 2, y + LED_SIZE // 2), LED_SIZE // 2)
    pygame.display.flip()

try:
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        currentMillis = int(time.time() * 1000)  # Milliseconds since epoch
        led_race.led_race_loop(
            ledsArray, 
            ctypes.c_ulong(currentMillis) 
        )
        draw_leds()
        time.sleep(0.01)  # Match the 10 ms update interval

except KeyboardInterrupt:
    pygame.quit()
    sys.exit()
