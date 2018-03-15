#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Cells.h"

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Usage: ./ProgramName int:Size int:Step\n");
        return (1);
    }

    Node_t *root = NULL;
    int value = -1;
    int size = atoi((char *) argv[1]);
    int step = atoi((char *) argv[2]);

    if(size <= 0 || step < 0)
    {
        return (1);
    }
    printf("A cell can have two states: excited or quiet.\n"
            "1 signifies that the cell is excited,\n"
            "0 signifies that the cell is quiet.\n");

    printf("Please insert the %d states separated by a space followed by press enter: ", size);
    fflush(stdout);
    for(int i = 0; i < size; i++)
    {
        scanf("%d", &value);
        if (value < 0 ^ value > 1)
        {
            fprintf(stderr, "Please insert a valid state 1 or 0\n"
                            "separated by a space followed by press enter\n");
            return (1);
        }
        if(createCell(&root, value) != 0)
        {
            return (1);
        }
    }

    printf("Initial configuration of excited and quiet cells\n");
    printCell(&root);

    for (int i = 0; i < step; i++)
    {
      printf("\nStep number [%d]\n", i+1);
      sendSignal(&root, size);
      printCell(&root);
    }

    return (0);
}

Node_t *sendSignal(Node_t **root, int size)
{
    Node_t *current_node;
    current_node = *root;
    
    for (int i = 0; i < size; i++)
    {
        if(hasExcitedneighbors(current_node) && current_node->state == 1)
        {
            Node_t *next_node;
            next_node = current_node->next;
            Node_t * next_next_node;
            next_next_node = current_node->next->next;

            if(next_node->sender != next_next_node)
            {
                next_node->state = 1;
                next_node->sender = current_node;
            }else
            {
                next_node->state = 0;
                next_node->sender = current_node;                
            }

            Node_t *prev_node;
            prev_node = current_node->prev;
            Node_t * prev_prev_node;
            prev_prev_node = current_node->prev->prev;

            if(prev_node->sender != prev_prev_node)
            {
                prev_node->state = 1;
                prev_node->sender = current_node;
            }else
            {
                prev_node->state = 0;
                prev_node->sender = current_node;
            }
        }else
        {
            current_node->state = 0;
        }

        Node_t *next_node;
        next_node = current_node->next;
        current_node = next_node;
    }
    return (*root);
}


int createCell(Node_t **root, int value)
{
    Node_t *node;
    Node_t *prev_node;
    prev_node = *root;
    node = malloc(sizeof(Node_t));
    if (node == NULL)
    {
        return (1);
    }
    node->state = value;
    node->prev = NULL;
    node->next = NULL;
    node->sender = NULL;

    if (*root == NULL)
    {
        *root = node;
    }
    else
    {
        node->next = *root;
        (*root)->prev = node;
        if (prev_node->next == NULL)
        {
            prev_node->next = node;
        }
        else
        {
            while(prev_node->next != *root)
            {
                prev_node = prev_node->next;
            }
            prev_node->next = node;
        }
        node->prev = prev_node;
    }
    return (0);
}

void printCell(Node_t **root)
{
    Node_t *current_node;
    current_node = *root;

    while(current_node->next != *root)
    {
      printf("%d\n", current_node->state);
      current_node = current_node->next;
    }
    printf("%d\n", current_node->state);
}

int hasExcitedneighbors(Node_t *current_node)
{
    if(current_node->prev->state == 0 && current_node->next->state == 0)
    {
        return 0;
    }
    return 1;
}