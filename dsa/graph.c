#include <stdio.h>
#include <string.h>
#include "graph.h"

void initializeGraph(Graph *graph)
{
    graph->nodeCount = 0;

    for (int i = 0; i < MAX_NODES; i++)
    {
        graph->nodes[i].id = -1;
        graph->nodes[i].name[0] = '\0';
        graph->nodes[i].active = 0;

        for (int j = 0; j < MAX_NODES; j++)
        {
            if (i == j)
                graph->adjacencyMatrix[i][j] = 0;
            else
                graph->adjacencyMatrix[i][j] = INF;
        }
    }
}

int findGraphNode(Graph *graph, int id)
{
    for (int i = 0; i < graph->nodeCount; i++)
    {
        if (graph->nodes[i].id == id &&
            graph->nodes[i].active)
        {
            return i;
        }
    }

    return -1;
}

int findGraphNodeByName(Graph *graph, const char *name)
{
    for (int i = 0; i < graph->nodeCount; i++)
    {
        if (graph->nodes[i].active &&
            strcmp(graph->nodes[i].name, name) == 0)
        {
            return i;
        }
    }

    return -1;
}

int addGraphNode(Graph *graph, int id, const char *name)
{
    if (graph->nodeCount >= MAX_NODES)
    {
        printf("Maximum graph nodes reached.\n");
        return 0;
    }

    if (findGraphNode(graph, id) != -1)
    {
        printf("Graph node already exists.\n");
        return 0;
    }

    int index = graph->nodeCount;

    graph->nodes[index].id = id;

    strncpy(graph->nodes[index].name,
            name,
            sizeof(graph->nodes[index].name) - 1);

    graph->nodes[index].name[
        sizeof(graph->nodes[index].name) - 1
    ] = '\0';

    graph->nodes[index].active = 1;

    graph->nodeCount++;

    return 1;
}

int addGraphEdge(Graph *graph,
                 int sourceId,
                 int destinationId,
                 int distance,
                 int bidirectional)
{
    int sourceIndex = findGraphNode(graph, sourceId);
    int destinationIndex = findGraphNode(graph, destinationId);

    if (sourceIndex == -1 || destinationIndex == -1)
    {
        printf("One or both graph nodes do not exist.\n");
        return 0;
    }

    if (distance <= 0)
    {
        printf("Distance must be greater than zero.\n");
        return 0;
    }

    graph->adjacencyMatrix[sourceIndex][destinationIndex] =
        distance;

    if (bidirectional)
    {
        graph->adjacencyMatrix[destinationIndex][sourceIndex] =
            distance;
    }

    return 1;
}

int removeGraphEdge(Graph *graph,
                    int sourceId,
                    int destinationId)
{
    int sourceIndex = findGraphNode(graph, sourceId);
    int destinationIndex = findGraphNode(graph, destinationId);

    if (sourceIndex == -1 || destinationIndex == -1)
        return 0;

    graph->adjacencyMatrix[sourceIndex][destinationIndex] = INF;

    return 1;
}

int getEdgeDistance(Graph *graph,
                     int sourceId,
                     int destinationId)
{
    int sourceIndex = findGraphNode(graph, sourceId);
    int destinationIndex = findGraphNode(graph, destinationId);

    if (sourceIndex == -1 || destinationIndex == -1)
        return INF;

    return graph->adjacencyMatrix[sourceIndex][destinationIndex];
}

void displayGraphNode(Graph *graph, int nodeId)
{
    int index = findGraphNode(graph, nodeId);

    if (index == -1)
    {
        printf("Node not found.\n");
        return;
    }

    printf("\nNode ID   : %d\n",
           graph->nodes[index].id);

    printf("Node Name : %s\n",
           graph->nodes[index].name);

    printf("Connections:\n");

    for (int i = 0; i < graph->nodeCount; i++)
    {
        int distance =
            graph->adjacencyMatrix[index][i];

        if (distance != INF && i != index)
        {
            printf("  -> %s : %d metres\n",
                   graph->nodes[i].name,
                   distance);
        }
    }
}

void displayGraph(Graph *graph)
{
    if (graph->nodeCount == 0)
    {
        printf("Campus graph is empty.\n");
        return;
    }

    printf("\n========== CAMPUS GRAPH ==========\n");

    for (int i = 0; i < graph->nodeCount; i++)
    {
        if (!graph->nodes[i].active)
            continue;

        printf("\n[%d] %s\n",
               graph->nodes[i].id,
               graph->nodes[i].name);

        for (int j = 0; j < graph->nodeCount; j++)
        {
            int distance =
                graph->adjacencyMatrix[i][j];

            if (distance != INF && i != j)
            {
                printf("    -> %s (%d m)\n",
                       graph->nodes[j].name,
                       distance);
            }
        }
    }
}