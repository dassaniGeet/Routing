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


typedef struct PriorityQNode PriorityQNode;
typedef struct PriorityQNode* PriorityQNodePtr;
typedef struct PriorityQ PriorityQ;
typedef struct PriorityQ* PriorityQPtr;

// Structure to represent a node in PriorityQ
typedef struct PriorityQNode
{
    vertex v;
    int edge_len;

} PriorityQNode;
 
// Structure to represent a PriorityQ
struct PriorityQ
{
    int size;    // Number of nodes present currently
    PriorityQNodePtr *priorityQ_arr;   // array which stores the PriorityQ
};
 


/*----------- init_graph for intialising a graph------------------------------------------*/
Graph init_graph(Graph G,int n);

/*----------- Print_Graph for printing a vertex in a graph--------------------------------*/
void Print_Graph(Graph G,int n);

/*----------- add_vertex for adding a vertex in a graph-----------------------------------*/
void add_vertex(Graph G,vertex source,vertex dest,int edge_len);

/*----------- search_node for searching a vertex in a graph-------------------------------*/
int search_node(Graph G,vertex a);

/*----------- priorityQ functions---------------------------------------------------------*/

//make new PriorityQNode
PriorityQNodePtr newPriorityQNode(vertex v, int distance);

// create a PriorityQ
PriorityQPtr createPriorityQ(int size);

//swap
void swap(PriorityQNodePtr* a, PriorityQNodePtr* b);

//heapify function in PriorityQ
void heapify(vertex parent_ind, PriorityQPtr PQ);

//extracts minimum node from PriorityQ
PriorityQNodePtr extractMin(PriorityQPtr PQ);

//decreases edge_len value of a given vertex v in PriorityQ. 
void decreaseKey(PriorityQPtr PQ,vertex v, int distance);

/*----------- choose_min for searching min_distance vertex from a source in a graph--------*/
vertex choose_min(PriorityQPtr PriorityQ,int* visited, Graph G);

/*----------- Dijkstra for finding the shortest paths between nodes in a graph-------------*/
void Dijkstra(Graph G, vertex source,vertex destination);

#endif  //!__GRAPH__H__