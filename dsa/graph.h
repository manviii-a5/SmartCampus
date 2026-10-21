
#ifdef __cplusplus
extern "C" {
#endif
#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 100
#define INF 999999

typedef struct
{
    int id;
    char name[100];
    int active;
} GraphNode;

typedef struct
{
    int nodeId;
    int distance;
} GraphEdge;

typedef struct
{
    GraphNode nodes[MAX_NODES];

    int adjacencyMatrix[MAX_NODES][MAX_NODES];

    int nodeCount;
} Graph;

void initializeGraph(Graph *graph);

int addGraphNode(Graph *graph, int id, const char *name);

int findGraphNode(Graph *graph, int id);

int findGraphNodeByName(Graph *graph, const char *name);

int addGraphEdge(Graph *graph,
                 int sourceId,
                 int destinationId,
                 int distance,
                 int bidirectional);

int removeGraphEdge(Graph *graph,
                    int sourceId,
                    int destinationId);

int getEdgeDistance(Graph *graph,
                     int sourceId,
                     int destinationId);

void displayGraph(Graph *graph);

void displayGraphNode(Graph *graph, int nodeId);

#endif
#ifdef __cplusplus
}
#endif
