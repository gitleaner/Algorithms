/**
 In this programming problem you'll code up Dijkstra's shortest-path algorithm.
 Download the text file here. (Right click and save link as).
 The file contains an adjacency list representation of an undirected weighted graph with 200 vertices labeled 1 to 200. Each row consists of the node tuples that are adjacent to that particular vertex along with the length of that edge. For example, the 6th row has 6 as the first entry indicating that this row corresponds to the vertex labeled 6. The next entry of this row "141,8200" indicates that there is an edge between vertex 6 and vertex 141 that has length 8200. The rest of the pairs of this row indicate the other vertices adjacent to vertex 6 and the lengths of the corresponding edges.
 
 Your task is to run Dijkstra's shortest-path algorithm on this graph, using 1 (the first vertex) as the source vertex, and to compute the shortest-path distances between 1 and every other vertex of the graph. If there is no path between a vertex v and vertex 1, we'll define the shortest-path distance between 1 and v to be 1000000.
 
 You should report the shortest-path distances to the following ten vertices, in order: 7,37,59,82,99,115,133,165,188,197. You should encode the distances as a comma-separated string of integers. So if you find that all ten of these vertices except 115 are at distance 1000 away from vertex 1 and 115 is 2000 distance away, then your answer should be 1000,1000,1000,1000,1000,2000,1000,1000,1000,1000. Remember the order of reporting DOES MATTER, and the string should be in the same order in which the above ten vertices are given. Please type your answer in the space provided.
 
 IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn) time implementation of Dijkstra's algorithm should work fine. OPTIONAL: For those of you seeking an additional challenge, try implementing the heap-based version. Note this requires a heap that supports deletions, and you'll probably need to maintain some kind of mapping between vertices and their positions in the heap.
**/

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <utility>
#include <string>
#include <sstream>
using namespace std;

int convertStrToInt (string str)
{
    int num;
    stringstream s(str);
    s >> num;
    return num;
}

void tokenizeBySpace (string line, int &startVertex, list<pair<int,int> > &edgeList)
{
    string str;
    bool foundVertex=false;
    stringstream s(line);
    while (s >> str)
    {
        if (!foundVertex)
        {
            startVertex = convertStrToInt(str);
            foundVertex = true;
        }
        else
        {
            vector<string> tokens;
            size_t current; size_t next = -1;
            do {
                current = next + 1;
                next = str.find_first_of( ",", current);
                tokens.push_back (str.substr(current, next-current));
            } while (next != string::npos);
            
            int toVertex = convertStrToInt (tokens[0]);
            int weight = convertStrToInt (tokens[1]);
            
            edgeList.push_back(make_pair(toVertex, weight));
        }
    }
}

class graph {
private:
    map <int, list<pair<int, int> > > adjList;
    int vertexCount;
    int edgeCount;
    
public:
    graph();
    ~graph();
    void print();
    void findShortestPath(int src);
};


graph::graph()
{
    edgeCount = 0; vertexCount = 0;
    
    /* Initialize graph here */
    fstream fread("dijkstraData.txt");
    int edge=0;
    list<pair<int, int> > edgeList;
    int startVertex;
    
    while (!fread.eof())
    {
        string line;
        getline (fread, line);
        tokenizeBySpace (line, startVertex, edgeList);
        adjList.insert (make_pair(startVertex, edgeList));
        edgeCount = edgeCount+edgeList.size();
        edgeList.clear();
    }
    vertexCount = adjList.size();
    //print();
}

void graph::print()
{
    for (map<int, list<pair<int, int> > >::iterator iter=adjList.begin(); iter != adjList.end(); iter++)
    {
        cout << iter->first << "   ";
        for (list<pair<int, int> >::iterator locIter=iter->second.begin(); locIter != iter->second.end(); locIter++)
            cout << locIter->first << "," << locIter->second << "   ";
        cout << endl;
    }
    
    cout << " Num Edges :: " << edgeCount<< endl;
    cout << " Num Vertices :: "  << vertexCount << endl;
}

graph::~graph()
{
    for (map<int, list<pair<int, int> > >::iterator mapIter = adjList.begin();mapIter != adjList.end(); mapIter++)
    {
        mapIter->second.clear();
    }
    adjList.clear();
}

void graph::findShortestPath (int src)
{
    vector<int> distance(vertexCount+1, 1000000);
    vector<bool> inTree(vertexCount+1, false);
    
    int dest = src;
    distance[src] = 0;
    while (!inTree[dest])
    {
        inTree[dest] = true;
        list<pair<int, int> >::iterator listIt = adjList[dest].begin();
        
        // Update weights for vertices adjacent to src
        for (listIt; listIt != adjList[dest].end(); listIt++)
        {
            if (distance[listIt->first] > (distance[dest] + listIt->second))
            {
                distance[listIt->first] = distance[dest] + listIt->second;
            }
        }
        
        // Find minimum edge for next traversal.
        int max = 1000000;
        for (int i=1; i<=vertexCount; i++)
        {
            if ((!inTree[i]) &&
                (distance[i] < max))
            {
                max = distance[i];
                dest = i;
            }
        }
    }

    for (size_t i=1; i<=distance.size(); i++)
    {
        if ((i==7) || (i==37) || (i==59) || (i==82) || (i==99) || (i==115) ||
            (i==133) || (i==165) || (i==188) || (i==197))
        {
            cout << distance[i] << ",";
        }
    }
    cout << endl;
}

int main()
{
    graph g;
    g.findShortestPath(1);
}