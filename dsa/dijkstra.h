
#ifdef __cplusplus
extern "C" {
#endif
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

void dijkstra(Graph *graph,
               int sourceId,
               int distances[],
               int previous[]);

int buildShortestPath(Graph *graph,
                      int sourceId,
                      int destinationId,
                      int path[],
                      int *pathLength,
                      int *totalDistance);

#endif
#ifdef __cplusplus
}
#endif
