// Centrality Measures ADT interface
// COMP2521 Assignment 2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "FloydWarshall.h"
#include "Graph.h"

/**
 * Finds  the  edge  betweenness  centrality  for each edge in the given
 * graph and returns the results in a  EdgeValues  structure.  The  edge
 * betweenness centrality of a non-existant edge should be set to -1.0.
 */
EdgeValues edgeBetweennessCentrality(Graph g) {
	// TODO: Implement this function
	int numNodes = GraphNumVertices(g);
	//Intialising 2D matrix of edge betweeness centrality set to -1.0
	double ** values = malloc(numNodes * sizeof(double *));
	for (int i = 0; i < numNodes; i++) { 
		values[i] = malloc(numNodes * sizeof(double));
	}
	for (int i = 0; i < numNodes; i++) { 
		for (int j = 0; j < numNodes; j++) { 
			values[i][j] = -1.0;
		}
	}
	ShortestPaths sps = FloydWarshall(g);
	//Go through each possible vertex in the graph and calculate if there is an edge
	for (int source_edge = 0; source_edge < numNodes; source_edge++) {
		for (int dest_edge = 0; dest_edge < numNodes; dest_edge++) {
		//If there exists an edge between two vertices
			if(GraphIsAdjacent(g, source_edge, dest_edge)) {
				values[source_edge][dest_edge] = 0.0;
			}
			//Go through each possible path in the graph and calculate edge betweeness
			for (int start_path = 0; start_path < numNodes; start_path++) {
				for (int end_path = 0; end_path < numNodes; end_path++) {
					int path_curr = start_path;
					while (path_curr != end_path && sps.dist[path_curr][end_path] < INFINITY) { 
						if (path_curr == source_edge && sps.next[path_curr][end_path] == dest_edge) { 
							values[source_edge][dest_edge]+= 1.0;
							}
						path_curr = sps.next[path_curr][end_path];
					}
				}
			}
		}





	}


    freeShortestPaths(sps);
	EdgeValues e;
	e.values = values;
	e.numNodes = numNodes;
	return e;
}

/**
 * Prints  the  values in the given EdgeValues structure to stdout. This
 * function is purely for debugging purposes and will NOT be marked.
 */
void showEdgeValues(EdgeValues evs) {

}

/**
 * Frees all memory associated with the given EdgeValues  structure.  We
 * will call this function during testing, so you must implement it.
 */
void freeEdgeValues(EdgeValues evs) {
	// TODO: Implement this function
		// TODO: Implement this function
	for (int i = 0; i < evs.numNodes; i++) {
	    double *currDist = evs.values[i];
	    free(currDist);
	     
	}
	free(evs.values);
}


