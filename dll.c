#include "apc.h"

int dl_insert_last(Dlist **head, Dlist **tail, int value) // makes list and store value from last
{
    Dlist *newNode = malloc(sizeof(Dlist));
    if (newNode == NULL)
    {
        return FAILURE;
    }
    newNode->prev = NULL;
    newNode->data = value;
    newNode->next = NULL;
    if (*head == NULL)
    {
        *head = *tail = newNode;
        return SUCCESS;
    }

    (*tail)->next = newNode;
    newNode->prev = *tail;
    *tail = newNode;

    return SUCCESS;
}

int dl_insert_first(Dlist **head, Dlist **tail, int value) // makes list and store value from first
{
    Dlist *newNode = malloc(sizeof(Dlist));
    if (newNode == NULL)
    {
        return FAILURE;
    }

    newNode->prev = NULL;
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = *tail = newNode;
        return SUCCESS;
    }
    else
    {
        (*head)->prev = newNode;
        newNode->next = *head;
        *head = newNode;
    }
    return SUCCESS;
}

int display(Dlist **head) // generally display the result stored in the list
{
    Dlist *temp;
    if (*head == NULL)
    {
        printf("list is empty!!\n");
        return FAILURE;
    }
    for (temp = *head; temp != NULL; temp = temp->next)
    {
        printf("%d", temp->data);
    }
    // //delete
    // while(*head!=NULL)
    // {
    //     temp = *head;
    //     *head = (*head)->next;
    //     free(temp);
    // }

    printf("\n");
    return SUCCESS;
}