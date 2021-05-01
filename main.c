#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

int main(){

    int n;
    printf("Enter no. of nodes:\n");
    scanf("%d",&n);

    Graph G;
    G=(Graph)malloc(sizeof(struct graph));
    assert(G!=NULL);
    G->num_of_nodes=n;
    
    for(int i=0; i<n; i++){
        G->pnext[i]=(pointer)malloc(sizeof(struct Node));
    }

    G=init_graph(G,n);

    add_vertex(G,0,1,10); 
    add_vertex(G,0,4,5);  
    add_vertex(G,1,2,1);
    add_vertex(G,3,2,6);
    add_vertex(G,2,3,4);
    add_vertex(G,1,4,2);
    add_vertex(G,4,1,3);
    add_vertex(G,4,2,9);
    add_vertex(G,4,3,2);
    add_vertex(G,3,0,7);





    Print_Graph(G,n);

    printf("\nEnter vertex to be searched:\n");
    int a;
    scanf("%d",&a);

    int flag=search_node(G,a);
    if(flag==0)
        printf("Not Found\n");
    else
        printf("Found\n");

    vertex source,destination;
    printf("\nEnter source:\n");
    scanf("%d",&source);
    printf("Enter destination:\n");
    scanf("%d",&destination);

    Dijkstra(G,source,destination);

    return 0;
}