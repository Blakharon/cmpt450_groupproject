#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

#define MAX_NODES 10

int capacities[MAX_NODES][MAX_NODES]; // Capacities of each edge [from][to]
int flowPassed[MAX_NODES][MAX_NODES];
vector<int> graph[MAX_NODES]; // Holds a vector of what edges each node is connected to
int parentsList[MAX_NODES];
int currentPathCapacity[MAX_NODES];

int breadthFirstSearch(int startNode, int endNode)
{
    memset(parentsList, -1, sizeof(parentsList)); // set unvisited 
    memset(currentPathCapacity, 0, sizeof(currentPathCapacity)); // set current capacities to 0

    queue<int> q;

    q.push(startNode);
    parentsList[startNode] = -2;

    currentPathCapacity[startNode] = 1000; // a filler number

    while(!q.empty())
    {
        int currentNode = q.front();
        q.pop();

        for(int i = 0; i < graph[currentNode].size(); i++)
        {
            int to = graph[currentNode][i];

            if(parentsList[to] == -1)
            {
                if(capacities[currentNode][to] - flowPassed[currentNode][to] > 0)
                {
                    parentsList[to] = currentNode;
                    currentPathCapacity[to] = min(currentPathCapacity[currentNode], 
                    capacities[currentNode][to] - flowPassed[currentNode][to]);

                    if(to == endNode)
                    {
                        return currentPathCapacity[endNode];
                    }

                    q.push(to);
                }
            }
        }
    }
    
    return 0;
}

int edmondsKarp(int startNode, int endNode)
{
    int maxFlow = 0;

    // Keep filling up all paths until maximum flow is reached
    while(true)
    {
        int flow = breadthFirstSearch(startNode, endNode);

        if (flow == 0) 
        {
            break;
        }

        maxFlow += flow;
        int currentNode = endNode;
        
        while(currentNode != startNode)
        {
            int previousNode = parentsList[currentNode];

            flowPassed[previousNode][currentNode] += flow;
            flowPassed[currentNode][previousNode] -= flow;
            currentNode = previousNode;
        }
    }

    return maxFlow;
}

int main()
{
    int nodesCount, edgesCount;
    cout << "Enter the number of nodes and edges (Max is " << MAX_NODES << ")" << endl;
    cin >> nodesCount >> edgesCount;
    
    cout << "Nodes range from 0-" << to_string(nodesCount - 1) << endl;
    
    int source, sink;
    cout << "Enter the source and sink" << endl;
    cin >> source >> sink;

    cout << "Creating graph..." << endl;
    cout << "For each edge you will tell the start node, end node, and the capacity" << endl << endl;
    
    for(int edge = 0; edge < edgesCount; edge++)
    {
        cout << "Edge: " << to_string(edge) << endl;
        cout << "Enter the start node, end node, and capacity" << endl;

        int from, to, capacity;
        cin >> from >> to >> capacity;

        capacities[from][to] = capacity;
        graph[from].push_back(to);
        graph[to].push_back(from);

        cout << endl;
    }
    
    int maxFlow = edmondsKarp(source, sink);
    cout << endl << endl << "Max Flow is:" << maxFlow << endl;
}
