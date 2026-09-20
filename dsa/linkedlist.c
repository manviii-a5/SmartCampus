#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void initList(LinkedList* list)
{
    list->head = NULL;
    list->size = 0;
}

void insertFront(LinkedList* list, int data)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = data;
    newNode->next = list->head;

    list->head = newNode;
    list->size++;
}

void insertEnd(LinkedList* list, int data)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL)
    {
        list->head = newNode;
    }
    else
    {
        ListNode* temp = list->head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    list->size++;
}

int deleteValue(LinkedList* list, int data)
{
    if (list->head == NULL)
        return 0;

    ListNode* temp = list->head;
    ListNode* prev = NULL;

    while (temp != NULL)
    {
        if (temp->data == data)
        {
            if (prev == NULL)
                list->head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            list->size--;

            return 1;
        }

        prev = temp;
        temp = temp->next;
    }

    return 0;
}

int searchList(LinkedList* list, int data)
{
    ListNode* temp = list->head;

    while (temp != NULL)
    {
        if (temp->data == data)
            return 1;

        temp = temp->next;
    }

    return 0;
}

void displayList(LinkedList* list)
{
    ListNode* temp = list->head;

    if (temp == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    printf("Linked List: ");

    while (temp != NULL)
    {
        printf("%d", temp->data);

        if (temp->next != NULL)
            printf(" -> ");

        temp = temp->next;
    }

    printf("\n");
}

void freeList(LinkedList* list)
{
    ListNode* temp;

    while (list->head != NULL)
    {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
    }

    list->size = 0;
}