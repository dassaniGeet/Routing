#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "graph.h"

/*----------- init_graph for intialising a graph---------*/

Graph init_graph(Graph G,int n){
    for(int i=0;i<n;i++){
        G->pnext[i]->elem=i;
        G->pnext[i]->edge_len=0;
        G->pnext[i]->next=NULL;
    }
    return G;
}

/*----------- add_vertex for adding a vertex in a graph---------*/
void add_vertex(Graph G,vertex source,vertex dest,int edge_len){
    pointer ptr=(pointer)malloc(sizeof(struct Node));
    ptr->elem=dest;
    ptr->edge_len=edge_len;
    ptr->next=NULL;

    pointer p=G->pnext[source];

    while(p->next!=NULL){
        p=p->next;
    }
    p->next=ptr;

    // pointer ptr2=(pointer)malloc(sizeof(struct Node));
    // ptr2->elem=source;
    // ptr2->edge_len=edge_len;
    // ptr2->next=NULL;

    // pointer p2=G->pnext[dest];
    // while(p2->next!=NULL){
    //     p2=p2->next;
    // }
    // p2->next=ptr2;

}


/*----------- search_node for searching a vertex in a graph---------*/
int search_node(Graph G,vertex a){
    if(G->pnext[a]->next==NULL)
        return 0;

    return 1;   
}


/*----------- Print_Graph for printing a vertex in a graph---------*/
void Print_Graph(Graph G,int n){
    if(G==NULL){
        printf("NULL\n");
        return;
    }
    
    for(int i=0 ; i<G->num_of_nodes ; i++){
        pointer p=G->pnext[i];
        while(p->next!=NULL){
            printf("%d(Edge len between %d and %d is %d)\t",p->elem,i,p->elem,p->edge_len);

            p=p->next;
        }
        printf("%d(Edge len between %d and %d is %d)\n",p->elem,i,p->elem,p->edge_len);
    }
}


/*----------- priorityQ functions---------------------------------------------------------*/
// This is needed for decreaseKey(). keeps track of position of each vertex. so pos[i] gives position of vertex i in PriorityQ_arr
int *pos; 

//make new PriorityQNode
PriorityQNodePtr newPriorityQNode(vertex v, int distance)
{
    PriorityQNodePtr PQNode = (PriorityQNodePtr) malloc(sizeof(PriorityQNode));
    PQNode->v = v;
    PQNode->edge_len = distance;
    return PQNode;
}
 
// create a PriorityQ
PriorityQPtr createPriorityQ(int size)
{
    PriorityQPtr PQ = (PriorityQPtr) malloc(sizeof(PriorityQ));
    PQ->size = size;
    PQ->priorityQ_arr = (PriorityQNodePtr*) malloc(size *sizeof(PriorityQNodePtr));
    return PQ;
}
 

