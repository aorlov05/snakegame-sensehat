#include "project.h"

sense_joystick_t *joystick;

/**
 * Opens a connection with the Sense Hat joystick.
 * Allocates a pi_joystick_t object if one hasn't been made which must be freed by calling close_input().
*/
void open_input(void) {
    if (joystick == NULL) {
        joystick = get_joystick();
    }
}

/**
 * Frees the memory associated a previouslly allocated Sense Hat joystick.
*/
void close_input(void) {
    if (joystick != NULL) {
        free_joystick(joystick);
        joystick = NULL;
    }
}

/**
 * Checks for user input on the joystick for 'delay' milliseconds, 
 * and calls the callback function if the joystick is pressed.
*/
void check_input(void (*callback)(unsigned int code), int delay) {
    read_next_joystick_event(joystick, delay, callback);
}
