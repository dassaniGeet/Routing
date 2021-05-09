#include "graph.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*----------- init_graph for intialising a graph---------*/

Graph init_graph(Graph G, int n) {
  for (int i = 0; i < n; i++) {
    G->pnext[i]->elem = i;
    G->pnext[i]->edge_len = 0;
    // G->pnext[i]->we_edge=0;
    G->pnext[i]->con = 0;
    G->pnext[i]->next = NULL;
  }
  return G;
}

/*----------- add_edge for adding a vertex in a graph---------*/
void add_edge(Graph G, vertex source, vertex dest, double edge_len,
              int traffic) {
  pointer ptr = (pointer)malloc(sizeof(struct Node));
  ptr->elem = dest;
  ptr->edge_len = edge_len;

  /*
   Congestion ratio = traffic/edge length
   v = Speed , denotes the max speed a vehicle can drive on the road with
   particular congestion ratio. Time = edge length/appropriate speed. A higher
   ratio of congestion signifies more time and hence must be avoided. A higher
   ratio of congestion => lower max speed of a vehicle.
   */

  ptr->con = traffic / edge_len;
  double temp = traffic / edge_len;

  if (temp <= 50) {
    double v = 80;
    ptr->time = edge_len / v;
  } else if (temp <= 250) {
    double v = 50;
    ptr->time = edge_len / v;
  } else if (temp <= 500) {
    double v = 30;
    ptr->time = edge_len / v;
  } else {
    double v = 5;
    ptr->time = edge_len / v;
  }

  ptr->next = NULL;

  pointer p = G->pnext[source];

  while (p->next != NULL) {
    p = p->next;
  }
  p->next = ptr;
}

/*----------- search_node for searching a vertex in a graph---------*/
int search_node(Graph G, vertex a) {
  if (G->pnext[a]->next == NULL)
    return 0;

  return 1;
}

/*----------- Print_Graph for printing a vertex in a graph---------*/
void Print_Graph(Graph G, int n) {
  if (G == NULL) {
    printf("NULL\n");
    return;
  }

  printf("\n \n Graph:\n");

  for (int i = 0; i < G->num_of_nodes; i++) {
    pointer p = G->pnext[i];
    while (p->next != NULL) {
      printf("%d[Edge len between %d and %d is %g] ===> ", p->elem, i, p->elem,
             p->edge_len);

      p = p->next;
    }
    printf("%d[Edge len between %d and %d is %g]\n\n", p->elem, i, p->elem,
           p->edge_len);
  }
}

/*----------- delete edge from the graph------------------------------------------------- */
void delete_edge(Graph G, vertex v1, vertex v2) {
  pointer p = G->pnext[v1];

  int flag = 0;
  int last = 0;
  pointer prev = (pointer)malloc(sizeof(struct Node));
  prev = p;
  while (p->next != NULL) {
    if (p->elem == v2) {
      flag = 1;
      break;
    }
    prev = p;
    p = p->next;
  }
  if (p->elem == v2 && flag == 0) {
    flag = 1;
    last = 1;
  }

  if (flag == 0) {
    printf("Edge not present!\n");
  } else {
    if (last == 1) {
      prev->next = NULL;
    } else {
      prev->next = p->next;
    }
  }

  return;
}

/*----------- search edge from the graph------------------------------------------------- */
void search_edge(Graph G, vertex v1, vertex v2) 
{
    pointer p = G->pnext[v1];

  int flag = 0;

  while (p->next != NULL) {
    if (p->elem == v2) {
      flag = 1;
      printf("edge_len: %g\n",p->edge_len);
      printf("edge_time: %g\n",p->time);
      break;
    }

    p = p->next;
  }

  if (p->elem == v2 && flag == 0) {
    flag = 1;
    printf("edge_len: %g\n",p->edge_len);
    printf("edge_time: %g\n",p->time);
  }

  if (flag == 0) {
    printf("Edge not present!\n");
  } 

  return;
}

/*----------- priorityQ functions---------------------------------------------------------*/
// This is needed for decreaseKey(). keeps track of position of each vertex. so
// pos[i] gives position of vertex i in PriorityQ_arr
int *pos;

// make new PriorityQNode
PriorityQNodePtr newPriorityQNode(vertex v, double time) {
  PriorityQNodePtr PQNode = (PriorityQNodePtr)malloc(sizeof(PriorityQNode));
  PQNode->v = v;
  PQNode->time = time;
  return PQNode;
}

// create a PriorityQ
PriorityQPtr createPriorityQ(int size) {
  PriorityQPtr PQ = (PriorityQPtr)malloc(sizeof(PriorityQ));
  PQ->size = size;
  PQ->priorityQ_arr =
      (PriorityQNodePtr *)malloc(size * sizeof(PriorityQNodePtr));
  return PQ;
}

