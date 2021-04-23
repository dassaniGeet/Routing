#ifndef __GRAPH__H__
#define __GRAPH__H__

#define Max_Nodes 1000

typedef struct Node* pointer;
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

Graph init_graph(Graph G,int n);

void Print_Graph(Graph G,int n);

void add_vertex(Graph G,vertex source,vertex dest,int edge_len);

int search_node(Graph G,vertex a);


#endif  //!__GRAPH__H__