#include <assert.h>
#include <stdio.h>
#include "graph.h"
int main(void){
 Graph g; initializeGraph(&g); assert(g.nodeCount==0);
 assert(addGraphNode(&g,1,"B. Tech Block")); assert(addGraphNode(&g,2,"Civil Block")); assert(addGraphNode(&g,3,"Library"));
 assert(!addGraphNode(&g,1,"Duplicate"));
 assert(findGraphNode(&g,2)>=0); assert(findGraphNodeByName(&g,"Library")>=0); assert(findGraphNode(&g,99)==-1);
 assert(addGraphEdge(&g,1,2,111,1)); assert(getEdgeDistance(&g,1,2)==111); assert(getEdgeDistance(&g,2,1)==111);
 assert(!addGraphEdge(&g,1,3,0,1)); assert(!addGraphEdge(&g,1,99,10,1));
 assert(removeGraphEdge(&g,1,2)); assert(getEdgeDistance(&g,1,2)==INF);
 puts("PASS: Graph tests"); return 0;
}
