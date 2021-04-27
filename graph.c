#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

    pointer ptr2=(pointer)malloc(sizeof(struct Node));
    ptr2->elem=source;
    ptr2->edge_len=edge_len;
    ptr2->next=NULL;

    pointer p2=G->pnext[dest];
    while(p2->next!=NULL){
        p2=p2->next;
    }
    p2->next=ptr2;

    // return G;
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


/*----------- choose_min for searching min_distance vertex from a source in a graph--------*/

vertex choose_min(int* min_distance,int* visited, Graph G)
{
    int min = INF,n = G->num_of_nodes,min_node=-1;

    for (int i = 0; i < n; ++i)
    {
        if(min_distance[i]<min && !visited[i])
        {
            min = min_distance[i];
            min_node = i;

        }
    }

    return min_node;
}


/*----------- Dijkstra for finding the shortest paths between nodes in a graph-------------*/

void Dijkstra(Graph G, vertex source, vertex destination)
{
    
    if(source<0||source>(G->num_of_nodes)-1)
        return;

    int *visited =(int*)malloc(sizeof(int)* (G->num_of_nodes));
    int *min_distance = (int*)malloc(sizeof(int)* (G->num_of_nodes));
    int *prev = (int*)malloc(sizeof(int)* (G->num_of_nodes));

    //intialise:
     for(int i=0;i<G->num_of_nodes;i++){
        visited[i] = 0;
        min_distance[i] = INF;
        prev[i] = -1;
    }

    // source node:
    visited[source] = 1;
    min_distance[source] = 0;
    prev[source] = -1;
    Node *p = G->pnext[source];
    while(p!=NULL) {
       min_distance[p->elem] = p->edge_len;
       if(p->elem!=source && min_distance[p->elem ]<INF)
        prev[p->elem] = source;
       p = p->next;
    }

      for(int i=1;i<G->num_of_nodes;i++){
        int k = choose_min(min_distance,visited,G);

        if(k==-1) continue;
        
        visited[k] = 1;

        Node *p = G->pnext[k];
        while(p!=NULL) {

        if(min_distance[p->elem] > min_distance[k] + p->edge_len && !visited[p->elem])
        {
            min_distance[p->elem] = min_distance[k] + p->edge_len;
            prev[p->elem] = k;    
        }
        p = p->next;
    }

  }

prev[source] = -1;

 //printf final path
  printf("source: %d\n", source);
  printf("destination: %d\n", destination);
  printf("min distance: %d\n", min_distance[destination]);
  printf("path: \n");

  
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