//swap
void swap(PriorityQNodePtr* a, PriorityQNodePtr* b)
{
    PriorityQNodePtr temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//heapify function in PriorityQ
void heapify(vertex parent_ind, PriorityQPtr PQ)
{
    int smallest_ind, left_child_ind,right_child_ind;

    // Find the smallest among root, left child and right child
    smallest_ind = parent_ind;

    left_child_ind = 2 * parent_ind + 1;
    if (left_child_ind < PQ->size && PQ->priorityQ_arr[left_child_ind]->edge_len <  PQ->priorityQ_arr[smallest_ind]->edge_len)
      smallest_ind = left_child_ind;

    right_child_ind= 2 * parent_ind + 2;
    if (right_child_ind < PQ->size && PQ->priorityQ_arr[right_child_ind]->edge_len <  PQ->priorityQ_arr[smallest_ind]->edge_len)
       smallest_ind = right_child_ind;
 
    // Swap and continue heapifying if root is not smallest
    if (smallest_ind != parent_ind) {
      // Swap positions
      pos[PQ->priorityQ_arr[smallest_ind]->v] = parent_ind;
      pos[PQ->priorityQ_arr[parent_ind]->v] = smallest_ind;

      // Swap nodes
      swap(&(PQ->priorityQ_arr[parent_ind]), &(PQ->priorityQ_arr[smallest_ind]));
      heapify(smallest_ind,PQ);
    }
}
 

//extracts minimum node from PriorityQ
PriorityQNodePtr extractMin(PriorityQPtr PQ)
{
    //if PQ isEmpty
    if (PQ->size==0) return NULL;
 
    // Replace root node with last node: (root = PQ->priorityQ_arr[0]) (lastNode = PQ->priorityQ_arr[(PQ->size) - 1])
    PriorityQNodePtr root = PQ->priorityQ_arr[0];
    pos[PQ->priorityQ_arr[0]->v] = PQ->size-1;
    pos[PQ->priorityQ_arr[(PQ->size) - 1]->v] = 0;
    swap(&(PQ->priorityQ_arr[0]),&(PQ->priorityQ_arr[(PQ->size) - 1]));
 
    // Reduce PriorityQ size and heapify root
    --PQ->size;
    heapify(0,PQ);
 
    return root;
}
 
//decreases edge_len value of a given vertex v in PriorityQ. 
void decreaseKey(PriorityQPtr PQ,vertex v, int distance)
{
    //Get the index of v in PriorityQ array. This function uses pos[] of min heap to get the current index of node in min heap.
    int i = pos[v];
 
    //Get the node and update its edge_len value
    PQ->priorityQ_arr[i]->edge_len = distance;

    //while PriorityQ is not hepified
    while (PQ->priorityQ_arr[i]->edge_len < PQ->priorityQ_arr[(i - 1) / 2]-> edge_len)
    {
        // Swap this node with its parent
        int parent_ind = (i-1)/2;
        pos[PQ->priorityQ_arr[i]->v] = parent_ind;
        pos[PQ->priorityQ_arr[parent_ind]->v] = i;

        swap(&(PQ->priorityQ_arr[i]),&(PQ->priorityQ_arr[parent_ind]));

        parent_ind = (parent_ind - 1) / 2;
    }
}
 
/*----------- choose_min for searching min_distance vertex from a source in a graph--------*/

vertex choose_min(PriorityQPtr PQ,int* visited, Graph G)
{
    int k;
    struct PriorityQNode* PQNode = extractMin(PQ);

    if(PQNode!=NULL) k = PQNode->v;
    else k = -1;

    return k;
}


/*----------- Dijkstra for finding the shortest paths between nodes in a graph-------------*/

void Dijkstra(Graph G, vertex source, vertex destination)
{
    
    //checks for valid source
    if(source<0||source>(G->num_of_nodes)-1)
        return;

    /*
    visited[i] --> keeps track of visited nodes
    min_distance[i] --> minimum distance of vertex i from source
    prev[i] --> previous node visted before i in shortest path from source
    PQ -> priorityQ for choose_min for searching min_distance vertex from a source in a graph
    pos[i] ->  keeps track of position of each vertex in PriorityQ. so pos[i] gives position of vertex i in PriorityQ_arr.
    */

    int *visited =(int*)malloc(sizeof(int)* (G->num_of_nodes));
    int *min_distance = (int*)malloc(sizeof(int)* (G->num_of_nodes));
    int *prev = (int*)malloc(sizeof(int)* (G->num_of_nodes));
    struct PriorityQ* PQ = createPriorityQ(G->num_of_nodes);
    pos = (int *)malloc((G->num_of_nodes )* sizeof(int));

    
    /*
    intialise:
    none of the nodes are visited
    min_distance of all nodes is INF and insert in PriorityQ
    and prev nodes -1
    */

     for(int i=0;i<G->num_of_nodes;i++){
        visited[i] = 0;
        min_distance[i] = INF;
        PQ->priorityQ_arr[i] = newPriorityQNode(i,min_distance[i]);
        pos[i] = i;
        prev[i] = -1;
    }

    /*
     source node:
     source_node = visited   visited[source] = 1 , min_distance[source] = 0
     for all neighbours of source node => min_distance[i] = edge_len and decreaseKey() this new min_distance in PriorityQ
    */

    min_distance[source] = 0;
    decreaseKey(PQ, source, min_distance[source]);
    visited[source] = 1;
    min_distance[source] = 0;
    prev[source] = -1;
    Node *p = G->pnext[source];
    while(p!=NULL) {
       min_distance[p->elem] = p->edge_len;
       decreaseKey(PQ, p->elem, min_distance[p->elem]); 
       if(p->elem!=source && min_distance[p->elem ]<INF)
          prev[p->elem] = source;

       p = p->next;
    }

    /*
    for(i=1;i<G->num_of_nodes;i++) // i.e till all nodes are visited
    {
    1. choose the minimum vertex
         ..... make it visited
    2. update the estimates of the neighbours of this minimum vertex 
        .... make its prev node the minimum vertex from step 1
    }
    */

    for(int i=1;i<G->num_of_nodes;i++)
      {

        int k = choose_min(PQ,visited,G);
        if(k==-1) continue;
        
        visited[k] = 1;

        Node *p = G->pnext[k];
        while(p!=NULL) {

        if(min_distance[p->elem] > min_distance[k] + p->edge_len && !visited[p->elem])
        {
            //printf("min_distance: %d\n", min_distance[k]);
            min_distance[p->elem] = min_distance[k] + p->edge_len;
            prev[p->elem] = k; 
            decreaseKey(PQ, p->elem, min_distance[p->elem]);   
        }
        p = p->next;
    }

  }

 prev[source] = -1;

 //print final path:
  printf("Source: %d\n", source);
  printf("Destination: %d\n", destination);
  printf("Min Distance: %d\n", min_distance[destination]);
  printf("Path: \n");

 /*

  //debug
  
  for (int i = 0; i < G->num_of_nodes; ++i)
  {
     printf("%d , ", min_distance[i]);
  }

  printf("\n");

  for (int i = 0; i < G->num_of_nodes; ++i)
  {
     printf("%d , ", prev[i]);
  }

  printf("\n");

*/

  if(prev[destination]==-1)
  {
    //printf("%d\n", source);
    printf("No path\n");
    return;
  }

  while(prev[destination]!=-1)
  {
    printf("%d <===== ", destination);
    destination = prev[destination];
  }

  printf("%d\n", source);
  return;
}