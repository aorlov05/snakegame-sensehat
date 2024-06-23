#include "project.h"

sense_framebuffer_t *fb;

/**
 * Opens the frame buffer on the Raspberry Pi Sense Hat.
 * If the sense hat was accessed, returns 1, otherwise returns 0.
*/
int open_display(void) {
    fb = get_sense_hat_framebuffer();
    if (fb == NULL) {
        return 0;
    }

    return 1;
}

/**
 * Sets the pixel on the Sense Hat which corresponds to the inputted x and y to white.
*/
void display_pixel(int x, int y) {
    set_pixel(fb, x, y, rgb888_to_rgb565(255, 255, 255));
}

/**
 * Displays every pixel of a snake linked list on the Sense Hat.
*/
void display_snake(node_t *head) {
    while (head) {
        display_pixel(head->x, head->y);
        head = head->next;
    }
}

/**
 * Sets the pixel of the coordinates of the apple to red.
*/
void display_apple(apple_t *apple) {
    set_pixel(fb, apple->x, apple->y, rgb888_to_rgb565(255, 0, 0));
}

/**
 * Clears the display by setting every pixel to 0x0000.
*/
void clear_display(void) {
    clear_screen(fb);
}

/**
 * Frees the frame buffer and shuts down the program.
*/
void close_display(void) {
    free_framebuffer(fb);
}
