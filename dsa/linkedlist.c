#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

StudentNode* createStudentNode(long long studentId)
{
    StudentNode *newNode =
        (StudentNode*)malloc(sizeof(StudentNode));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newNode->studentId = studentId;
    newNode->next = NULL;

    return newNode;
}

void insertStudent(StudentNode **head, long long studentId)
{
    StudentNode *newNode = createStudentNode(studentId);

    if (newNode == NULL)
        return;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    StudentNode *temp = *head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void deleteStudent(StudentNode **head, long long studentId)
{
    if (*head == NULL)
        return;

    StudentNode *temp = *head;
    StudentNode *prev = NULL;

    if (temp->studentId == studentId)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->studentId != studentId)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;
    free(temp);
}

StudentNode* searchStudent(StudentNode *head, long long studentId)
{
    StudentNode *temp = head;

    while (temp != NULL)
    {
        if (temp->studentId == studentId)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

void displayStudents(StudentNode *head)
{
    if (head == NULL)
    {
        printf("No students found.\n");
        return;
    }

    StudentNode *temp = head;

    while (temp != NULL)
    {
        printf("Student ID: %lld\n", temp->studentId);
        temp = temp->next;
    }
}

void freeStudentList(StudentNode **head)
{
    StudentNode *temp;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}