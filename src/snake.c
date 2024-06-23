#include "project.h"

/**
 * Allocates space for a struct node, assigns parameters to its corresponding member values, 
 * and returns a pointer to the created node.
 * If any velocity is greater than 1 or less than -1, returns NULL.
*/
node_t *make_node(int x, int y) {
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(1);
    }

    node->x = x;
    node->y = y;
    node->next = NULL;
    return node;
}

/**
 * Moves the tail to the front snake depending on the snake's direction.
 * If the tail is bound to go off the Sense Hat 8x8 display, 
 * then it is wrapped around to the other side.
*/
void move_tail_to_front(node_t *head, node_t *tail, int vx, int vy) {
    tail->x = (head->x + vx) % 8;
    if (tail->x < 0) {
        tail->x += 8;
    }

    tail->y = (head->y + vy) % 8;
    if (tail->y < 0) {
        tail->y += 8;
    }
}

/**
 * Gets the last element in the snake and sets it to the beginning, returning the new head of the snake.
 * This updates the linked list pointers so that the penultimate item is now the last item, 
 * and the original tail is now the head of the snake.
 * If the head is NULL, returns NULL.
 * If the snake only has one node, then this simply moves that node and returns it.
*/
node_t *move_snake(node_t *head, int vx, int vy) {
    if (head == NULL) {
        return NULL;
    }

    if (head->next == NULL) {
        move_tail_to_front(head, head, vx, vy);
        return head;
    }

    node_t *penultimate = head;
    while (penultimate->next->next) {
        penultimate = penultimate->next;
    }

    node_t *tail = penultimate->next;
    tail->x = head->x + vx;
    tail->y = head->y + vy;
    move_tail_to_front(head, tail, vx, vy);

    penultimate->next = NULL;
    tail->next = head;
    return tail;
}

/**
 * Grows the snake by adding a new node at the specified x and y.
 * The old tail x and y should refer to the position of the tail of the snake before moving to it's next position.
*/
void grow_snake(node_t *head, int old_tail_x, int old_tail_y) {
    node_t *current_tail = head;
    while (current_tail->next) {
        current_tail = current_tail->next;
    }

    node_t *new_tail = make_node(old_tail_x, old_tail_y);
    current_tail->next = new_tail;
}

/**
 * Finds the tail given a snake head and assign the coordinates of the tail to the 
 * values pointing to the x and y passed in.
*/
void get_tail(node_t *head, int *x, int *y) {
    node_t *tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    *x = tail->x;
    *y = tail->y;
}

/**
 * Checks if the snake is colliding with it's own body, and returns 1 if it is, 0 if it isn't.
 * If the head is NULL or there is only one element in the snake, this returns 0.
*/
int is_colliding(node_t *head) {
    if (head == NULL || head->next == NULL) {
        return 0;
    }

    node_t *body = head->next;
    while (body) {
        if (head->x == body->x && head->y == body->y) {
            return 1;
        }

        body = body->next;
    }
    
    return 0;
}

/**
 * Frees the memory of all nodes in the snake.
*/
void free_snake(node_t *head) {
    while (head) {
        node_t *delete = head;
        head = head->next;
        free(delete);
    }
}
