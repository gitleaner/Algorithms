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
#include <random>
#include <time.h>
using namespace std;


std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, 200);

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
        return adjList[vertA].size();
    }
    
    int findVertex (int vertA, int position)
    {
        list<int>::iterator iter=adjList[vertA].begin();
        for (int i=0; i<position; i++)
            iter++;
        return *iter;
    }
    
    int numVertices()
    {
        return adjList.size();
    }
        
public:
    graph();
    ~graph();
    void print();
    int findMinCut();
    void removeSelfLoops(int vertA);
    void mergeVertices(int vertA, int vertB);
    void replaceFromVertToVert (int fromVert, int toVert);
};

graph::graph()
{
    /* Initialize graph here */
    fstream fread("kargerMinCut.txt");
    //fstream fread("1.txt");
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

void graph::removeSelfLoops(int vertA)
{
    adjList[vertA].remove(vertA);
}

void graph::replaceFromVertToVert (int fromVert, int toVert)
{
    for (map<int, list<int> >::iterator iter=adjList.begin(); iter != adjList.end(); iter++)
    {
        for (list<int>::iterator locIter=iter->second.begin(); locIter != iter->second.end(); locIter++)
        {
            if (*locIter == fromVert)
                *locIter = toVert;
        }
    }
}

void graph::mergeVertices(int vertA, int vertB)
{
    list<int> &edgeListA = adjList[vertA];
    list<int> &edgeListB = adjList[vertB];
    
    edgeListA.insert (edgeListA.end(), edgeListB.begin(), edgeListB.end());
    adjList.erase(vertB);
    replaceFromVertToVert(vertB, vertA);
    removeSelfLoops(vertA);
}

int getRandomNumber ()
{
    int randNum =  distribution(generator);
    distribution.reset();
    return randNum;
}

int graph::findMinCut()
{
    int vertA, vertB;
    while (numVertices() > 2)
    {
        int randIndexA =  (rand())%numVertices();
        int mapIterCount=1;
        map<int, list<int> >::iterator mapIter = adjList.begin();
        for (mapIter=adjList.begin(); ((mapIter != adjList.end()) && (mapIterCount < randIndexA)); mapIter++)
            mapIterCount++;
        vertA = mapIter->first;
        
        //cout << " NumVertices = " << numVertices() << " NumEdges = " << numEdges(vertA) << endl;
        
        int randIndexB = (rand())%numEdges(vertA);
        int listIterCount=1;
        list<int>::iterator listIter = adjList[vertA].begin();
        for (listIter=adjList[vertA].begin(); ((listIter != adjList[vertA].end()) && (listIterCount < randIndexB)); listIter++)
            listIterCount++;
        vertB = *listIter;
        
        mergeVertices (vertA, vertB);
        //cout << "RandA = " << randIndexA << " " << "RandB = " << randIndexB << endl;
        cout << "Merging (" << vertA << "," << vertB  << "), " << " Num Vertices :: "  << numVertices() << endl;
    }
    minCut = numEdges()/2;
    return minCut;
}

graph::~graph()
{
    
}

int main()
{
    srand (time(NULL));
    graph g;
    g.findMinCut();
    g.print();
    return 1;
}