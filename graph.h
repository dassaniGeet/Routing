#ifndef __GRAPH__H__
#define __GRAPH__H__

#define Max_Nodes 5000
#define INF 10000000
typedef int vertex;

/*--------------------- graph -------------------------*/
typedef struct Node* pointer;
typedef struct Node Node;
typedef struct graph* Graph;


//graph node
struct Node{
    int elem;
    double edge_len;
    // int we_edge;
    double con;
    double time;
    struct Node* next;
};

//graph
struct graph{
    int num_of_nodes;
    pointer pnext[Max_Nodes];
};

/*--------------------- priorityQ -------------------------*/
typedef struct PriorityQNode PriorityQNode;
typedef struct PriorityQNode* PriorityQNodePtr;
typedef struct PriorityQ PriorityQ;
typedef struct PriorityQ* PriorityQPtr;

// Structure to represent a node in PriorityQ
typedef struct PriorityQNode
{
    vertex v;
    double time;

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

/*----------- add_edge for adding a vertex in a graph-----------------------------------*/
void add_edge(Graph G,vertex source,vertex dest,double edge_len,int traffic);

/*----------- search_node for searching a vertex in a graph-------------------------------*/
int search_node(Graph G,vertex a);

/*----------- delete edge from the graph------------------------------------------------- */
void delete_edge(Graph G,vertex v1,vertex v2);

/*----------- search edge from the graph------------------------------------------------- */
void search_edge(Graph G,vertex v1,vertex v2);

/*----------- priorityQ functions---------------------------------------------------------*/

//make new PriorityQNode
PriorityQNodePtr newPriorityQNode(vertex v, double time);

// create a PriorityQ
PriorityQPtr createPriorityQ(int size);

//swap
void swap(PriorityQNodePtr* a, PriorityQNodePtr* b);

//heapify function in PriorityQ
void heapify(vertex parent_ind, PriorityQPtr PQ);

//extracts minimum node from PriorityQ
PriorityQNodePtr extractMin(PriorityQPtr PQ);

//decreases edge_len value of a given vertex v in PriorityQ. 
void decreaseKey(PriorityQPtr PQ,vertex v, double time);

/*----------- choose_min for searching min_distance vertex from a source in a graph--------*/
vertex choose_min(PriorityQPtr PriorityQ,int* visited, Graph G);

/*----------- Dijkstra for finding the shortest paths between nodes in a graph-------------*/
void Dijkstra(Graph G, vertex source,vertex destination,int city);

/*----------- graph visuals--------------------------------*/
void writeMapNetwork(Graph g);
void ViewMapNetwork(Graph g);
#endif  //!__GRAPH__H__