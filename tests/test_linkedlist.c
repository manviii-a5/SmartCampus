#include <assert.h>
#include <stdio.h>
#include "linkedlist.h"
int main(void){
 StudentNode *head=NULL; assert(searchStudent(head,10)==NULL);
 insertStudent(&head,10); insertStudent(&head,20); insertStudent(&head,30);
 assert(searchStudent(head,20)!=NULL); assert(searchStudent(head,99)==NULL);
 deleteStudent(&head,20); assert(searchStudent(head,20)==NULL);
 deleteStudent(&head,10); assert(searchStudent(head,10)==NULL);
 deleteStudent(&head,30); assert(head==NULL);
 freeStudentList(&head); assert(head==NULL);
 puts("PASS: Linked list tests"); return 0;
}
