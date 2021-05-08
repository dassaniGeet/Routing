// A C++ Program to generate test cases for
// a weighted directed graph
#include<bits/stdc++.h>
using namespace std;

// Define the number of runs for the test data
// generated
#define RUN 1

// Define the maximum number of vertices of the graph
#define MAX_VERTICES 5000

// Define the maximum number of edges
#define MAX_EDGES 10000

// Define the maximum weight of edges
#define MAXWEIGHT 100

// Define the maximum number of traffic
#define  MAXTraffic 10000 


int main()
{
	set<pair<int, int>> container;
	set<pair<int, int>>::iterator it;

	// Uncomment the below line to store
	// the test data in a file
	// freopen("Test_Cases_Directed_Weighted_Graph.in",
	//		 "w", stdout);

	// For random values every time
	srand(time(NULL));

	int NUM; // Number of Vertices
	int NUMEDGE; // Number of Edges
    int NUMTraffic;// Number of Traffic

	for (int i=1; i<=RUN; i++)
	{
		NUM = 1 + rand() % MAX_VERTICES;

		// Define the maximum number of edges of the graph
		// Since the most dense graph can have N*(N-1)/2 edges
		// where N = n number of vertices in the graph
		NUMEDGE = 1 + rand() % MAX_EDGES;

        NUMTraffic=1+ rand() % MAXTraffic;

		while (NUMEDGE > NUM*(NUM-1)/2)
			NUMEDGE = 1 + rand() % MAX_EDGES;

		// First print the number of vertices and edges
		printf("%d %d\n", NUM, NUMEDGE);

		// Then print the edges of the form (a b)
		// where 'a' is connected to 'b'
		for (int j=1; j<=NUMEDGE; j++)
		{
			int a = 1 + rand() % NUM;
			int b = 1 + rand() % NUM;
			pair<int, int> p = make_pair(a, b);

			// Search for a random "new" edge every time
			// Note - In a tree the edge (a, b) is same
			// as the edge (b, a)
			while (container.find(p) != container.end())
			{
				a = 1 + rand() % NUM;
				b = 1 + rand() % NUM;
				p = make_pair(a, b);
			}
			container.insert(p);
		}

		for (it=container.begin(); it!=container.end(); ++it)
		{
			int wt = 1 + rand() % MAXWEIGHT;
            int tr= 1+ rand() % MAXTraffic;
			printf("%d %d %d %d\n", it->first, it->second, wt, tr);
		}

		container.clear();
		printf("\n");

	}

	// Uncomment the below line to store
	// the test data in a file
	// fclose(stdout);
	return(0);
}
