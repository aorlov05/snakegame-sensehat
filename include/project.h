#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include "sense.h"

typedef struct node {
    int x, y;
    struct node *next;
} node_t;

typedef struct apple {
    int x, y;
} apple_t;

void open_input(void);
void close_input(void);
void check_input(void (*callback)(unsigned int code), int delay);

int open_display(void);
void display_pixel(int x, int y);
void display_snake(node_t *head);
void display_apple(apple_t *apple);
void clear_display(void);
void close_display(void);

node_t *make_node(int x, int y);
node_t *move_snake(node_t *head, int vx, int vy);
void grow_snake(node_t *head, int old_tail_x, int old_tail_y);
void get_tail(node_t *head, int *x, int *y);
int is_colliding(node_t *head);
void free_snake(node_t *head);

apple_t *generate_apple(void);
void randomize_position(apple_t *apple, node_t *snake);
int is_eaten(apple_t *apple, node_t *snake_head);