// swap
void swap(PriorityQNodePtr *a, PriorityQNodePtr *b) {
  PriorityQNodePtr temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

// heapify function in PriorityQ
void heapify(vertex parent_ind, PriorityQPtr PQ) {
  int smallest_ind, left_child_ind, right_child_ind;

  // Find the smallest among root, left child and right child
  smallest_ind = parent_ind;

  left_child_ind = 2 * parent_ind + 1;
  if (left_child_ind < PQ->size && PQ->priorityQ_arr[left_child_ind]->time <
                                       PQ->priorityQ_arr[smallest_ind]->time)
    smallest_ind = left_child_ind;

  right_child_ind = 2 * parent_ind + 2;
  if (right_child_ind < PQ->size && PQ->priorityQ_arr[right_child_ind]->time <
                                        PQ->priorityQ_arr[smallest_ind]->time)
    smallest_ind = right_child_ind;

  // Swap and continue heapifying if root is not smallest
  if (smallest_ind != parent_ind) {
    // Swap positions
    pos[PQ->priorityQ_arr[smallest_ind]->v] = parent_ind;
    pos[PQ->priorityQ_arr[parent_ind]->v] = smallest_ind;

    // Swap nodes
    swap(&(PQ->priorityQ_arr[parent_ind]), &(PQ->priorityQ_arr[smallest_ind]));
    heapify(smallest_ind, PQ);
  }
}

// extracts minimum node from PriorityQ
PriorityQNodePtr extractMin(PriorityQPtr PQ) {
  // if PQ isEmpty
  if (PQ->size == 0)
    return NULL;

  // Replace root node with last node: (root = PQ->priorityQ_arr[0]) (lastNode =
  // PQ->priorityQ_arr[(PQ->size) - 1])
  PriorityQNodePtr root = PQ->priorityQ_arr[0];
  pos[PQ->priorityQ_arr[0]->v] = PQ->size - 1;
  pos[PQ->priorityQ_arr[(PQ->size) - 1]->v] = 0;
  swap(&(PQ->priorityQ_arr[0]), &(PQ->priorityQ_arr[(PQ->size) - 1]));

  // Reduce PriorityQ size and heapify root
  --PQ->size;
  heapify(0, PQ);

  return root;
}

// decreases edge_len value of a given vertex v in PriorityQ.
void decreaseKey(PriorityQPtr PQ, vertex v, double time) {
  // Get the index of v in PriorityQ array. This function uses pos[] of min heap
  // to get the current index of node in min heap.
  int i = pos[v];

  // Get the node and update its edge_len value
  PQ->priorityQ_arr[i]->time = time;

  // while PriorityQ is not hepified
  while (PQ->priorityQ_arr[i]->time < PQ->priorityQ_arr[(i - 1) / 2]->time &&
         i != 0) {
    // Swap this node with its parent
    int parent_ind = (i - 1) / 2;

    swap(&(PQ->priorityQ_arr[i]), &(PQ->priorityQ_arr[parent_ind]));

    pos[PQ->priorityQ_arr[i]->v] = parent_ind;
    pos[PQ->priorityQ_arr[parent_ind]->v] = i;

    i = parent_ind;

    // parent_ind = (parent_ind - 1) / 2;
  }
}

/*----------- choose_min for searching min_distance vertex from a source in a graph--------*/

vertex choose_min(PriorityQPtr PQ, int *visited, Graph G) {
  /* // brute force n^2 find minimum
    int k = INF;
    for (int i = 0; i < G->num_of_nodes; ++i) {
      if (min_time[i] < k && !visited[i])
         k = i;
     }
  */

  // find minimum using min-heaps
  int k;
  struct PriorityQNode *PQNode = extractMin(PQ);

  if (PQNode != NULL)
    k = PQNode->v;
  else
    k = -1;

  return k;
}

/*----------- Dijkstra for finding the shortest paths between nodes in a graph-------------*/

void Dijkstra(Graph G, vertex source, vertex destination, int city) {

  // checks for valid source
  if (source < 0 || source > (G->num_of_nodes) - 1)
    return;

  /*
  visited[i] --> keeps track of visited nodes
  min_distance[i] --> minimum distance of vertex i from source
  min_time[i] --> minimum time of vertex i from source
  prev[i] --> previous node visted before i in shortest path from source
  PQ -> priorityQ for choose_min for searching min_distance vertex from a source
  in a graph pos[i] ->  keeps track of position of each vertex in PriorityQ. so
  pos[i] gives position of vertex i in PriorityQ_arr.
  */

  int *visited = (int *)malloc(sizeof(int) * (G->num_of_nodes));
  double *min_distance = (double *)malloc(sizeof(double) * (G->num_of_nodes));
  double *min_time = (double *)malloc(sizeof(double) * (G->num_of_nodes));
  int *prev = (int *)malloc(sizeof(int) * (G->num_of_nodes));
  struct PriorityQ *PQ = createPriorityQ(G->num_of_nodes);
  pos = (int *)malloc((G->num_of_nodes) * sizeof(int));

  /*
  intialise:
  none of the nodes are visited
  min_time of all nodes is INF and insert in PriorityQ
  min_distance of all nodes is INF
  and prev nodes -1
  */

  for (int i = 0; i < G->num_of_nodes; i++) {
    visited[i] = 0;
    min_distance[i] = INF;
    min_time[i] = INF;
    PQ->priorityQ_arr[i] = newPriorityQNode(i, min_time[i]);
    pos[i] = i;
    prev[i] = -1;
  }

  /*
   source node:
   source_node = visited   visited[source] = 1 , min_distance[source] = 0,
   min_time[source] = 0 for all neighbours p of source node => min_distance[i] =
   p->edge_len and min_time[i] = p->time decreaseKey() this new min_distance in
   PriorityQ
  */

  min_distance[source] = 0;
  min_time[source] = 0;
  decreaseKey(PQ, source, min_time[source]);
  visited[source] = 1;
  prev[source] = -1;

  Node *p = G->pnext[source];
  while (p != NULL) {
    min_distance[p->elem] = p->edge_len;
    min_time[p->elem] = p->time;
    decreaseKey(PQ, p->elem, min_time[p->elem]);
    if (p->elem != source && min_time[p->elem] < INF)
      prev[p->elem] = source;

    p = p->next;
  }

  /*

    for(i=1;i<G->num_of_nodes;i++) // i.e till all nodes are visited
    {
    1. choose the minimum time vertex
           ..... make it visited
    2. update the estimates of the neighbours of this minimum vertex
           ..... make its prev node the minimum vertex from step 1
    }
    */

  for (int i = 1; i < G->num_of_nodes; i++) {

    int k = choose_min(PQ, visited, G);

    if (k == -1)
      continue;

    visited[k] = 1;

    Node *p = G->pnext[k];
    while (p != NULL) {

      if (min_time[p->elem] > min_time[k] + p->time && !visited[p->elem]) {
        // printf("min_distance: %d\n", min_distance[k]);
        min_distance[p->elem] = min_distance[k] + p->edge_len;
        min_time[p->elem] = min_time[k] + p->time;
        prev[p->elem] = k;
        decreaseKey(PQ, p->elem, min_time[p->elem]);
      }
      p = p->next;
    }
  }

  prev[source] = -1;

  // UI time functionality
  double t = min_time[destination];
  int hrs = (int)floor(t);
  int min = (t - hrs) * 60;

  time_t now;
  time(&now);

  struct tm *local = localtime(&now);

  int hours = local->tm_hour; // get hours since midnight (0-23)
  int minutes = local->tm_min;
  int day = local->tm_mday;  // get day of month (1 to 31)
  int month = local->tm_mon; // get month of year (0 to 11)
  int year = local->tm_year; // get minutes passed after the hour (0-59)

  printf("\nCity: %d\n\n", city);

  printf("Source: %d\n\n", source);

  printf("Destination:%d\n\n", destination);

  printf("\n\n");

  printf("/*-----------  <==       ...............   ==>  ------------*/\n\n");

  printf("Approximate Distance(kms): %g\n\n", min_distance[destination]);
  printf("Approximate Minimum Time: %dhrs %dmins\n", hrs, min);

  printf("\n\n\n");
  printf("/*-----------  <==       ...............   ==>  ------------*/\n\n");

  printf("Current Time:   %s", ctime(&now));

  minutes = minutes + min;
  hours = hours + hrs;

  if (minutes >= 60) {
    hours++;
    minutes = minutes - 60;
  }
  if (hours >= 24) {
    hours = hours - 24;
  }

  printf("Approximate Arrival Time:   %d:%d  \n\n", hours, minutes);

  // printing map path
  printf("Map Path: \n");

  if (prev[destination] == -1) {
    // printf("%d\n", source);
    printf("No path\n");
    return;
  }

  while (prev[destination] != -1) {
    printf("%d <===== ", destination);
    destination = prev[destination];
  }

  printf("%d\n", source);
  return;
}

  
void writeMapNetwork(Graph g) {

    system("clear");
    FILE *f = fopen("graphviz.dot", "w");

    fprintf(f, "digraph MAPS {\n");
    fprintf(f, "\tnode [fontname=\"Consolas\", shape=oval, style=filled, color=\".7 .3 1.0\"];\n");

     // printf("hie\n");
      for (int i = 0; i < g->num_of_nodes; ++i) {
        if (g->pnext[i]) {
            pointer temp = g->pnext[i];
            //printf("hie1\n");
            fprintf(f, "\t\"%d\" -> ", temp->elem);
            while (temp->next != NULL) {
                fprintf(f, "\"%d\"", temp->elem);
                fprintf(f, " -> ");
                temp = temp->next;
                    
            }
            fprintf(f, "\"%d\"", temp->elem);
            fprintf(f, "\n");
             //printf("hie2\n");
        }
    }
    fprintf(f, "}");

    fclose(f);
}

void ViewMapNetwork(Graph g) {
    writeMapNetwork(g);
    system("dot -Tpng graphviz.dot -o map-network.png && xdg-open map-network.png");
}