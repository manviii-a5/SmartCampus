#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
int main(void){
 UndoStack s; initializeStack(&s); assert(isStackEmpty(&s));
 assert(popUndo(&s).operationId==-1);
 for(int i=1;i<=STACK_MAX;i++){ UndoOperation o; o.operationId=i; o.operationType=1; snprintf(o.description,sizeof(o.description),"operation %d",i); pushUndo(&s,o); }
 assert(isStackFull(&s)); assert(peekUndo(&s).operationId==STACK_MAX);
 UndoOperation next; next.operationId=STACK_MAX+1; next.operationType=2; strcpy(next.description,"latest"); pushUndo(&s,next);
 assert(isStackFull(&s)); assert(peekUndo(&s).operationId==STACK_MAX+1);
 assert(popUndo(&s).operationId==STACK_MAX+1); clearUndoStack(&s); assert(isStackEmpty(&s));
 puts("PASS: Stack tests"); return 0;
}
