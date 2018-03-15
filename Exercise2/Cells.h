#ifndef __CELL_H_
#define __CELL_H_

typedef struct Node{
    int state;
    struct Node *prev;
    struct Node *next;
    struct Node *sender;
}Node_t;

int createCell(Node_t **root, int value);
void printCell(Node_t **root);
Node_t *sendSignal(Node_t **root, int step);
int hasExcitedneighbors(Node_t *current_node);

#endif