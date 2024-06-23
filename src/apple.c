#include "project.h"

/**
 * Allocates space for a struct apple, assigns it a default x and y, 
 * and returns a pointer to the created object.
*/
apple_t *generate_apple(void) {
    apple_t *apple = malloc(sizeof(apple_t));
    if (apple == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(1);
    }

    apple->x = 0;
    apple->y = 0;
    return apple;
}

/**
 * Sets the position of the apple to a random coordinate inside the Sense Hat 8x8 display.
 * If the randomly generated coordinate overlaps with the provided snake's position, then
 * this continuously regenerates it until it finds an unused position.
*/
void randomize_position(apple_t *apple, node_t *snake) {
    int overlapping, rand_x, rand_y;
    do {
        overlapping = 0;
        rand_x = rand() % 8;
        rand_y = rand() % 8;
        node_t *node = snake;
        while (node) {
            if (node->x == rand_x && node->y == rand_y) {
                overlapping = 1;
                break;
            }

            node = node->next;
        }
    } while (overlapping);
    apple->x = rand_x;
    apple->y = rand_y;
}

int is_eaten(apple_t *apple, node_t *snake_head) {
    return apple->x == snake_head->x && apple->y == snake_head->y;
}
