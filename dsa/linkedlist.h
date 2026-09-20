#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct ListNode
    {
        int data;
        struct ListNode *next;
    } ListNode;

    typedef struct
    {
        ListNode *head;
        int size;
    } LinkedList;

    void initList(LinkedList *list);
    void insertFront(LinkedList *list, int data);
    void insertEnd(LinkedList *list, int data);
    int deleteValue(LinkedList *list, int data);
    int searchList(LinkedList *list, int data);
    void displayList(LinkedList *list);
    void freeList(LinkedList *list);

#ifdef __cplusplus
}
#endif

#endif