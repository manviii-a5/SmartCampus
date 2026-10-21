
#ifdef __cplusplus
extern "C" {
#endif
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct StudentNode {
    long long studentId;
    struct StudentNode *next;
} StudentNode;

StudentNode* createStudentNode(long long studentId);

void insertStudent(StudentNode **head, long long studentId);

void deleteStudent(StudentNode **head, long long studentId);

StudentNode* searchStudent(StudentNode *head, long long studentId);

void displayStudents(StudentNode *head);

void freeStudentList(StudentNode **head);

#endif
#ifdef __cplusplus
}
#endif
