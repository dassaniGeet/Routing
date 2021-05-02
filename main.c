#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

int main(){

    printf("/*-----------  <==       ...............   ==>  ------------*/\n");
printf("                          Way To Hell                          \n");
printf("\n\n");

                
printf("                       Navigate & Explore                     \n");
printf("/*-----------  <==       ...............     ==>  ------------*/\n\n\n");

printf("WELCOME!\nExplore the World With Us!\n\n\n");

    int city;
    printf("\nEnter the city you want to start your exploration: \n");
    scanf("%d",&city);

    FILE *fptr=fopen("input.txt", "r");
    // if(city==1)
    //     fptr=fopen("input_1.txt","r");
    // else if(city==2)
    //     fptr=fopen("input_2.txt","r");
    // else if(city==3)
    //     fptr=fopen("input_3.txt","r");
    // else if(city==4)
    //     fptr=fopen("input_4.txt","r");
    // else if(city==5)
    //     fptr=fopen("input_5.txt","r");
    // else{
    //     printf("Invalid city\n");
    //     exit(0);
    // }

    // if ((fptr == NULL)){
    //      printf("Graph not available!\n");
    //      exit(0);
    // }

    int n;
    // printf("Enter no. of nodes:\n");
    fscanf(fptr,"%d",&n);
    // printf("%d\n",n);   

    Graph G;
    G=(Graph)malloc(sizeof(struct graph));
    assert(G!=NULL);
    G->num_of_nodes=n;
    
    for(int i=0; i<n; i++){
        G->pnext[i]=(pointer)malloc(sizeof(struct Node));
    }

    G=init_graph(G,n);

    while(1){

        int v1,v2,tr;
        double el;
        fscanf(fptr,"%d %d %lf %d",&v1,&v2,&el,&tr);

        if(v1<0 || v2<0){
            break;
        }

        // printf("%d  %d  %g  %d\n",v1,v2,el,tr);

        add_vertex(G,v1,v2,el,tr);
    }





    // Print_Graph(G,n);

    // printf("\nEnter vertex to be searched:\n");
    // int a;
    // scanf("%d",&a);

    // int flag=search_node(G,a);
    // if(flag==0)
    //     printf("Not Found\n");
    // else
    //     printf("Found\n");

    vertex source,destination;
    printf("\nEnter Source:");
    scanf("%d",&source);
    printf("\n\nEnter Destination:");
    scanf("%d",&destination);

    printf("\n\n\n");
    printf("/*-----------  <==       ...............   ==>  ------------*/\n");


    Dijkstra(G,source,destination);

    return 0;
}