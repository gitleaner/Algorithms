/**
 Question 1
 Download the text file here. (Right click and save link as)
 The file contains the adjacency list representation of a simple undirected graph. There are 200 vertices labeled 1 to 200. The first column in the file represents the vertex label, and the particular row (other entries except the first column) tells all the vertices that the vertex is adjacent to. So for example, the 6th row looks like : "6	155	56	52	120	......". This just means that the vertex with label 6 is adjacent to (i.e., shares an edge with) the vertices with labels 155,56,52,120,......,etc
 
 Your task is to code up and run the randomized contraction algorithm for the min cut problem and use it on the above graph to compute the min cut. (HINT: Note that you'll have to figure out an implementation of edge contractions. Initially, you might want to do this naively, creating a new graph from the old every time there's an edge contraction. But you should also think about more efficient implementations.) (WARNING: As per the video lectures, please make sure to run the algorithm many times with different random seeds, and remember the smallest cut that you ever find.) Write your numeric answer in the space provided. So e.g., if your answer is 5, just type 5 in the space provided.
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <utility>
#include <time.h>
using namespace std;

void tokenizeBySpace (string line, int &startVertex, list<int> &edgeList)
{
    int str;
    bool foundVertex=false;
    stringstream s(line);
    while (s >> str)
    {
        if (!foundVertex)
        {
            startVertex = str;
            foundVertex = true;
        }
        else
            edgeList.push_back(str);
    }
}

class graph {
private:
    map <int, list<int> > adjList;
    int minCut;
    int numEdges()
    {
        int countEdges = 0;
        for (map<int, list<int> >::iterator iter=adjList.begin(); iter != adjList.end(); iter++)
        {
            countEdges += iter->second.size();
        }
        return countEdges;
    }
    
    int numEdges(int vertA)
    {
        int countEdges = 0;
        return adjList[vertA].size();
    }
    
    int numVertices()
    {
        return adjList.size();
    }
    
    bool edgeExist (int vertA, int vertB)
    {
        for (map<int, list<int> >::iterator iter=adjList.begin(); iter != adjList.end(); iter++)
        {
            if (iter->first == vertA)
            {
                for (list<int>::iterator locIter=iter->second.begin(); locIter != iter->second.end(); locIter++)
                {
                    if (*locIter == vertB)
                        return true;
                }
            }
        }
        return false;
    }
public:
    graph();
    ~graph();
    void print();
    int findMinCut();
    void removeSelfLoops();
    void mergeVertices(int vertA, int vertB);
};

graph::graph()
{
    /* Initialize graph here */
    fstream fread("kargerMinCut.txt");
    list<int> edgeList;
    int startVertex;
    
    while (!fread.eof())
    {
        string line;
        getline (fread, line);
        tokenizeBySpace (line, startVertex, edgeList);
        adjList.insert (make_pair(startVertex, edgeList));
        edgeList.clear();
    }
    print();
}

void graph::print()
{
    for (map<int, list<int> >::iterator iter=adjList.begin(); iter != adjList.end(); iter++)
    {
        cout << iter->first << " ";
        for (list<int>::iterator locIter=iter->second.begin(); locIter != iter->second.end(); locIter++)
            cout << *locIter << "  ";
        cout << endl;
    }
    
    cout << " Num Edges :: " << numEdges() << endl;
    cout << " Num Vertices :: "  << numVertices() << endl;
    cout << " Min Cut :: " << minCut << endl;
}

void graph::removeSelfLoops()
{
    for (map<int, list<int> >::iterator iter=adjList.begin(); iter != adjList.end(); iter++)
    {
        int startVertex = iter->first;
        list<int> &edgeList = iter->second;
        for (list<int>::iterator locIter=edgeList.begin(); locIter != edgeList.end(); locIter++)
        {
            if (*locIter == startVertex)
                edgeList.erase(locIter);
                
        }
    }
}

void graph::mergeVertices(int vertA, int vertB)
{
    list<int> &edgeListA = adjList[vertA];
    list<int> &edgeListB = adjList[vertB];
    
    edgeListA.insert (edgeListA.end(), edgeListB.begin(), edgeListB.end());
    adjList.erase(vertB);
    removeSelfLoops();
}

int graph::findMinCut()
{
    int vertA = 0, vertB = 0;
    
    while (numVertices() > 2)
    {
        bool foundEdge = false;
        while (!foundEdge)
        {
            vertA = rand() % 200;
            if (adjList.find(vertA))
            {
                vertB = rand() % numEdges(vertA);
                if (edgeExist(vertA, vertB) || edgeExist(vertB, vertA))
                {
                    foundEdge = true;
                    cout << "Merging (" << vertA << "," << vertB << ") " ;
                    // Found the random edge, contract now
                    mergeVertices(vertA, vertB);
                    cout << " Num Vertices :: " << numVertices() << endl;
                }
            }
        }
    }
    
    minCut = numEdges();
    return minCut;
}

graph::~graph()
{
    
}

int main()
{
    graph g;
    srand(time(NULL));
    g.findMinCut();
    g.print();
    return 1;
}