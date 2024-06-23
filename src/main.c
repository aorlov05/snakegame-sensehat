#include "project.h"

int vx = 1, vy = 0; // Direction that the snake is moving
int moving = 0; // If a key has just been pressed
int running = 1; // Current program state

void joystickCallback(unsigned int code);

int main(void) {
    srand(getpid()); // Sets the seed for random number generation to the process id
    open_input();
    int opened_display = open_display();
    if (!opened_display) {
        fprintf(stderr, "Could not open Sense Hat display");
        return 1;
    }

    node_t *node = make_node(3, 3);
    apple_t *apple = generate_apple();
    randomize_position(apple, node);
    while (running) {
        clear_display();
        display_snake(node);
        display_apple(apple);
        check_input(joystickCallback, 1000);
        // Joystick presses run four times, twice when the key is pressed in and twice when the key is released.
        // This prevents a duplicate movement by preventing the snake from moving on duplicate key press.
        if (moving) {
            moving--;
            continue;
        }

        int old_tail_x, old_tail_y;
        get_tail(node, &old_tail_x, &old_tail_y);
        node = move_snake(node, vx, vy);
        if (is_eaten(apple, node)) {
            grow_snake(node, old_tail_x, old_tail_y);
            randomize_position(apple, node);
        }

        if (is_colliding(node)) {
            running = 0;
            sleep(3);
        }
    }

    clear_display();
    close_display();
    free_snake(node);
    close_input();
    return 0;
}

/**
 * Takes an joystick key code and sets the direction of the snake 
 * to that which corresponds to the direction the joystick was pressed.
*/
void joystickCallback(unsigned int code) {
    if (code == KEY_UP) { // RIGHT
        vx = -1;
        vy = 0;
        moving = 3;
    } else if (code == KEY_DOWN) { // LEFT
        vx = 1;
        vy = 0;
        moving = 3;
    } else if (code == KEY_LEFT) { // UP
        vx = 0;
        vy = -1;
        moving = 3;
    } else if (code == KEY_RIGHT) { // DOWN
        vx = 0;
        vy = 1;
        moving = 3;
    } else if (code == KEY_ENTER) { // PRESS IN
        running = 0;
    }
}
