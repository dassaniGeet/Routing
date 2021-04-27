#ifndef __GRAPH__H__
#define __GRAPH__H__

#define Max_Nodes 1000
#define INF 100000
typedef struct Node* pointer;
typedef struct Node Node;
typedef struct graph* Graph;
typedef int vertex;


struct Node{
    int elem;
    int edge_len;
    struct Node* next;
};

struct graph{
    int num_of_nodes;
    pointer pnext[Max_Nodes];
};

/*----------- init_graph for intialising a graph------------------------------------------*/
Graph init_graph(Graph G,int n);

/*----------- Print_Graph for printing a vertex in a graph--------------------------------*/
void Print_Graph(Graph G,int n);

/*----------- add_vertex for adding a vertex in a graph-----------------------------------*/
void add_vertex(Graph G,vertex source,vertex dest,int edge_len);

/*----------- search_node for searching a vertex in a graph-------------------------------*/
int search_node(Graph G,vertex a);

/*----------- choose_min for searching min_distance vertex from a source in a graph--------*/
vertex choose_min(int* min_distance,int* visited, Graph G);

/*----------- Dijkstra for finding the shortest paths between nodes in a graph-------------*/
void Dijkstra(Graph G, vertex source,vertex destination);

#endif  //!__GRAPH__H__