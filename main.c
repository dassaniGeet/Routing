#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "conio.h"
#include "graph.h"

int main()
{

    clrscr();

    printf("/*-----------  <==       ...............   ==>  ------------*/\n");
    printf("                          Way To Hell                          \n");
    printf("\n\n");

    printf("                       Navigate & Explore                     \n");
    printf("/*-----------  <==       ...............     ==>  ------------*/\n\n\n");

    printf("WELCOME!\nExplore the World With Us!\n\n\n");

    int city;
    printf("\nEnter the city you want to start your exploration: \n");
    scanf("%d", &city);

starting:

    printf("                     Press:                  \n");
    printf("                    1. Admin                   \n");
    printf("                    2. User                   \n");
    int x;
    scanf("%d", &x);

    if (x != 1 && x != 2)
    {
        exit(0);
    }
    clrscr();
    printf("/*-----------  <==       ...............   ==>  ------------*/\n");
    printf("                          Way To Hell                          \n");
    printf("\n\n");

    printf("                       Navigate & Explore                     \n");
    printf("/*-----------  <==       ...............     ==>  ------------*/\n\n\n");

    printf("WELCOME!\nExplore the World With Us!\n\n\n");

    FILE *fptr = fopen("input_5.txt", "r");
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
    fscanf(fptr, "%d", &n);
    n=n+1;
    // printf("%d\n",n);

    Graph G;
    G = (Graph)malloc(sizeof(struct graph));
    assert(G != NULL);
    G->num_of_nodes = n;

    for (int i = 0; i < n; i++)
    {
        G->pnext[i] = (pointer)malloc(sizeof(struct Node));
    }

    G = init_graph(G, n);

    while (1)
    {

        int v1, v2, tr;
        double el;
        fscanf(fptr, "%d %d %lf %d", &v1, &v2, &el, &tr);

        if (v1 < 0 || v2 < 0)
        {
            break;
        }

        // printf("%d  %d  %g  %d\n",v1,v2,el,tr);

        add_vertex(G, v1, v2, el, tr);
    }

    /* User Window */
    if (x == 2)
    {

        vertex source, destination;
        printf("\nEnter Source:");
        scanf("%d", &source);
        printf("\n\nEnter Destination:");
        scanf("%d", &destination);

        printf("\n\n\n");
        printf("/*-----------  <==       ...............   ==>  ------------*/\n");

        Dijkstra(G, source, destination);
    }

    /* End */

    /* Admin Window */

    else if (x == 1)
    {
    password:

        printf("\n1. Enter Admin Password:\n2. Exit\n\n");
        int A;
        scanf("%d", &A);
        if(A==2){
            goto starting;
        }
        printf("Enter Password:\n");
        char s[100];
        scanf("%s",s);

        if(strcmp(s,"abc123")){
            printf("Wrong Password\nPlease Try Again\n");
            goto password;
        }

        printf("\n\n");

        Print_Graph(G, n);

    loop:
        printf("\n/*-----------  <==       ...............     ==>  ------------*/\n");
        printf("Enter action to performed:\n");
        printf("                    1. Add Edge                   \n");
        printf("                    2. Remove Edge                   \n");
        printf("                    3. Search Node                   \n");
        printf("                    4. Exit                   \n");
        printf("/*-----------  <==       ...............     ==>  ------------*/\n");

        int y;
        scanf("%d", &y);

        if (y == 1)
        {
            printf("Enter Vertices V1, V2, Edge Length and Traffic: ");
            vertex v1, v2;
            double el;
            int traffic;
            scanf("%d %d %lf %d", &v1, &v2, &el, &traffic);
            printf("\n\n");

            add_vertex(G, v1, v2, el, traffic);

            printf("\n\n\n");
            Print_Graph(G, n);
        }
        else if (y == 2)
        {
            printf("Enter Vertices V1,V2: ");
            int v1, v2;
            scanf("%d %d", &v1, &v2);

            printf("\n\n");
            delete_edge(G, v1, v2);

            printf("\n\n\n");

            Print_Graph(G, n);
        }
        else if (y == 3)
        {
            printf("Enter Vertex to be searched:");
            int a;
            scanf("%d", &a);
            printf("\n\n");

            int flag = search_node(G, a);
            if (flag == 0)
                printf("Not Found\n\n");
            else
                printf("Found\n\n");
        }
        else if (y == 4)
        {
            exit(0);
        }
        else
        {
            printf("Wrong Input!\n\n");
        }

        goto loop;

        // Print_Graph(G,n);
    }

    return 0;
}