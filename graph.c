#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

Graph init_graph(Graph G,int n){
    for(int i=0;i<n;i++){
        G->pnext[i]->elem=i;
        G->pnext[i]->edge_len=0;
        G->pnext[i]->next=NULL;
    }
    return G;
}

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

int search_node(Graph G,vertex a){
    if(G->pnext[a]->next==NULL)
        return 0;

    return 1;   
}

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

    add_vertex(G,0,3,2);
    add_vertex(G,0,5,3);
    add_vertex(G,1,4,4);
    add_vertex(G,2,3,5);

    Print_Graph(G,n);

    printf("\nEnter vertex to be searched:\n");
    int a;
    scanf("%d",&a);

    int flag=search_node(G,a);
    if(flag==0)
        printf("Not Found\n");
    else
        printf("Found\n");

    return 0;
}