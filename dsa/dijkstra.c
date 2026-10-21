#include <stdio.h>
#include "dijkstra.h"

static int findMinimumDistanceNode(
    int distances[],
    int visited[],
    int nodeCount)
{
    int minimum = INF;
    int minimumIndex = -1;

    for (int i = 0; i < nodeCount; i++)
    {
        if (!visited[i] &&
            distances[i] < minimum)
        {
            minimum = distances[i];
            minimumIndex = i;
        }
    }

    return minimumIndex;
}

void dijkstra(Graph *graph,
              int sourceId,
              int distances[],
              int previous[])
{
    int sourceIndex =
        findGraphNode(graph, sourceId);

    if (sourceIndex == -1)
    {
        return;
    }

    int visited[MAX_NODES];

    for (int i = 0; i < graph->nodeCount; i++)
    {
        distances[i] = INF;
        previous[i] = -1;
        visited[i] = 0;
    }

    distances[sourceIndex] = 0;

    for (int count = 0;
         count < graph->nodeCount;
         count++)
    {
        int current =
            findMinimumDistanceNode(
                distances,
                visited,
                graph->nodeCount
            );

        if (current == -1)
            break;

        visited[current] = 1;

        for (int neighbor = 0;
             neighbor < graph->nodeCount;
             neighbor++)
        {
            int edgeDistance =
                graph->adjacencyMatrix[current][neighbor];

            if (edgeDistance == INF)
                continue;

            if (visited[neighbor])
                continue;

            if (distances[current] == INF)
                continue;

            int newDistance =
                distances[current] + edgeDistance;

            if (newDistance < distances[neighbor])
            {
                distances[neighbor] = newDistance;
                previous[neighbor] = current;
            }
        }
    }
}

int buildShortestPath(Graph *graph,
                      int sourceId,
                      int destinationId,
                      int path[],
                      int *pathLength,
                      int *totalDistance)
{
    int sourceIndex =
        findGraphNode(graph, sourceId);

    int destinationIndex =
        findGraphNode(graph, destinationId);

    if (sourceIndex == -1 ||
        destinationIndex == -1)
    {
        return 0;
    }

    int distances[MAX_NODES];
    int previous[MAX_NODES];

    dijkstra(graph,
             sourceId,
             distances,
             previous);

    if (distances[destinationIndex] == INF)
    {
        return 0;
    }

    int reversedPath[MAX_NODES];
    int count = 0;

    int current = destinationIndex;

    while (current != -1 &&
           count < MAX_NODES)
    {
        reversedPath[count] = current;

        if (current == sourceIndex)
            break;

        current = previous[current];
        count++;
    }

    if (count >= MAX_NODES ||
        reversedPath[count] != sourceIndex)
    {
        return 0;
    }

    *pathLength = count + 1;

    for (int i = 0; i < *pathLength; i++)
    {
        path[i] =
            graph->nodes[
                reversedPath[*pathLength - 1 - i]
            ].id;
    }

    *totalDistance =
        distances[destinationIndex];

    return 1;
}