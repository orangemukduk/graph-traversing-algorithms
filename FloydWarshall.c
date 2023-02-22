// Floyd Warshall ADT interface
// COMP2521 Assignment 2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "FloydWarshall.h"
#include "Graph.h"


/**
 * Finds all shortest paths between all pairs of nodes.
 * 
 * The  function  returns  a 'ShortestPaths' structure with the required
 * information:
 * - the number of vertices in the graph
 * - distance matrix
 * - matrix of intermediates (see description above)
 */
ShortestPaths FloydWarshall(Graph g) {
	// TODO: Implement this function
	//Intialising next and dist matrix
	int numNodes = GraphNumVertices(g);
	int ** dist = malloc(numNodes * sizeof(int *));
	int ** next = malloc(numNodes * sizeof(int *));
	for (int i = 0; i < numNodes; i++) { 
		dist[i] = malloc(numNodes * sizeof(int));
		next[i] = malloc(numNodes * sizeof(int));
	}
	//Intialising values of matrix (infinity if not connected)
	//(0 if connected)
	for (Vertex i = 0; i < numNodes; i++) { 
		for (Vertex j = 0; j < numNodes; j++) { 
			if (i == j) { 
				dist[i][j] = 0;
			}
			else { 
				dist[i][j] = INFINITY;
			}
			next[i][j] = -1;
		}
	}
	//Copy adjacency list to the matrix list dist
	for (Vertex i = 0; i < numNodes; i++){
		AdjList Adjacency = GraphOutIncident(g, i);
		while (Adjacency != NULL) {
			dist[i][Adjacency->v] = Adjacency->weight;
			next[i][Adjacency->v] = Adjacency->v;
			Adjacency = Adjacency->next;
		}
	}
	//Using FloydWarshall algorithm
	for (Vertex k = 0; k < numNodes; k++) {
		for (Vertex i = 0; i < numNodes; i++) {
			for (Vertex j = 0; j < numNodes; j++) {
				//This if statement prevents integer overflow i.e negative values
				if (dist[i][k] != INFINITY && dist[k][j] != INFINITY){
					if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = next[i][k];
					}
				}
			}
		}
	}
            

	ShortestPaths sps;
	sps.dist = dist;
	sps.next = next;
	sps.numNodes = numNodes;
	return sps;	
}	

/**
 * This  function  is  for  you to print out the ShortestPaths structure
 * while you are debugging/testing your implementation. 
 * 
 * We will not call this function during testing, so you may  print  out
 * the  given  ShortestPaths  structure in whatever format you want. You
 * may choose not to implement this function.
 */
void showShortestPaths(ShortestPaths sps) {

}

/**
 * Frees  all  memory associated with the given ShortestPaths structure.
 * We will call this function during testing, so you must implement it.
 */
void freeShortestPaths(ShortestPaths sps) {
	// TODO: Implement this function
	for (int i = 0; i < sps.numNodes; i++) {
	    int *currDist = sps.dist[i];
	    free(currDist);
	    int *currNext = sps.next[i];
	    free(currNext);
	     
	}
	free(sps.dist);
	free(sps.next);
}
