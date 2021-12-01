#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
    char character;
    node *next;
};

void append(node **head, char character);
int len(node *head);
void print_list(node *head);