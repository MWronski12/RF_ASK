#include <stdio.h>
#include <stdlib.h>
#include "../include/linked_list.h"

void append(node **head, char character)
{
    node *new = (node*)malloc(sizeof(node));
    new->character = character;
    new->next = NULL;
    node *temp = *head;
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
    }
}

int len(node *head)
{
    int i = 0;
    while (head != NULL)
    {
        i++;
        head = head->next;
    }
    return i;
}

void print_list(node *head)
{
    if (head == NULL)
    {
        return;
    }
    printf("[ ");
    while (head != NULL)
    {
        printf("%c ", head->character);
        head = head->next;
    }
    printf("]");
}

// int main()
// {
//     node *head = NULL;
//     append(&head, 'a');
//     append(&head, 'c');
//     append(&head, 'a');
//     append(&head, 'b');
//     print_list(head);
//     return 1;
// }